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

#ifndef MESHEDGE_H
#define MESHEDGE_H

#include "meshentity.h"
#include <vector>
#include <set>
using namespace std;

class MeshVertex;
class MeshFace;

/// This class represents a mesh edge.  A mesh edge is a 1D object bounded by two
/// vertices.  A mesh edge bounds mesh faces.  This class is derived from MeshEntity.
/// Note that adjacencies are stored using a one-level representation and that use
/// entities are included.

class MeshEdge : public MeshEntity {

public:
  
  /// Default constructor.  Currently empty.
  MeshEdge ( ) { }
  
  /// Returns a pointer to the n-th vertex of this edge (either 0 or 1)
  MeshVertex* getVertex(int n);
  
  /// Returns an iterator to the first face that this edge bounds
  vector<MeshFace*>::iterator getFirstFace();

  /// Returns an iterator to the last face that this edge bounds
  vector<MeshFace*>::iterator getLastFace();
    
  /// Returns a pointer to the n-th face that this edge bounds
  MeshFace* getFace(int n);
  
  /// Adds a vertex to the adjacency information for this edge
  void addVertex(MeshVertex* new_vertex, int n);
  
  /// Adds a face to the adjacency information for this edge (should be deleted)
  void addFace(MeshFace* new_face);
  
  /// Get a list of all mesh faces that this edge bounds
  set<MeshFace*> getFaces();
  
  /// Returns the other vertex for this edge
  MeshVertex* otherVertex(MeshVertex*);
  
  /// Returns whether or not this edge is connected to the given edge
  bool isConnected(MeshEdge*);

  /// Returns whether or not the given vertex bounds this edge
  bool isConnected(MeshVertex*);
  
  int get_dimensions() const {
  	return 1;
  }
  
  /// Returns an ordered list of nodes for this edge
  /// Vertex nodes 1st, edge node 2nd
  virtual vector<Node*> getNodes();
        
protected:
  
private:

   /// Indicates the "level" or dimensions of edges, may be used someday
   static const int dimensions = 1;

   /// A constant-sized array to hold pointers to each vertex of this edge
   MeshVertex* MeshVertexes[2];
   
   /// An STL Vector for holding pointers to Face adjacenecies
   vector<MeshFace*> MeshFaces;
  
};
#endif //MESHEDGE_H

