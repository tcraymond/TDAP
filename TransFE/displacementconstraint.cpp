/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
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
