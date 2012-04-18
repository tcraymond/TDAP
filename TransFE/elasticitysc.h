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
