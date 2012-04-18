/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#ifndef STIFFNESSCONTRIBUTOR_H
#define STIFFNESSCONTRIBUTOR_H

#include <vector>
#include "MeshDB/meshentity.h"
#include "mapping.h"
#include "shapefunction.h"
#include "assembler.h"
#include "typedefs.h" //Matrix, Vector, etc.
#include "MeshDB/point.h"

class StiffnessContributor{
public:
    StiffnessContributor(MeshEntity* Element_in, Mapping* Map_in, ShapeFunction* SF_in){
       Element = Element_in;
       Map = Map_in;
       SF = SF_in;
       nen = Element->getNodes().size();
    };

    ~StiffnessContributor();
    
    void evaluate(Assembler*);
    
    virtual Matrix evaluatePt(point) = 0;
    
    vector<DOF*> getDOFs();
    
protected:
   MeshEntity* Element;
   Mapping* Map;
   ShapeFunction* SF;
   Matrix dsdx;
   Matrix dNdx;
   int nnd; // # of DOFs/node - must be set by derived class
   int nen; // # of nodes/element

};

#endif
