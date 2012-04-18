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


#ifndef FEANALYSIS_H
#define FEANALYSIS_H

#include "MeshDB/meshregion.h"
#include "MeshDB/meshface.h"
#include "MeshDB/meshedge.h"
#include "MeshDB/meshvertex.h"
#include "MeshDB/mesh.h"
#include "discretesystem.h"
#include "stiffnesscontributor.h"
#include "forcecontributor.h"
#include "constraint.h"

//#include <sstream>

/// This class represents a generic finite element analysis.
/// This is the base class for specific finite element analysis implementations
/// For an example implemeentation, refer to ElasticityAnalysis

class FEAnalysis {

public:

   /// Default constructor
   FEAnalysis();

   /// Virtual default destructor
   virtual ~FEAnalysis();  

   /// Runs the analysis steps (setup, solve, recover)
   void run();

   /// Determines which finite element entities are contributors and creates
   /// instances of the appropriate classes
   void setup();
   
   /// Returns a pointer to the mesh
   Mesh* getMesh();
   
   // The following virtual functions must be implemented in each derived analysis class

   /// Processes the contributors to evaluate, assemble and solve
   virtual void solve() = 0;
   
   /// Recover them all important secondary variables
   virtual void recover() = 0;
   
   /// Create the appropriate StiffnessContributor for the face "element"
   virtual StiffnessContributor* makeStiffContrib(MeshFace* face) = 0;

   /// Create the appropriate StiffnessContributor for the face "element"
   virtual StiffnessContributor* makeStiffContrib(MeshRegion* region) = 0;

   virtual ForceContributor* makeForceContrib(MeshRegion* region) = 0;

   /// Create the appropriate ForceContributor for a face body force
   virtual ForceContributor* makeForceContrib(MeshFace* face) = 0;

   /// Create the appropriate ForceContributor for an edge force
   virtual ForceContributor* makeForceContrib(MeshEdge* edge) = 0;

   /// Create the appropriate Constraint for a face
   virtual Constraint* makeConstraint(MeshFace* face) = 0;

   /// Create the appropriate Constraint for an edge
   virtual Constraint* makeConstraint(MeshEdge* edge) = 0;

   /// Create the appropriate Constraint for a vertex
   virtual Constraint* makeConstraint(MeshVertex* vertex) = 0;

   /// For the saving of the output
   virtual void saveOut(const char* filename) = 0;

   //stringstream outStream;
   int formulation;
  
protected:
  
   DiscreteSystem DS;
   Mesh theMesh;

private:

};
#endif //CONSTRAINT_H

