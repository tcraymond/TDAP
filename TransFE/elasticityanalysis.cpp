/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#include "elasticityanalysis.h"
#include "mapping2d.h"
#include "mapping1d2d.h"
#include "lintrisf.h"
#include "quadtrisf.h"
#include "linquadsf.h"
#include "quadquadsf.h"
#include "lin1dsf.h"
#include "quad1dsf.h"

ElasticityAnalysis::ElasticityAnalysis()
{
}


ElasticityAnalysis::~ElasticityAnalysis()
{
}

StiffnessContributor* ElasticityAnalysis::makeStiffContrib(MeshFace* face){
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
   Mapping* mapping = new Mapping2D(face, sf);
   return new ElasticitySC(face, mapping, sf);
};

ForceContributor* ElasticityAnalysis::makeForceContrib(MeshFace* face){
   if(face->getClassification()->getAttribute("F_x")!=NO_ATTRIB || face->getClassification()->getAttribute("F_y")!=NO_ATTRIB){
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
      Mapping* mapping = new Mapping2D(face, sf);
      return new ElasticityFC(face, mapping, sf);
   }
   return NULL;
};

ForceContributor* ElasticityAnalysis::makeForceContrib(MeshEdge* edge){
   if(edge->getClassification()->getAttribute("F_x")!=NO_ATTRIB || edge->getClassification()->getAttribute("F_y")!=NO_ATTRIB){
      int nen = edge->getNodes().size();  //inefficient...
      ShapeFunction* sf;
      if(nen==2){ //1st order line
         sf = new Lin1DSF(edge);
      }else if(nen==3){ //2nd order line
         sf = new Quad1DSF(edge);
      }else{
         cerr << "Unknown element type!" << endl;
      }
      Mapping1D2D* mapping = new Mapping1D2D(edge, sf);
      return new ElasticityFC(edge, mapping, sf);
   }
   return NULL;
};

Constraint* ElasticityAnalysis::makeConstraint(MeshEdge* edge){
   if(edge->getClassification()->getAttribute("x_constraint")!=NO_ATTRIB || edge->getClassification()->getAttribute("y_constraint")!=NO_ATTRIB){
      DisplacementConstraint* new_constraint = new DisplacementConstraint(edge);
      //cout << "Adding constraint for edge #" << edge->ID << endl;
      return new_constraint;
   }
   return NULL;
};

Constraint* ElasticityAnalysis::makeConstraint(MeshVertex* vertex){
   if(vertex->getClassification()->getAttribute("x_constraint")!=NO_ATTRIB || vertex->getClassification()->getAttribute("y_constraint")!=NO_ATTRIB){
      DisplacementConstraint* new_constraint = new DisplacementConstraint(vertex);
      //cout << "Adding constraint for edge #" << vertex->ID << endl;
      return new_constraint;
   }
   return NULL;
};

void ElasticityAnalysis::solve(){
   LinearSystemAssembler assembler;
   AlgebraicSystem AS(&DS, &assembler, &theMesh);
   AS.solve();

   //get vector of nodal displacements from AlgebraicSystem
   BigVector d = AS.get_d();
   //assign nodal displacements to DOF value
   vector<Node*>::iterator node_iter;
   vector<DOF*> DOFs;
   vector<DOF*>::iterator DOF_iter;

   for(node_iter=theMesh.getFirstNode();node_iter!=theMesh.getLastNode();node_iter++){
      DOFs = (*node_iter)->getDOFs();
      for(DOF_iter=DOFs.begin(); DOF_iter!=DOFs.end(); DOF_iter++){
         if((*DOF_iter)->get_status() == DOF_Free){
            (*DOF_iter)->set_value(d[(*DOF_iter)->get_eqnumber()]);
         }
      }
   }

};

void ElasticityAnalysis::recover(){
   MeshFace* face;
   vector<MeshFace*>::iterator face_iter;
   vector<DOF*> DOFs;

   stress = Vector(theMesh.numNodes()*3);
   
   int nnd = 2;
   //calculate stress
   for(face_iter=theMesh.getFirstFace();face_iter!=theMesh.getLastFace();face_iter++){
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

      Matrix B(3, nen*nnd);
      Matrix D(3,3);
      vector<double> d_n(nen*nnd);
      vector<double> stress_n(nnd);

      double nu = face->getClassification()->getAttribute("nu");
      double E = face->getClassification()->getAttribute("E");

      //Set D for Plane Strain     
      double lambda = nu * E / ((1 + nu) * (1 - 2 * nu));
      double mu = E / (2 * (1 + nu));

      D[0][0] = lambda + 2 * mu;
      D[0][1] = lambda;
      D[0][2] = 0;
      D[1][0] = lambda;
      D[1][1] = lambda + 2 * mu;
      D[1][2] = 0;
      D[2][0] = 0;
      D[2][1] = 0;
      D[2][2] = mu;

      for(int n=0;n<nen;n++){
            DOFs = nodes[n]->getDOFs();
            d_n[2*n] = DOFs[0]->get_value();
            d_n[2*n+1] = DOFs[1]->get_value();
      }

      for(int i=0;i<nen;i++){
         point pt = nodes[i]->pt();
         //Unlike Na, dNads at x!=a is not 0! (ie. the derivate at a node is a function of the other nodal values).
         //Therefore, B at a node must be evaluated using all nodal values (and hence another loop)
         Matrix dNds = sf->dNds(pt);
         Matrix dsdx = mapping->jacobianInverse(pt);
         Matrix dNdx = dNds * dsdx;

         for(int n=0;n<nen;n++){
            B[0][2*n] = dNdx[n][0];
            B[0][2*n+1] = 0;
            B[1][2*n] = 0;
            B[1][2*n+1] = dNdx[n][1];
            B[2][2*n] = dNdx[n][1];
            B[2][2*n+1] = dNdx[n][0];
         }

         stress_n = D * B * d_n;

         for(int j=0; j<3; j++){
            stress[(nodes[i]->ID-1)*3+j] = stress_n[j];
         }
      }
   }
};
   
void ElasticityAnalysis::saveOut(const char* filename){
   vector<MeshFace*>::iterator face_iter;
   vector<DOF*> DOFs;

   //output to file for viewing in gmsh
   ofstream outFile;
   char stressfile[80];
   strcpy(stressfile, filename);
   strcat(stressfile, "_stress.pos");
   outFile.open(stressfile, ios::out);

   outFile << "View \"output\" {" << endl;
   //vector<MeshFace*>::iterator face_iter;
   for(face_iter=theMesh.getFirstFace();face_iter!=theMesh.getLastFace();face_iter++){
      vector<MeshVertex*>::iterator vertex_iter;
      vector<MeshVertex*> vertexes = (*face_iter)->getVertexes();
      if(vertexes.size()==3){
         outFile << "VT (";
      }else{
         outFile << "VQ (";
      }
      for(vertex_iter=vertexes.begin();vertex_iter!=vertexes.end();vertex_iter++){
         outFile << (*vertex_iter)->node->x() << "," << (*vertex_iter)->node->y() << "," << (*vertex_iter)->node->z();
         if((*vertex_iter)!=vertexes.back()){
            outFile << ",";
         }
      }
      outFile << "){";
      for(vertex_iter=vertexes.begin();vertex_iter!=vertexes.end();vertex_iter++){
         outFile << stress[(*vertex_iter)->node->ID*3] << "," << stress[(*vertex_iter)->node->ID*3+1] << "," << stress[(*vertex_iter)->node->ID*3+2];
         if((*vertex_iter)!=vertexes.back()){
            outFile << ",";
         }
      }
      outFile << "};" << endl;
   }
   outFile << "};" << endl;
   outFile.close();  

   //output to file for viewing in gmsh
   char dispfile[80];
   strcpy(dispfile, filename);
   strcat(dispfile, "_disp.pos");
   outFile.open(dispfile, ios::out);

   outFile << "View \"output\" {" << endl;
   //vector<Node*>::iterator node_iter;
   for(face_iter=theMesh.getFirstFace();face_iter!=theMesh.getLastFace();face_iter++){
      vector<MeshVertex*>::iterator vertex_iter;
      vector<MeshVertex*> vertexes = (*face_iter)->getVertexes();
      if(vertexes.size()==3){
         outFile << "VT (";
      }else{
         outFile << "VQ (";
      }
      for(vertex_iter=vertexes.begin();vertex_iter!=vertexes.end();vertex_iter++){
         outFile << (*vertex_iter)->node->x() << "," << (*vertex_iter)->node->y() << "," << (*vertex_iter)->node->z();
         if((*vertex_iter)!=vertexes.back()){
            outFile << ",";
         }
      }
      outFile << "){";
      for(vertex_iter=vertexes.begin();vertex_iter!=vertexes.end();vertex_iter++){
         DOFs = (*vertex_iter)->node->getDOFs();
         outFile << DOFs[0]->get_value() << "," << DOFs[1]->get_value() << "," << 0;
         if((*vertex_iter)!=vertexes.back()){
            outFile << ",";
         }
      }
      outFile << "};" << endl;
   }
   outFile << "};" << endl;
   outFile.close();
};

