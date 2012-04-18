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
