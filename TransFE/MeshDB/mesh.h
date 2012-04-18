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

#ifndef MESH_H
#define MESH_H
#include "meshregion.h"
#include "meshface.h"
#include "meshedge.h"
#include "meshvertex.h"
#include "node.h"
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <map>

using namespace std;

/// This class acts as a container for all of the mesh data structures
/// and functions.  Lists of each mesh entity type (regions, faces, etc.)
/// are kept here.  New entities are first added here and then connected
/// by adding adjacency information to the approriate entities.
 
class Mesh {

public:
  
  /// Mesh class constructor.  Currently empty.
  Mesh ( ) {
   //add blank GeomEntity for entities with no "physical" attributes
   GeomEntity* new_entity = new GeomEntity();
   GeomEntities[0]=new_entity;
  }

  Mesh(const Mesh&);

  ~Mesh();
  
  /// Adds new MeshRegion, both allocating memory and adding it to the master list of 
  /// regions
  MeshRegion * newRegion ();
  
  /// Adds new MeshFace, both allocating memory and adding it to the master list of faces
  MeshFace * newFace ();
  
  /// Adds new MeshEdge, both allocating memory and adding it to the master list of edges
  MeshEdge * newEdge ();
  
  /// Adds new MeshVertex, both allocating memory and adding it to the master list of 
  /// vertices
  MeshVertex * newVertex ();
  
  /// Adds new Node, both allocating memory and adding it to the master list of nodes
  Node * newNode ();
  
  /// Gets the MeshRegion corresponding to n in the master list of regions
  MeshRegion * getRegion(int n);
  
  /// Gets the n-th MeshFace in the master list of faces
  MeshFace * getFace(int n);
  
  /// Gets the n-th MeshEdge in the master list of regions
  MeshEdge * getEdge(int n);
  
  /// Gets the n-th MeshVertex in the master list of vertices
  MeshVertex * getVertex(int n);
  
  /// Gets the n-th Node in the master list of nodes
  Node * getNode(int n);
  
  /// Returns an iterator corresponding to the first MeshRegion in the master list of 
  /// regions
  vector<MeshRegion*>::iterator getFirstRegion();

   vector<MeshRegion*>::iterator getLastRegion();
  
  /// Returns an iterator corresponding to the first MeshFace in the master list of faces
  vector<MeshFace*>::iterator getFirstFace();
  
  /// Returns an iterator corresponding to the last MeshFace in the master list of faces 
  /// (may be after last face)
  vector<MeshFace*>::iterator getLastFace();
  
  /// Returns an iterator corresponding to the first MeshEdge in the master list of edges
  vector<MeshEdge*>::iterator getFirstEdge();

   vector<MeshEdge*>::iterator getLastEdge();
  
  /// Returns an iterator corresponding to the first MeshVertex in the master list of 
  /// vertices
  vector<MeshVertex*>::iterator getFirstVertex();
  
  /// Returns an iterator corresponding to the last MeshRegion in the master list of 
  /// vertices
  vector<MeshVertex*>::iterator getLastVertex();
  
  /// Returns an iterator corresponding to the first Node in the master list of nodes
  vector<Node*>::iterator getFirstNode();

  /// Returns an iterator corresponding to the last Node in the master list of nodes  
  vector<Node*>::iterator getLastNode();

   int numRegions();
  
  /// Returns the total number of faces in this mesh
  int numFaces();
  
  /// Returns the total number of edges in this mesh
  int numEdges();
  
  /// Returns the total number of vertices in this mesh
  int numVertexes();
  
  /// Returns the total number of nodes in this mesh
  int numNodes();
  
  /// a Reverse Cuthill-McKee reordering algorithm
  void reorder();

  void reorder2();
  
  /// Outputs the mesh in OpenDX format
  void exportDX(string);
  
  /// Reads a GMSH file (version 2.0)
  void readMesh(const char* meshfile);
  
  /// Reads an attribute file (.att)
  void readAttributes(const char* attribfile);
  
  /// An aborted attempt at dumping the mesh information to a file...
  friend ostream& operator<<(ostream &os, const Mesh&);
    
protected:
  
private:
  ///  Master list of pointers to all MeshRegions in this mesh
  vector<MeshRegion*> MeshRegions;
  
  ///  Master list of pointers to all MeshFaces in this mesh
  vector<MeshFace*> MeshFaces;
  
  ///  Master list of pointers to all MeshEdges in this mesh
  vector<MeshEdge*> MeshEdges;
  
  ///  Master list of pointers to all MeshVertexes in this mesh
  vector<MeshVertex*> MeshVertexes;
  
  ///  Master list of pointers to all Nodes in this mesh
  vector<Node*> Nodes;
  
  /// Master list of GeomEntities in this mesh (don't remember why I used map here)
  map<int, GeomEntity*> GeomEntities;
  
  /// Retrieves the start entity for the reordering algorithm
  MeshEntity* getStart();
  
  /// Find a vertex by a Node ID
  MeshVertex* findVertexbyNode(int n);
  
  /// Find an edge by it's vertexes
  MeshEdge* findEdgebyVertexes(MeshVertex* vertex1, MeshVertex* vertex2);

  pair<MeshFace*, bool> findFacebyEdge(MeshEdge* edge1, MeshEdge* edge2, MeshEdge* edge3);
  
  /// Find a node by its ID
  Node* findNodebyID(int n);
  
};
#endif //MESH_H

