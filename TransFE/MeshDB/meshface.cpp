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

#include "meshface.h"
#include "meshregion.h"
#include "meshedge.h"
#include "meshvertex.h"
#include "math.h"
#include <iostream>

vector<MeshEdge*>::iterator MeshFace::getFirstEdge() {
     return MeshEdges.begin();
}

vector<MeshEdge*>::iterator MeshFace::getLastEdge() {
     return MeshEdges.end();
}

MeshEdge* MeshFace::getEdge(int n) {
     return MeshEdges[n];
}

MeshRegion* MeshFace::getRegion(int n) {
     return MeshRegions[n];
}

void MeshFace::addEdge(MeshEdge * new_edge) {
     MeshEdges.push_back(new_edge);
}

void MeshFace::addRegion(MeshRegion * new_region) {
     MeshRegions.push_back(new_region);
}

int MeshFace::numEdges() {
     return MeshEdges.size();
}

double MeshFace::area() {
     MeshEdge* firstEdge;
     MeshVertex* firstVertex;
     vector<MeshEdge*>::iterator edge_iter;
     double Area = 0;
     
     edge_iter = getFirstEdge();
     firstEdge = *edge_iter;
     firstVertex = firstEdge->getVertex(0);
     
     for(edge_iter++;edge_iter!=getLastEdge();++edge_iter){
        if(!(*edge_iter)->isConnected(firstVertex)){	   
	   double X1;
	   double X2;
	   double X3;
	   double Y1;
	   double Y2;
	   double Y3;
	     
	   X1 = firstVertex->node->x();
	   X2 = (*edge_iter)->getVertex(0)->node->x();
	   X3 = (*edge_iter)->getVertex(1)->node->x();
	   Y1 = firstVertex->node->y();
	   Y2 = (*edge_iter)->getVertex(0)->node->y();
	   Y3 = (*edge_iter)->getVertex(1)->node->y();
           
	   Area = Area + 0.5 * fabs(X1*(Y3-Y2)+X2*(Y1-Y3)+X3*(Y2-Y1));
	}
     }
     
     return Area;
}

vector<Node*> MeshFace::getNodes(){
   vector<Node*> nodes;
   vector<MeshEdge*>::iterator edge_iter;
   MeshEdge* first_edge;

   //add nodes for each vertex of face first, in order
   //This assumes mesh data structure is already ordered!!!
   edge_iter=getFirstEdge(); //Get first edge;
   first_edge=(*edge_iter);
   ++edge_iter; //Get second edge;
   if((*edge_iter)->getVertex(0)==first_edge->getVertex(0) || (*edge_iter)->getVertex(1)==first_edge->getVertex(0)){
      nodes.push_back(first_edge->getVertex(1)->node);
      nodes.push_back(first_edge->getVertex(0)->node);
   }else{ 
      nodes.push_back(first_edge->getVertex(0)->node);
      nodes.push_back(first_edge->getVertex(1)->node);
   }

   for(/*edge_iter=second edge*/;(*edge_iter)!=MeshEdges.back();++edge_iter){
      if((*edge_iter)->getVertex(0)->node == nodes.back()){
         nodes.push_back((*edge_iter)->getVertex(1)->node);
      }else{
         nodes.push_back((*edge_iter)->getVertex(0)->node);
      }
   }

   //add nodes for all edges (if present) next
   for(edge_iter=getFirstEdge();edge_iter!=getLastEdge();++edge_iter){
      if((*edge_iter)->node != NULL){
         nodes.push_back((*edge_iter)->node);
      }
   }

   //add node in face (if present) last
   if(this->node != NULL){
      nodes.push_back(this->node);
   }

   return nodes;
}

vector<MeshVertex*> MeshFace::getVertexes(){
   vector<MeshVertex*> vertexes;
   vector<MeshEdge*>::iterator edge_iter;
   MeshEdge* first_edge;

   //add nodes for each vertex of face first, in order
   //This assumes mesh data structure is already ordered!!!
   edge_iter=getFirstEdge(); //Get first edge;
   first_edge=(*edge_iter);
   edge_iter++; //Get second edge;
   if((*edge_iter)->getVertex(0)==first_edge->getVertex(0) || (*edge_iter)->getVertex(1)==first_edge->getVertex(0)){
      vertexes.push_back(first_edge->getVertex(1));
      vertexes.push_back(first_edge->getVertex(0));
   }else{ 
      vertexes.push_back(first_edge->getVertex(0));
      vertexes.push_back(first_edge->getVertex(1));
   }

   for(/*edge_iter=second edge*/;(*edge_iter)!=MeshEdges.back();++edge_iter){
      if((*edge_iter)->getVertex(0) == vertexes.back()){
         vertexes.push_back((*edge_iter)->getVertex(1));
      }else{
         vertexes.push_back((*edge_iter)->getVertex(0));
      }
   }

   return vertexes;
}

#define EPSILON  0.0000001
#define MODULUS(p) (sqrt(p.x*p.x + p.y*p.y + p.z*p.z))
#define TWOPI 6.283185307179586476925287
#define RTOD 57.2957795

bool MeshFace::isPtInsideFace(double x, double y, double z)
{
   int i;
   double m1,m2;
   double anglesum=0,costheta;
   point p1,p2;
   vector<Node*> nodes = getNodes();
   int nen = nodes.size();

   for (i=0;i<nen;i++) {

      p1.x = nodes[i]->x() - x;
      p1.y = nodes[i]->y() - y;
      p1.z = nodes[i]->z() - z;
      p2.x = nodes[(i+1)%nen]->x() - x;
      p2.y = nodes[(i+1)%nen]->y() - y;
      p2.z = nodes[(i+1)%nen]->z() - z;

      m1 = MODULUS(p1);
      m2 = MODULUS(p2);
      if (m1*m2 <= EPSILON)
         return(true); /* We are on a node, consider this inside */
      else
         costheta = (p1.x*p2.x + p1.y*p2.y + p1.z*p2.z) / (m1*m2);

      anglesum += acos(costheta);
   }
   if(anglesum <= (TWOPI+EPSILON) && anglesum >= (TWOPI-EPSILON)){
	   return(true);
   }else{
	   return(false);
   }
}
