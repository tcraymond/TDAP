/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#ifndef ELASTICITYSC_H
#define ELASTICITYSC_H

#include "stiffnesscontributor.h"
#include "MeshDB/meshface.h"
#include "mapping.h"
#include "shapefunction.h"
#include "MeshDB/point.h"
#include <vector>
#include "dof.h"
#include "typedefs.h"

class ElasticitySC : public StiffnessContributor{
public:
    ElasticitySC(MeshFace* Element, Mapping* Map, ShapeFunction* SF):StiffnessContributor(Element, Map, SF){
      vector<Node*> nodes = Element->getNodes();
      vector<Node*>::iterator node_iter;
      vector<DOF*> DOFs;
      
      nnd = 2;
      
      for(node_iter=nodes.begin();node_iter!=nodes.end();node_iter++){
         
         DOFs = (*node_iter)->getDOFs();
         if(DOFs.empty()){
            for(int i=0;i<nnd;i++){
               DOF* newDOF = (*node_iter)->newDOF();
               //newDOF->set_eqnumber((*node_iter)->ID*2+i);
            }
         }
      }
    };

    ~ElasticitySC(){};
    
    virtual Matrix evaluatePt(point);
    
private:

};

#endif
