/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#include "stiffnesscontributor.h"
#include "precisiontimer.h"

StiffnessContributor::~StiffnessContributor(){
	//delete Element;
	delete Map;
	delete SF;
}

void StiffnessContributor::evaluate(Assembler* assem){
   vector<DOF*> DOFs = getDOFs();  //70us
   Matrix k(DOFs.size(), DOFs.size()); //10-20us
   vector<point> IntPt = SF->IntPts();
   Vector Weight = SF->Weights();
   int numIntPts = SF->numIntPts();
   
   //The majority of the time here is spent in evaluatePt
   for(int i=0; i<numIntPts; i++){
      point pt = IntPt[i];
      double weight = Weight[i];

	  Matrix dNds = SF->dNds(pt);
	  Matrix dXds = Map->dXds(pt);

	  dsdx = dXds.inv();
	  dNdx = dNds * dsdx;
		//approx. 830us
      k = k + evaluatePt(pt) * dXds.det() * weight; //Map->detJacobian(pt) * weight;
   }
   
   assem->accept(k,DOFs);
};

vector<DOF*> StiffnessContributor::getDOFs(){
   vector<Node*> nodes = Element->getNodes();
   vector<Node*>::iterator node_iter;
   vector<DOF*> node_DOFs;
   vector<DOF*>::iterator DOF_iter;
   vector<DOF*> DOFs;
   
   for(node_iter=nodes.begin();node_iter!=nodes.end();++node_iter){
      node_DOFs=(*node_iter)->getDOFs();
      for(DOF_iter=node_DOFs.begin();DOF_iter!=node_DOFs.end();++DOF_iter){
         DOFs.push_back((*DOF_iter));
      }
   }
   
   return DOFs;
}


