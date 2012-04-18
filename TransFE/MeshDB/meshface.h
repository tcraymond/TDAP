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

#ifndef MESHFACE_H
#define MESHFACE_H

#include "meshentity.h"
#include "meshvertex.h"
#include <vector>

using namespace std;

class MeshEdge;
class MeshRegion;

/// This class represents a mesh face.  A mesh face is a 2D object bounded by edges.
/// A mesh face bounds mesh regions. This class is derived from MeshEntity.
/// Note that adjacencies are stored using a one-level representation.

class MeshFace : public MeshEntity {

public:
  
  /// Default constructor.  Currently empty.
  MeshFace ( ) { }
  
  /// Returns an iterator for the first edge
  vector<MeshEdge*>::iterator getFirstEdge();
  
  /// Returns an iterator for the last edge
  vector<MeshEdge*>::iterator getLastEdge();
  
  /// Returns the n-th edge bounding this face (unordered)
  MeshEdge* getEdge(int n);
  
  /// Returns the n-th region that this face bounds (unordered)
  MeshRegion* getRegion(int n);
  
  /// Adds an edge to the list of adjacent edges
  void addEdge(MeshEdge * new_edge);
  
  /// Adds a region to the list of adjacent regions
  void addRegion(MeshRegion * new_region);
  
  /// Returns the number of edges bounding this face
  int numEdges();
  
  /// Returns the area of the face
  double area();
  
  int get_dimensions() const {
  	return 2;
  }
  
  /// Get an ordered listing of the nodes
  /// vertex nodes 1st, edge nodes 2nd, face node last
  virtual vector<Node*> getNodes();

  /// Get an ordered listing of the face vertexes (CCW)
  vector<MeshVertex*> getVertexes();

  bool isPtInsideFace(double x, double y, double z);
    
protected:

private:

   /// indicates that faces are 2D objects
   static const int dimensions = 2;
   
   //Containers for adjacency information (via pointers)
   /// List of edges attached to this face (currently unordered)
   vector<MeshEdge*> MeshEdges;
   
   /// Always 2 regions per face, one on each side
   vector<MeshRegion*> MeshRegions;

};
#endif //MESHFACE_H

