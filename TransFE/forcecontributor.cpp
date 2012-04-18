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
