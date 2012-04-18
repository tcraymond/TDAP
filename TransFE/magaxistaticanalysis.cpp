/***************************************************************************
 *   Copyright (c) 2012 by Timothy C. Raymond                              *
 *   tc.raymond@ieee.org												   *
 *   All rights reserved.												   *
 *                                                                         *
 *   Redistribution and use in source and binary forms, with or without    *
 *   modification, are permitted provided that the following conditions    *
 *   are met:                                                              *
 *      - Redistributions of source code must retain the above copyright   *
 *        notice, this list of conditions and the following disclaimer.    *
 *      - Redistributions in binary form must reproduce the above          *
 *        copyright notice, this list of conditions and the following      *
 *		  disclaimer in the documentation and/or other materials provided  *
 *		  with the distribution.                                           *
 *                                                                         *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS     *
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  *
 *   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
 *   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      *
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      *
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT    *
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN     *
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
 *   POSSIBILITY OF SUCH DAMAGE.                                           *
 *                                                                         *
 ***************************************************************************/

#include "magaxistaticanalysis.h"
#include "mapping2d.h"
#include "mapping2daxi.h"
#include "mapping1d2d.h"
#include "lintrisf.h"
#include "quadtrisf.h"
#include "linquadsf.h"
#include "quadquadsf.h"
#include "lin1dsf.h"
#include "quad1dsf.h"

#include "precisiontimer.h"

#define PI 3.141592653589793238512808959406186204433

//#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1 

MagAxiStaticAnalysis::MagAxiStaticAnalysis(int form)
{
	if(ndof!=0){
		//WARNING: Indicates previous calculation was not properly destroyed!
		ndof=0;
	}
	formulation=form;
}


MagAxiStaticAnalysis::~MagAxiStaticAnalysis()
{
}

StiffnessContributor* MagAxiStaticAnalysis::makeStiffContrib(MeshFace* face){
	//Note: StiffnessContributor will own the ShapeFunction and Mapping objects created here
   int nen = face->getNodes().size();  //inefficient...
   ShapeFunction* sf;
   if(face->numEdges()==3){  //triangle
      if(nen==3){ //1st order triangle
         sf = new LinTriSF(face);
      }else if(nen==6){ //2nd order triangle
         sf = new QuadTriSF(face);
      }else{
         cerr << "Unknown element type!" << endl;
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
      cerr << "Unknown element type!" << endl;
      exit(1);
   }
   Mapping* mapping;
   if(formulation==2){
		mapping = new Mapping2DAxi(face, sf);
	}else{
		mapping = new Mapping2D(face, sf);
	}
	return new MagAxiStaticSC(face, mapping, sf, formulation);
};

ForceContributor* MagAxiStaticAnalysis::makeForceContrib(MeshFace* face){
   if(face->getClassification()->getAttribute("J")!=NO_ATTRIB){
      int nen = face->getNodes().size();  //inefficient...
      ShapeFunction* sf;
      if(face->numEdges()==3){  //triangle
         if(nen==3){ //1st order triangle
            sf = new LinTriSF(face);
         }else if(nen==6){ //2nd order triangle
            sf = new QuadTriSF(face);
         }else{
            cerr << "Unknown element type!" << endl;
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
         cerr << "Unknown element type!" << endl;
         exit(1);
      }
	  Mapping* mapping;
	  if(formulation == 2){
		mapping = new Mapping2DAxi(face, sf);
	  }else{
		mapping = new Mapping2D(face, sf);
	  }

      return new MagAxiStaticFC(face, mapping, sf, formulation);
   }
   return NULL;
};

ForceContributor* MagAxiStaticAnalysis::makeForceContrib(MeshEdge* edge){
   return NULL;
};

Constraint* MagAxiStaticAnalysis::makeConstraint(MeshEdge* edge){
   if(edge->getClassification()->getAttribute("x_constraint")!=NO_ATTRIB || edge->getClassification()->getAttribute("y_constraint")!=NO_ATTRIB){
      DisplacementConstraint* new_constraint = new DisplacementConstraint(edge);
      //cout << "Adding constraint for edge #" << edge->ID << endl;
      return new_constraint;
   }
   return NULL;
};

Constraint* MagAxiStaticAnalysis::makeConstraint(MeshVertex* vertex){
   if(vertex->getClassification()->getAttribute("x_constraint")!=NO_ATTRIB || vertex->getClassification()->getAttribute("y_constraint")!=NO_ATTRIB){
      DisplacementConstraint* new_constraint = new DisplacementConstraint(vertex);
      //cout << "Adding constraint for edge #" << vertex->ID << endl;
      return new_constraint;
   }
   return NULL;
};

void MagAxiStaticAnalysis::solve(){
   LinearSystemAssembler assembler;
   AlgebraicSystem AS(&DS, &assembler, &theMesh);
   AS.solve();

   //get vector of nodal displacements from AlgebraicSystem
   BigVector d = AS.get_d();
   //assign nodal displacements to DOF value
   vector<Node*>::iterator node_iter;
   vector<DOF*> DOFs;
   vector<DOF*>::iterator DOF_iter;

   for(node_iter=theMesh.getFirstNode();node_iter!=theMesh.getLastNode();++node_iter){
      DOFs = (*node_iter)->getDOFs();
      for(DOF_iter=DOFs.begin(); DOF_iter!=DOFs.end(); ++DOF_iter){
         if((*DOF_iter)->get_status() == DOF_Free){
			 if(formulation==0){
				(*DOF_iter)->set_value(d[(*DOF_iter)->get_eqnumber()]);// * 2 * PI * (*node_iter)->x());
			 }else if(formulation==1){
				(*DOF_iter)->set_value(d[(*DOF_iter)->get_eqnumber()] * sqrt((*node_iter)->x()));
			 }else{
				(*DOF_iter)->set_value(d[(*DOF_iter)->get_eqnumber()] / (*node_iter)->x());
			 }
         }
      }
   }
};

void MagAxiStaticAnalysis::recover(){
	
#ifdef recover
	MeshFace* face;
	vector<MeshFace*>::iterator face_iter;
	vector<DOF*> DOFs;
	double W=0;
/*
	B = Vector(theMesh->numNodes()*2);

	double W = 0;
    
	int nnd = 2;
	//calculate flux density (curl A)
*/
	for(face_iter=theMesh->getFirstFace();face_iter!=theMesh->getLastFace();face_iter++){
		face = (*face_iter);
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
/*
		Matrix B_n(2, nen);
      
		vector<double> A_n(nen);
		vector<double> stress_n(nnd);

		for(int n=0;n<nen;n++){
			DOFs = nodes[n]->getDOFs();
			A_n[n] = DOFs[0]->get_value();
		}

		for(int i=0;i<nen;i++){
			
			point pt = nodes[i]->pt();

			Vector N = sf->N(pt);
			double r = 0;

			for(int n=0;n<nen;n++){
				DOFs = nodes[n]->getDOFs();
				A_n[n] = DOFs[0]->get_value();
				r = r + nodes[n]->x() * N[n];
			}
			//Unlike Na, dNads at x!=a is not 0! (ie. the derivate at a node is a function of the other nodal values).
			//Therefore, B at a node must be evaluated using all nodal values (and hence another loop)
			Matrix dNds = sf->dNds(pt);
			Matrix dsdx = mapping->jacobianInverse(pt);
			Matrix dNdx = dNds * dsdx;
			
			double B_r = 0;
			double B_z = 0;

			for(int n=0;n<nen;n++){
				B_r = B_r + A_n[n] * dNdx[n][1];
				B_z = B_z + A_n[n] * (dNdx[n][0] + N[n]/r);
			}

			B[(nodes[i]->ID-1)*2] = B_r;
			B[(nodes[i]->ID-1)*2+1] = B_z;

		}
*/
		if(face->getClassification()->getAttribute("J")!=NO_ATTRIB){
			double J = face->getClassification()->getAttribute("J");
			int nen = face->getNodes().size();  //inefficient...
			
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
			}
/*
			W=0;

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
			W = W + J*Ac*rc*D;
			*/
		}
	}
	double X_pu = PI * 60 * W / 3600;
#endif
};
   
void MagAxiStaticAnalysis::saveOut(const char* filename){
   vector<MeshFace*>::iterator face_iter;
   vector<DOF*> DOFs;

   //output to file for viewing in gmsh
   ofstream outFile;

   //output to file for viewing in gmsh
   char stressfile[256];
   strcpy(stressfile, filename);
   strcat(stressfile, "_fluxdensity.pos");
   outFile.open(stressfile, ios::out);

   outFile << "View \"output\" {" << endl;
   //vector<MeshFace*>::iterator face_iter;
   for(face_iter=theMesh.getFirstFace();face_iter!=theMesh.getLastFace();++face_iter){
      vector<MeshVertex*>::iterator vertex_iter;
      vector<MeshVertex*> vertexes = (*face_iter)->getVertexes();
      if(vertexes.size()==3){
         outFile << "VT (";
      }else{
         outFile << "VQ (";
      }
      for(vertex_iter=vertexes.begin();vertex_iter!=vertexes.end();++vertex_iter){
         outFile << (*vertex_iter)->node->x() << "," << (*vertex_iter)->node->y() << "," << (*vertex_iter)->node->z();
         if((*vertex_iter)!=vertexes.back()){
            outFile << ",";
         }
      }
      outFile << "){";
      for(vertex_iter=vertexes.begin();vertex_iter!=vertexes.end();++vertex_iter){
//         outFile << B[((*vertex_iter)->node->ID-1)*2] << "," << B[((*vertex_iter)->node->ID-1)*2+1] << "," << 0;
         if((*vertex_iter)!=vertexes.back()){
            outFile << ",";
         }
      }
      outFile << "};" << endl;
   }
   outFile << "};" << endl;
   outFile.close();  
   
   //output to file for viewing in gmsh
   char dispfile[256];
   strcpy(dispfile, filename);
   strcat(dispfile, "_mvp.pos");
   outFile.open(dispfile, ios::out);

   outFile << "View \"output\" {" << endl;
   //vector<Node*>::iterator node_iter;
   for(face_iter=theMesh.getFirstFace();face_iter!=theMesh.getLastFace();++face_iter){
      vector<MeshVertex*>::iterator vertex_iter;
      vector<MeshVertex*> vertexes = (*face_iter)->getVertexes();
      if(vertexes.size()==3){
         outFile << "ST (";
      }else{
         outFile << "SQ (";
      }
      for(vertex_iter=vertexes.begin();vertex_iter!=vertexes.end();++vertex_iter){
         outFile << (*vertex_iter)->node->x() << "," << (*vertex_iter)->node->y() << "," << (*vertex_iter)->node->z();
         if((*vertex_iter)!=vertexes.back()){
            outFile << ",";
         }
      }
      outFile << "){";
      for(vertex_iter=vertexes.begin();vertex_iter!=vertexes.end();++vertex_iter){
         DOFs = (*vertex_iter)->node->getDOFs();
         outFile << DOFs[0]->get_value();
		 //outFile << DOFs[0]->get_value();
         if((*vertex_iter)!=vertexes.back()){
            outFile << ",";
         }
      }
      outFile << "};" << endl;
   }
   outFile << "};" << endl;
   outFile.close();
};