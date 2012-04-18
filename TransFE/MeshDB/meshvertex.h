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

#ifndef MESHVERTEX_H
#define MESHVERTEX_H

#include "meshentity.h"
#include <vector>
#include <set>
using namespace std;

class MeshEdge;

/// This class represents a mesh vertex. A vertex is the lowest entity in the hierarchy.
/// Each edge is bounded by two vertices.  A vertex does not contain geometric data directly.
/// This information is contained by a node.

class MeshVertex : public MeshEntity {

public:
  
  /// Default constructor.  Currently empty.
  MeshVertex ( ) { }
  
  /// Returns an iterator to the first edge
  vector<MeshEdge*>::iterator getFirstEdge();

  /// Returns an iterator to the last edge
  vector<MeshEdge*>::iterator getLastEdge();
  
  /// Returns the n-th edge
  MeshEdge* getEdge(int n);
  
  /// Adds an edge to the list of adjacent edges
  void addEdge(MeshEdge*);
  
  /// Returns the number of adjacent edges
  int numEdges();
  
  /// Returns a set of the edges that this vertex bounds
  set<MeshEdge*> getEdges();
  
  int get_dimensions() const {
  	return 0;
  }
  
  /// Returns an ordered list of nodes for this vertex
  /// Not much to do here since there is only one node per vertex
  virtual vector<Node*> getNodes();
    
protected:

private:
  /// Indicates that a vertex is 0D
  static const int dimensions = 0;

  /// An STL Vector holding pointers to edges using this vertex (currently unordered)
  vector<MeshEdge*> MeshEdges;

};
#endif //MESHVERTEX_H

