/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#ifndef MAGAXISTATICSC_H
#define MAGAXISTATICSC_H

#include "stiffnesscontributor.h"
#include "MeshDB/meshface.h"
#include "mapping.h"
#include "shapefunction.h"
#include "MeshDB/point.h"
#include <vector>
#include "dof.h"
#include "typedefs.h"

class MagAxiStaticSC : public StiffnessContributor{
public:
    MagAxiStaticSC(MeshFace* Element, Mapping* Map, ShapeFunction* SF, int formul):StiffnessContributor(Element, Map, SF){
      vector<Node*> nodes = Element->getNodes();
      vector<Node*>::iterator node_iter;
      vector<DOF*> DOFs;
      
      //check the region type of this face and set nnd (and dofs) accordingly
      nnd=1; //Only have A component in z-direction

	  formulation = formul;
      
      //create a new DOF for each node
      for(node_iter=nodes.begin();node_iter!=nodes.end();++node_iter){
         
         DOFs = (*node_iter)->getDOFs();
         if(DOFs.size()<nnd){
            for(int i=DOFs.size();i<nnd;i++){
               DOF* newDOF = (*node_iter)->newDOF();
               //newDOF->set_eqnumber((*node_iter)->ID*2+i);
            }
         }
      }
    };

    //~MagAxiStaticSC(){};
    
    virtual Matrix evaluatePt(point);
    
private:
	int formulation;
};

#endif
