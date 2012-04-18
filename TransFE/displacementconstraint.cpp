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

#include "displacementconstraint.h"

DisplacementConstraint::~DisplacementConstraint(){
	
};

void DisplacementConstraint::apply(){
   vector<Node*> nodes = entity->getNodes();
   vector<Node*>::iterator node_iter;
   vector<DOF*> DOFs;
      
   if(entity->getClassification()->getAttribute("x_constraint")!=NO_ATTRIB){  //x component is constrained
      double x_constraint = entity->getClassification()->getAttribute("x_constraint");
      
      for(node_iter=nodes.begin();node_iter!=nodes.end();++node_iter){
         DOFs = (*node_iter)->getDOFs();
         if(DOFs.size()>0){
            //if(x_constraint == 0){  //zero essential BC
            //   DOFs[0]->set_status(DOF_Zero);
            //   DOFs[0]->set_value(0);
            //} else {  //non-zero essential BC
               DOFs[0]->set_status(DOF_Fixed);
               DOFs[0]->set_value(x_constraint);
            //}
         }else{
            cerr << "Tried to access unitialized DOFs!" << endl;
            exit(1);
         }
      }
   }
   if(entity->getClassification()->getAttribute("y_constraint")!=NO_ATTRIB){ //y component is constrained
      double y_constraint = entity->getClassification()->getAttribute("y_constraint");
      for(node_iter=nodes.begin();node_iter!=nodes.end();++node_iter){
         DOFs = (*node_iter)->getDOFs();
         if(y_constraint == 0){  //zero essential BC
	    DOFs[1]->set_status(DOF_Zero);
	    DOFs[1]->set_value(0);
	 } else {  //non-zero essential BC
	    DOFs[1]->set_status(DOF_Fixed);
	    DOFs[1]->set_value(y_constraint);
	 }
      }
   }
   if(entity->getClassification()->getAttribute("z_constraint")!=NO_ATTRIB){ //y component is constrained
      double y_constraint = entity->getClassification()->getAttribute("z_constraint");
      for(node_iter=nodes.begin();node_iter!=nodes.end();++node_iter){
         DOFs = (*node_iter)->getDOFs();
         if(y_constraint == 0){  //zero essential BC
	    DOFs[2]->set_status(DOF_Zero);
	    DOFs[2]->set_value(0);
	 } else {  //non-zero essential BC
	    DOFs[2]->set_status(DOF_Fixed);
	    DOFs[2]->set_value(y_constraint);
	 }
      }
   }
};
