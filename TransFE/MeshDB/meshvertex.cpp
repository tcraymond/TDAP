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

#include "meshvertex.h"
#include "meshedge.h"

void MeshVertex::addEdge(MeshEdge* new_edge){
	MeshEdges.push_back(new_edge); //should be ordered CCW
}

vector<MeshEdge*>::iterator MeshVertex::getFirstEdge() {
     return MeshEdges.begin();
}

vector<MeshEdge*>::iterator MeshVertex::getLastEdge() {
     return MeshEdges.end();
}

MeshEdge* MeshVertex::getEdge(int n){
     return MeshEdges[n];
}

int MeshVertex::numEdges(){
     return MeshEdges.size();
}

set<MeshEdge*> MeshVertex::getEdges(){
   set<MeshEdge*> return_set;
   vector<MeshEdge*>::iterator use_iter;
      for(use_iter=getFirstEdge();use_iter!=getLastEdge();++use_iter){
         MeshEdge* newedge = (*use_iter);
	 return_set.insert(newedge);
      }
   return return_set;
}

vector<Node*> MeshVertex::getNodes(){
   vector<Node*> nodes;
   nodes.push_back(this->node);
   return nodes;
}

