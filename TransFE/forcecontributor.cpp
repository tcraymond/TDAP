/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#include "forcecontributor.h"

ForceContributor::~ForceContributor(){
	//delete Element;
	delete Map;
	delete SF;
};

void ForceContributor::evaluate(Assembler* assem){
   vector<DOF*> DOFs = this->getDOFs();
   Vector f(DOFs.size());  //This is a vector of DOFs for either the face or the edge
   vector<point> IntPt = SF->IntPts();
   Vector Weight = SF->Weights();
   int numIntPts = SF->numIntPts();
   
   for(int i=0; i<numIntPts; i++){
      point pt = IntPt[i];
      double weight = Weight[i];
      f = f + evaluatePt(pt) * weight;
   }

   assem->accept(f,DOFs);
};

vector<DOF*> ForceContributor::getDOFs(){
   vector<Node*> nodes = Element->getNodes();
   vector<Node*>::iterator node_iter;
   vector<DOF*> node_DOFs;
   vector<DOF*>::iterator DOF_iter;
   vector<DOF*> DOFs;
   
   for(node_iter=nodes.begin();node_iter!=nodes.end();++node_iter){
      node_DOFs = (*node_iter)->getDOFs();
      for(DOF_iter=node_DOFs.begin();DOF_iter!=node_DOFs.end();++DOF_iter){
         DOFs.push_back((*DOF_iter));
      }
   }
   
   return DOFs;
}
