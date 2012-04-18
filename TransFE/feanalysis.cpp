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

#include "feanalysis.h"
#include "discretesystem.h"
#include "precisiontimer.h"

FEAnalysis::FEAnalysis(){
	//theMesh = new Mesh();
	//DS = new DiscreteSystem();
};

FEAnalysis::~FEAnalysis(){
	//delete theMesh;
	//delete DS;
};

Mesh* FEAnalysis::getMesh(){
   return &theMesh;
};

void FEAnalysis::run(){
   setup(); //determine the contributors
   solve(); //process the contributors to determine the system
            //perform integrations over contributors, assemble and solve system
   recover(); //recover secondary variables
};

void FEAnalysis::setup(){
   int i;
   StiffnessContributor* sc;
   ForceContributor* fc;
   Constraint* c;
   
   for(i=0;i<theMesh.numRegions();i++){
      MeshRegion* r = theMesh.getRegion(i);
      
      sc = makeStiffContrib(r);
      if(sc!=NULL){
         DS.add(sc);
      }
      fc = makeForceContrib(r);
      if(fc!=NULL){
         DS.add(fc);
      }
   }

   for(i=0;i<theMesh.numFaces();i++){ //process all the mesh faces
      //cout << "Processing face #" << i << endl;
      MeshFace* f = theMesh.getFace(i); //get face object
      sc = makeStiffContrib(f); //set-up type of stiffness contributor for the face
      if(sc!=NULL){
         DS.add(sc);
      }
      fc = makeForceContrib(f); //set-up force contributor for the face
      if(fc!=NULL){ //check if the face contributes to the force vector
         DS.add(fc); //if so, add the face to the list of force contributors
      }
      c = makeConstraint(f); //setup contraint for the edge
      if(c!=NULL){ //check if the edge is constrained
         DS.add(c); //if so, add the edge to the list of constraints
      }
   }

   for(i=0;i<theMesh.numEdges();i++){ //process all mesh edges
      MeshEdge* e = theMesh.getEdge(i); //get edge object
      //cout << "Processing edge #" << i << "(" << e->ID << ")" << endl;
      fc = makeForceContrib(e); //setup force contributor for the edge
      if(fc!=NULL){ //check if the edge contributes to the force vector
         DS.add(fc); //if so, add the edge to the list of force contributors
      }
      c = makeConstraint(e); //setup contraint for the edge
      if(c!=NULL){ //check if the edge is constrained
         DS.add(c); //if so, add the edge to the list of constraints
      }
   }
   for(i=0;i<theMesh.numVertexes();i++){ //process all mesh vertexes
      MeshVertex* v = theMesh.getVertex(i); //get vertex object
      //cout << "Processing vertex #" << i << "(" << v->ID << ")" << endl;
      c = makeConstraint(v); //create a constraint for the vertex
      if(c!=NULL){ //check if the vertex is contrained
         DS.add(c); //if so, add the vertex to the list of constraints
      }
   }
};