#include "StdAfx.h"
#include "Transformer.h"
#include "Winding.h"
#include "gmshFile.h"
#include "frmContourPlot.h"
#include <vcclr.h>
#include "..\TransFE\MeshDB\MeshVertex.h"
#include "..\TransFE\mapping2d.h"
#include "..\TransFE\lintrisf.h"
#include "..\TransFE\quadtrisf.h"
#include "..\TransFE\linquadsf.h"
#include "..\TransFE\quadquadsf.h"

#define PI 3.141592653589793238512808959406186204433

Transformer::Transformer(void)
{
	windings = gcnew List<Winding^>();
	core = gcnew Core();

	feprog = new FEProg();

	I_base=60;
}

Winding^ Transformer::addWinding(){
	Winding^ newWinding = gcnew Winding;
	newWinding->transformer = this;
	windings->Add(newWinding);
	return newWinding;
}

void Transformer::deleteWinding(Winding^ deletedWinding){
	windings->Remove(deletedWinding);
}

void Transformer::writeWindingsGmsh(gmshFile^ outFile){
	for each (Winding^ winding in windings) {
		winding->writeSectionsGmsh(outFile);
	}
}

void Transformer::writeTransformerGmsh(String^ filename){

	gmshFile^ outFile = gcnew gmshFile(filename);
	outFile->ElementOrder = ElementOrder;
	//This is ugly, but necessary...
	//Iterate through all sections to find outermost section
	double max_sec_radius = 0;
	for each (Winding^ winding in windings) {
		for each (Section^ section in winding->sections) {
			if(section->radius_outer > max_sec_radius) {
				max_sec_radius = section->radius_outer;
			}
		}
	}

	//Create reactangle for core window
	//outFile->gmshRectangle(core->radius_leg, 0, core->radius_leg + max_sec_width + dist_WdgTnk, core->window_height);
	//Have to do this manually, because we want the point for the boundary condition to be in the middle of the left side.
	gmshPoint^ ll = gcnew gmshPoint(core->radius_leg, 0, 0);
	gmshPoint^ lr = gcnew gmshPoint(max_sec_radius + dist_WdgTnk, 0, 0);
	gmshPoint^ ur = gcnew gmshPoint(max_sec_radius + dist_WdgTnk, core->window_height, 0);
	gmshPoint^ ul = gcnew gmshPoint(core->radius_leg, core->window_height, 0);
	gmshPoint^ bc = gcnew gmshPoint(max_sec_radius + dist_WdgTnk, core->window_height/2, 0); //gcnew gmshPoint(core->radius_leg, core->window_height/2, 0);
	//The "boundary condition" point MUST be first...
	outFile->points->Add(bc);
	outFile->points->Add(ll);
	outFile->points->Add(lr);
	outFile->points->Add(ur);
	outFile->points->Add(ul);
	gmshLine^ bottom = gcnew gmshLine(ll, lr);
	//gmshLine^ right = gcnew gmshLine(lr, ur);
	gmshLine^ right_lower = gcnew gmshLine(lr, bc);
	gmshLine^ right_upper = gcnew gmshLine(bc, ur);
	gmshLine^ top = gcnew gmshLine(ur, ul);
	//gmshLine^ left_upper = gcnew gmshLine(ul, bc);
	//gmshLine^ left_lower = gcnew gmshLine(bc, ll);
	gmshLine^ left = gcnew gmshLine(ul, ll);
	outFile->lines->Add(bottom);
	//outFile->lines->Add(right);
	outFile->lines->Add(right_lower);
	outFile->lines->Add(right_upper);
	outFile->lines->Add(top);
	//outFile->lines->Add(left_upper);
	//outFile->lines->Add(left_lower);
	outFile->lines->Add(left);
	List<gmshLine^>^ rect_lines = gcnew List<gmshLine^>;
	rect_lines->Add(bottom);
	//rect_lines->Add(right);
	rect_lines->Add(right_lower);
	rect_lines->Add(right_upper);
	rect_lines->Add(top);
	//rect_lines->Add(left_upper);
	//rect_lines->Add(left_lower);
	rect_lines->Add(left);
	gmshLineLoop^ rect = gcnew gmshLineLoop(rect_lines);
	outFile->line_loops->Add(rect);

	writeWindingsGmsh(outFile);
	outFile->writeFile();
}

void Transformer::writeAttributes(String^ filename) {
	StreamWriter^ sw = File::CreateText(filename);
	//The first "entity" should always be the boundary condition point
	//where we define the potential to be 0 (half-way up the left side)
	sw->WriteLine("GeomEntity 1");
	sw->WriteLine("x_constraint 0");
	//The second "entity" should always be the air surrounding the windings
	sw->WriteLine("GeomEntity 2");
	sw->WriteLine("mu 1.0");
	//The remaining "entities" are the windings themselves
	int index = 2;
	for each (Winding^ winding in windings) {
		for each (Section^ section in winding->sections) {
			index++;
			sw->WriteLine("GeomEntity {0}", index);
			sw->WriteLine("mu 1.0");
			sw->WriteLine("J {0}", section->CurrentDensity()*winding->currDir);
			sw->WriteLine("wdg_num {0}", windings->IndexOf(winding));
			sw->WriteLine("section_num {0}", winding->sections->IndexOf(section));
		}
	}
	sw->Close();
}

void Transformer::setFilename(String^ name){
	filename = name;
}

/*ostringstream* Transformer::getStream(){
	return &(feprog->outStream);
}*/

void Transformer::runFEA(){
	pin_ptr<const wchar_t> wch = PtrToStringChars(filename);
	size_t convertedChars = 0;
	size_t  sizeInBytes = ((filename->Length + 1) * 2);
	errno_t err = 0;
	char *ch = (char *)malloc(sizeInBytes);

	err = wcstombs_s(&convertedChars, 
                    ch, sizeInBytes,
                    wch, sizeInBytes);

	Stopwatch^ stopWatch;
	stopWatch = gcnew Stopwatch;
	stopWatch->Start();

	delete feprog;
	//delete feaMesh;

	feprog = new FEProg();

	feaMesh = feprog->run_FEA(ch, formulation);

	stopWatch->Stop();
	int runTime = stopWatch->ElapsedMilliseconds;
	//MessageBox::Show( "Run Time minus X calc (ms) = " + runTime, "Run Time",
	//	MessageBoxButtons::OK, MessageBoxIcon::Exclamation );

}

void Transformer::calcX(){
	MeshFace* face;
	vector<MeshFace*>::iterator face_iter;
	vector<DOF*> DOFs;

	double W = 0;
	double W_anderson = 0;
	for(face_iter=feaMesh->getFirstFace();face_iter!=feaMesh->getLastFace();face_iter++){
		face = (*face_iter);

		if(face->getClassification()->getAttribute("J")!=NO_ATTRIB){
			vector<Node*> nodes = face->getNodes();
			int nen = nodes.size();

			ShapeFunction* sf;

			if(face->numEdges()==3){ //triangle
				if(nen==3){ //1st order triangle
					sf = new LinTriSF(face);
				}else if(nen==6){ //2nd order triangle
					sf = new QuadTriSF(face);
				}
			}else if(face->numEdges()==4){ //quad
				if(nen==4){ //1st order quad
					sf = new LinQuadSF(face);
				}else if(nen==9){ //2nd order quad
					sf = new QuadQuadSF(face);
				}else{
					cerr << "Unknown element type!" << endl;
				}
			}else{ //dunno
				cerr << "Uknown element type!" << endl;
				exit(1);
			}

			Mapping* mapping = new Mapping2D(face, sf);

			double J = face->getClassification()->getAttribute("J");
			int wdg_num = face->getClassification()->getAttribute("wdg_num");
			int section_num = face->getClassification()->getAttribute("section_num");
			Winding^ winding = windings[wdg_num];
			Section^ section = winding->sections[section_num];
						
			vector<point> IntPt = sf->IntPts();
			Vector Weight = sf->Weights();
			int numIntPts = sf->numIntPts();

			for(int i=0; i<numIntPts; i++){
				point pt = IntPt[i];
				Vector N = sf->N(pt);
				double weight = Weight[i];
				double r = 0;
				double A = 0;
				for(int n=0;n<nen;n++){
					DOFs = nodes[n]->getDOFs();
					double An = DOFs[0]->get_value();
					r = r + nodes[n]->x() * N[n];
					A = A + An * N[n];
				}
				W = W + 2 * PI * r * A * J * mapping->detJacobian(pt) * weight;
				//section->F_r = section->F_r + blah;

			}

			double r0 = nodes[0]->x();
			double r1 = nodes[1]->x();
			double r2 = nodes[2]->x();
			double z0 = nodes[0]->y();
			double z1 = nodes[1]->y();
			double z2 = nodes[2]->y();
			double D = (r1*z2-r2*z1)+(r2*z0-r0*z2)+(r0*z1-r1*z0);
			double A[3];
			double Ac=0;
			double rc=0;
			for(int n=0;n<3;n++){
				DOFs = nodes[n]->getDOFs();
				A[n] = DOFs[0]->get_value();
				Ac = Ac + A[n];
				rc = rc + nodes[n]->x();
			}
			Ac = Ac/3;
			rc = rc/3;
			W_anderson = W_anderson + PI / 2 * J*Ac*rc*D;
		}
	}
	X_pu = 2 * PI * 60 * W / (I_base*I_base);
	CalcF();
};

void Transformer::BuildTurns(){
	for each (Winding^ winding in windings) {
		for each (Section^ section in winding->sections) {
			section->BuildTurns();
		}
	}
}

void Transformer::CalcF(){
	for each (Winding^ winding in windings) {
		for each (Section^ section in winding->sections) {
			double A_at_pt = A((section->radius_inner + section->radius_outer)/2, section->h_abv_yoke + section->height/2);
		}
	}
};

double Transformer::A(double r, double y){
	MeshFace* face;
	vector<MeshFace*>::iterator face_iter;
	vector<DOF*> DOFs;

	for(face_iter=feaMesh->getFirstFace();face_iter!=feaMesh->getLastFace();face_iter++){
		face = (*face_iter);

		if(face->isPtInsideFace(r, y, 0)){
			//calc A at point
			vector<Node*> nodes = face->getNodes();
			int nen = nodes.size();
			return 1;
		}

	}
	
	return 0;
};

void Transformer::contourPlot(){
	MeshFace* face;
	vector<MeshFace*>::iterator face_iter;
	MeshEdge* edge;
	vector<MeshEdge*>::iterator edge_iter;
	vector<DOF*> DOFs;
	Node* node;
	vector<Node*>::iterator node_iter;

	double min = 0;
	double max = 0;

	double xmin = 99999;
	double xmax = 0;
	double ymin = 99999;
	double ymax = 0;

	int numContours = 30;

	//first pass through to get min an max	
	for(node_iter=feaMesh->getFirstNode();node_iter!=feaMesh->getLastNode();++node_iter){
		node = (*node_iter);
		DOFs = node->getDOFs();
		double DOF_value = DOFs[0]->get_value() * 2 * PI * node->x();
		if(DOF_value < min){
			min = DOF_value;
		}
		if(DOF_value > max){
			max = DOF_value;
		}
		if(node->x()<xmin){
			xmin = node->x();
		}
		if(node->x()>xmax){
			xmax = node->x();
		}
		if(node->y()<ymin){
			ymin = node->y();
		}
		if(node->y()>ymax){
			ymax = node->y();
		}

	}

	double pltInterval = (max - min) / (numContours - 1);
	TDAP::frmContourPlot^ plotForm = gcnew TDAP::frmContourPlot();
	plotForm->Show();
	
	for(int i = 0; i < numContours; i++){
		double contLine = min + i * pltInterval;
		for(face_iter=feaMesh->getFirstFace();face_iter!=feaMesh->getLastFace();++face_iter){
			face = (*face_iter);
			float x[2];
			float y[2];
			int pt_idx = 0;
			for(edge_iter=face->getFirstEdge();edge_iter!=face->getLastEdge();++edge_iter){
				edge = (*edge_iter);
				Node* node1 = edge->getVertex(0)->getNodes()[0];
				DOF* dof1 = node1->getDOFs()[0];
				Node* node2 = edge->getVertex(1)->getNodes()[0];
				DOF* dof2 = node2->getDOFs()[0];
				double dof1_value = dof1->get_value() * 2 * PI * node1->x();
				double dof2_value = dof2->get_value() * 2 * PI * node2->x();
				
				if(((dof1_value >= contLine) && (dof2_value < contLine)) || ((dof1_value <= contLine) && (dof2_value > contLine))){
					//draw line
					x[pt_idx] = node1->x() + (node2->x() - node1->x()) * (contLine - dof1_value) / (dof2_value - dof1_value);
					y[pt_idx] = node1->y() + (node2->y() - node1->y()) * (contLine - dof1_value) / (dof2_value - dof1_value);
					pt_idx++;
				}
			}
			if(pt_idx == 2){
				//plotPath->AddLine(x[0], y[0], x[1], y[1]);
				//plotPath->StartFigure();
				plotForm->lines->Add(PointF(x[0], y[0]));
				plotForm->lines->Add(PointF(x[1], y[1]));
			} else {
				//error
				int a = 1;
			}
		}
	}

	for each (Winding^ winding in windings) {
		for each (Section^ section in winding->sections) {
			plotForm->rectangles->Add(RectangleF(section->radius_inner, section->h_abv_yoke, section->radius_outer-section->radius_inner, section->height));
		}
	}

	plotForm->setPhysicalSize(xmin, xmax, ymin, ymax);
	plotForm->drawPlot();
	//plotForm->Show();

};