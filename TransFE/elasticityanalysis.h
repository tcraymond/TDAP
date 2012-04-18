/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
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
