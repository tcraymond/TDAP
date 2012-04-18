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

#include "meshregion.h"
#include <iostream>

vector< pair<MeshFace*, bool> >::iterator MeshRegion::getFirstFace() {
     return MeshFaces.begin();
}

vector< pair<MeshFace*, bool> >::iterator MeshRegion::getLastFace() {
     return MeshFaces.end();
}

void MeshRegion::addFace(pair<MeshFace*, bool> new_face){
     MeshFaces.push_back(new_face);
}

vector<Node*> MeshRegion::getNodes(){
   //Ugly kludge to get ordered list of nodes for linear tetrahedron
   //Any other element type will fail miserably
   //FIXME
   
   vector<Node*> nodes;
   vector<Node*> nodes2;
   vector< pair<MeshFace*, bool> >::iterator face_iter = this->getFirstFace();
   vector<Node*>::iterator node_iter;
   vector<Node*>::iterator node_iter2;
   vector<Node*>::reverse_iterator node_riter;
   
   nodes = (*face_iter).first->getNodes();

   if((*face_iter).second == 0){
      vector<Node*> tmp;
      for(node_riter=nodes.rbegin();node_riter!=nodes.rend();++node_riter){
         tmp.push_back((*node_riter));
      }
      nodes = tmp;
   }

   //cout << "nodes.size()=" << nodes.size() << endl;

   //cout << "Nodes in first face" << endl;
   //int i = 0;
   //for(node_iter=nodes.begin();node_iter!=nodes.end();node_iter++){
   //   cout << "Node #" << i << ": x=" << (*node_iter)->pt().X(0) << " y=" << (*node_iter)->pt().X(1) << " z=" << (*node_iter)->pt().X(2) << endl;
   //   i++;
   //}
   
   face_iter++;
   
   nodes2 = (*face_iter).first->getNodes();
   //cout << "nodes2.size()=" << nodes2.size() << endl;

   //cout << "Nodes in second face" << endl;
   //for(int i=0;i<3;i++){
   //   cout << "Node #" << i << ": x=" << nodes2[i]->pt().X(0) << " y=" << nodes2[i]->pt().X(1) << " z=" << nodes2[i]->pt().X(2) << endl;
   //}

   bool node_found = false;

   for(node_iter2=nodes2.begin();node_iter2!=nodes2.end();++node_iter2){ //loop through nodes in second face
      node_found = false;
      for(node_iter=nodes.begin();node_iter!=nodes.end();++node_iter){
         if((*node_iter)==(*node_iter2)){ //check to see if the node in the 2nd face is in the 1st face
            node_found = true;
         }
      }
      if(node_found==false){
         nodes.push_back((*node_iter2));
         //cout << "Nodes in region" << endl;
         //for(int i=0;i<4;i++){
         //   cout << "Node #" << i << ": x=" << nodes[i]->pt().X(0) << " y=" << nodes[i]->pt().X(1) << " z=" << nodes[i]->pt().X(2) << endl;
         //}
         return nodes;
      }
   }
   cerr << "Region contains two identical faces!" << endl;
   exit(1);
}


