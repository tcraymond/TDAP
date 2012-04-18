/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
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

