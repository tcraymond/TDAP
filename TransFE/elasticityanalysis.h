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

#ifndef ELASTICITYANALYSIS_H
#define ELASTICITYANALYSIS_H

#include "feanalysis.h"
#include "elasticitysc.h"
#include "elasticityfc.h"
#include "displacementconstraint.h"
#include "linearsystemassembler.h"
#include "algebraicsystem.h"

class ElasticityAnalysis : public FEAnalysis{
public:
   ElasticityAnalysis();

   virtual ~ElasticityAnalysis();
   
   virtual void solve();
    
   virtual void recover(); //recover them all important secondary variables
   
   virtual StiffnessContributor* makeStiffContrib(MeshFace* face); //face "element" stiffness
   virtual StiffnessContributor* makeStiffContrib(MeshRegion* region){return NULL;};
   virtual ForceContributor* makeForceContrib(MeshRegion* region){return NULL;};
   virtual ForceContributor* makeForceContrib(MeshFace* face); //face body force
   virtual ForceContributor* makeForceContrib(MeshEdge* edge); //edge forces
   virtual Constraint* makeConstraint(MeshFace* face){return NULL;};
   virtual Constraint* makeConstraint(MeshEdge* edge);
   virtual Constraint* makeConstraint(MeshVertex* vertex);

   virtual void saveOut(const char* filename);

protected:
   Vector stress;

};

#endif
