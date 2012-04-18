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

#include "meshedge.h"
#include "meshvertex.h"
#include "meshface.h"

MeshVertex * MeshEdge::getVertex(int n) {
     return MeshVertexes[n];
}

vector<MeshFace*>::iterator MeshEdge::getFirstFace() {
     return MeshFaces.begin();
}

vector<MeshFace*>::iterator MeshEdge::getLastFace() {
     return MeshFaces.end();
}

MeshFace* MeshEdge::getFace(int n) {
     return MeshFaces[n];
}

void MeshEdge::addVertex(MeshVertex * new_vertex, int n){
     MeshVertexes[n] = new_vertex;
}

void MeshEdge::addFace(MeshFace * new_face){
     MeshFaces.push_back(new_face);
}

set<MeshFace*> MeshEdge::getFaces(){
   set<MeshFace*> return_set;
   vector<MeshFace*>::iterator use_iter;
     for(use_iter=getFirstFace();use_iter!=getLastFace();++use_iter){
         MeshFace* newface = (*use_iter);
	 return_set.insert(newface);
      }
   return return_set;
}

MeshVertex* MeshEdge::otherVertex(MeshVertex* vertex){
   if(vertex==MeshVertexes[0]){
      return MeshVertexes[1];
   }else{
      return MeshVertexes[0];
   }
}

bool MeshEdge::isConnected(MeshEdge* edge){
   if(edge->getVertex(0)==MeshVertexes[0] || edge->getVertex(0)==MeshVertexes[1]
   || edge->getVertex(1)==MeshVertexes[0] || edge->getVertex(1)==MeshVertexes[1]){
      return true;
   }else{
      return false;
   }
}

bool MeshEdge::isConnected(MeshVertex* vertex){
   if(MeshVertexes[0]==vertex || MeshVertexes[1]==vertex){
      return true;
   }else{
      return false;
   }
}

vector<Node*> MeshEdge::getNodes(){
   vector<Node*> nodes;
   
   for(int i=0;i<2;i++){
      nodes.push_back(this->getVertex(i)->node);
   }
   if(this->node != NULL){
      nodes.push_back(this->node);
   }
   return nodes;
}
