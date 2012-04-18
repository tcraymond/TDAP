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

#include "mesh.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

//#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1 

Mesh::Mesh(const Mesh& old_mesh){
	MeshRegions.assign(old_mesh.MeshRegions.begin(), old_mesh.MeshRegions.end());
	MeshFaces.assign(old_mesh.MeshFaces.begin(), old_mesh.MeshFaces.end());
    MeshEdges.assign(old_mesh.MeshEdges.begin(), old_mesh.MeshEdges.end());
    MeshVertexes.assign(old_mesh.MeshVertexes.begin(), old_mesh.MeshVertexes.end());
    Nodes.assign(old_mesh.Nodes.begin(), old_mesh.Nodes.end());
	//MeshRegions = old_mesh.MeshRegions;
	//MeshFaces = old_mesh.MeshFaces;
	//MeshEdges = old_mesh.MeshEdges;
	//MeshVertexes = old_mesh.MeshVertexes;
	//Nodes = old_mesh.Nodes;
	GeomEntities = old_mesh.GeomEntities;
}

Mesh::~Mesh(){
	vector<MeshRegion*>::iterator region_iter;
	for(region_iter=MeshRegions.begin();region_iter!=MeshRegions.end();++region_iter){
		delete (*region_iter);
	}

	vector<MeshFace*>::iterator face_iter;
	for(face_iter=MeshFaces.begin();face_iter!=MeshFaces.end();++face_iter){
		delete (*face_iter);
	}

	vector<MeshEdge*>::iterator edge_iter;
	for(edge_iter=MeshEdges.begin();edge_iter!=MeshEdges.end();++edge_iter){
		delete (*edge_iter);
	}

	vector<MeshVertex*>::iterator vertex_iter;
	for(vertex_iter=MeshVertexes.begin();vertex_iter!=MeshVertexes.end();++vertex_iter){
		delete (*vertex_iter);
	}

	vector<Node*>::iterator node_iter;
	for(node_iter=Nodes.begin();node_iter!=Nodes.end();++node_iter){
		delete (*node_iter);
	}
	if(!GeomEntities.empty()){
		map<int, GeomEntity*>::iterator geom_iter;
		for(geom_iter=GeomEntities.begin();geom_iter!=GeomEntities.end();++geom_iter){
			delete (*geom_iter).second;
		}
	}
}

MeshRegion * Mesh::newRegion() {
  MeshRegion* new_region = new MeshRegion();
  MeshRegions.push_back(new_region);
  return MeshRegions.back();
}

MeshFace * Mesh::newFace() {
  MeshFace* new_face = new MeshFace();
  MeshFaces.push_back(new_face);
  return MeshFaces.back();
}

MeshEdge * Mesh::newEdge () {
  MeshEdge* new_edge = new MeshEdge();
  MeshEdges.push_back(new_edge);
  return MeshEdges.back();
}

MeshVertex * Mesh::newVertex () {
  MeshVertex* new_vertex = new MeshVertex();
  MeshVertexes.push_back(new_vertex);
  return MeshVertexes.back();
}

Node * Mesh::newNode() {
  Node* new_node = new Node();
  Nodes.push_back(new_node);
  return Nodes.back();
}

MeshRegion * Mesh::getRegion(int n){
  return MeshRegions[n];
}

MeshFace * Mesh::getFace(int n){
  return MeshFaces[n];
}

MeshEdge * Mesh::getEdge(int n){
  return MeshEdges[n];
}

MeshVertex * Mesh::getVertex(int n){
  return MeshVertexes[n];
}

Node * Mesh::getNode(int n){
  return Nodes[n];
}

vector<MeshRegion*>::iterator Mesh::getFirstRegion() {
     return MeshRegions.begin();
}

vector<MeshRegion*>::iterator Mesh::getLastRegion() {
   return MeshRegions.end();
}

vector<MeshFace*>::iterator Mesh::getFirstFace() {
     return MeshFaces.begin();
}

vector<MeshFace*>::iterator Mesh::getLastFace() {
     return MeshFaces.end();
}

vector<MeshEdge*>::iterator Mesh::getFirstEdge() {
     return MeshEdges.begin();
}

vector<MeshEdge*>::iterator Mesh::getLastEdge() {
   return MeshEdges.end();
}

vector<MeshVertex*>::iterator Mesh::getFirstVertex() {
     return MeshVertexes.begin();
}

vector<MeshVertex*>::iterator Mesh::getLastVertex() {
     return MeshVertexes.end();
}

vector<Node*>::iterator Mesh::getFirstNode() {
     return Nodes.begin();
}

vector<Node*>::iterator Mesh::getLastNode() {
     return Nodes.end();
}

int Mesh::numRegions() {
   return MeshRegions.size();
}

int Mesh::numFaces() {
     return MeshFaces.size();
}

int Mesh::numEdges() {
     return MeshEdges.size();
}

int Mesh::numVertexes() {
     return MeshVertexes.size();
}

int Mesh::numNodes() {
     return Nodes.size();
}

#ifdef MESHSIM
void Mesh::loadMeshSim(pMesh mesh) {
//First pass through mesh to set up objects
  cout << "Allocating mesh objects\n";
  //Loop through the regions and create a new MeshRegion for each
  
  int i=0;
   FIter face_iterator; pFace face;
   face_iterator = M_faceIter(mesh);
   while(face = FIter_next(face_iterator)){
   	EN_setID(face, i);
   	this->newFace();
	this->getFace(i)->setClassification(F_whatIn(face));
	this->getFace(i)->ID=i;
	//cout << "Creating face #" << i << "\n";
	i++;
   }
   FIter_delete(face_iterator);
   
   i=0;
   EIter edge_iterator; pEdge edge;
   edge_iterator = M_edgeIter(mesh);
   while(edge = EIter_next(edge_iterator)){
   	EN_setID(edge, i);
   	this->newEdge();
	if(E_numPoints(edge)>=1){
		Node* new_node = this->newNode();
		new_node->x = P_x(E_point(edge, 0));
		new_node->y = P_y(E_point(edge, 0));
		new_node->z = P_z(E_point(edge, 0));
		this->getEdge(i)->node = new_node;
		new_node->ID = numNodes() - 1;
	}
	this->getEdge(i)->setClassification(E_whatIn(edge));
	this->getEdge(i)->ID=i;
	//cout << "Creating edge #" << i << "\n";
	i++;
   }
   EIter_delete(edge_iterator);
   
   i=0;
   VIter vertex_iterator; pVertex vertex;
   vertex_iterator = M_vertexIter(mesh);
   while(vertex = VIter_next(vertex_iterator)){
   	EN_setID(vertex, i);
	MeshVertex* new_vertex;
	new_vertex = this->newVertex();
	new_vertex->ID = i;
	Node* new_node;
	new_node = this->newNode();
	new_node->x = P_x(V_point(vertex));
	new_node->y = P_y(V_point(vertex));
	new_node->z = P_z(V_point(vertex));
	new_node->ID = numNodes()-1;
	this->getVertex(i)->node = new_node;
	this->getVertex(i)->setClassification(V_whatIn(vertex));
	//cout << "Creating vertex #" << i << "; x=" << new_node->x << " y= " << new_node->y << " z= " << new_node->z << "\n";
	i++;
   }
   VIter_delete(vertex_iterator);
        
   //Second pass through to set up downward adjacencies
   cout << "Setting up downward adjacencies\n";
   
   /*i=0;
   region_iterator = M_regionIter(mesh);
   while(region = RIter_next(region_iterator)){
   	MeshRegion * newregion = this->getRegion(i);
	for(int j=0; j<R_numFaces(region); j++){
		newregion->addFace(this->getFace(EN_id(R_face(region, j))));
		//cout << "Adding Face #" << EN_id(R_face(region, j)) << " to Region #" << i << "\n";
	}
	i++;
   }
   RIter_delete(region_iterator);*/
   
   i=0;
   face_iterator = M_faceIter(mesh);
   while(face = FIter_next(face_iterator)){
   	MeshFace * newface = this->getFace(i);
	for(int j=0; j<F_numEdges(face); j++){
		newface->addEdge(this->getEdge(EN_id(F_edge(face, j))));
		//cout << "Adding Edge #" << EN_id(F_edge(face, j)) << " to Face #" << i << "\n";
	}
	i++;
   }
   FIter_delete(face_iterator);
   
   i=0;
   edge_iterator = M_edgeIter(mesh);
   while(edge = EIter_next(edge_iterator)){
   	MeshEdge * newedge = this->getEdge(i);
	for(int j=0; j<2; j++){
		newedge->addVertex(this->getVertex(EN_id(E_vertex(edge, j))), j);
		//cout << "Adding Vertex #" << EN_id(E_vertex(edge, j)) << " to Edge #" << i << "\n";
	}
	i++;
   }
   EIter_delete(edge_iterator);
   
   //Third and final pass through to set up upward adjacencies
   cout << "Setting up upward adjacencies\n";
   
   i=0;
   vertex_iterator = M_vertexIter(mesh);
   while(vertex = VIter_next(vertex_iterator)){
   	MeshVertex * newvertex = this->getVertex(i);
	for(int j=0; j<V_numEdges(vertex); j++){
		newvertex->addEdge(this->getEdge(EN_id(V_edge(vertex, j))));
		//cout << "Adding Edge #" << EN_id(V_edge(vertex, j)) << " to Vertex #" << i << "\n";
	}
	i++;
   }
   VIter_delete(vertex_iterator);
   
   i=0;
   edge_iterator = M_edgeIter(mesh);
   while(edge = EIter_next(edge_iterator)){
   	MeshEdge * newedge = this->getEdge(i);
	for(int j=0; j<E_numFaces(edge); j++){
		newedge->addFace(this->getFace(EN_id(E_face(edge, j))));
		//cout << "Adding Face #" << EN_id(E_face(edge, j)) << " to Edge #" << i << "\n";
	}
	i++;
   }
   EIter_delete(edge_iterator);
   
   /*cout << "end edge\n";
   i=0;
   face_iterator = M_faceIter(mesh);
   cout << "get face iterator\n"
   while(face = FIter_next(face_iterator)){
   	MeshFace * newface = newmesh.getFace(i);
	for(int j=0; j<2; j++){
		newface->addRegion(newmesh.getRegion(EN_id(F_region(face, j))), j);
		//cout << "Adding Region #" << EN_id(F_region(face, j)) << " to Face #" << i << "\n";
	}
	i++;
   }
   FIter_delete(face_iterator);
   cout << "end face\n";*/
}
#endif

void Mesh::reorder2(){
   vector<DOF*> DOFs;
   int labeldof = -1;
   for(int i=0;i<numNodes();i++){
      DOFs = Nodes[i]->getDOFs();
      for(int j=0;j<DOFs.size();j++){
         if(DOFs[j]->get_status()==DOF_Free){
            labeldof=labeldof+1;
            DOFs[j]->set_eqnumber(labeldof);
         }
      }
   }
};

void Mesh::reorder(){
   int labeldof = ndof;
   int labelnode = Nodes.size();
   int labelface = MeshFaces.size();
   int labelregion = MeshRegions.size();
   Node* node;
   queue<MeshEntity*> q;
   queue<MeshEntity*> list;
   MeshVertex* othervertex;
   vector<DOF*> DOFs;
   vector<DOF*>::iterator dof_iter;
   
   //cout << "Beginning mesh reordering...\n";
   
   for(int i=0;i<numNodes();i++){
   	Nodes[i]->ID = -2; //-2 indicates not labeled and not in queue
   }
   for(int i=0;i<numFaces();i++){
   	MeshFaces[i]->ID = -2; //-2 indicates not labeled and not in queue
   }
   for(int i=0;i<numRegions();i++){
   	MeshRegions[i]->ID = -2; //-2 indicates not labeled and not in queue
   }
   
   //cout << "Get start...\n";
   
	MeshEntity* entity = getStart();
   	//cout << "Put first entity into queue...\n";
	q.push(entity);
	entity->ID = -1; //0 indicates entity in queue
	//cout << "Begin looping through queue...\n";
	while(q.size()>0){
		if(labelnode<0){
			cout << "ERROR! labelnode<0!\n";
			return;
		}
		entity = q.front();
		q.pop();
		//if(entity->get_dimensions()==1){cout << "dequeueing edge\n";}
		node = entity->node;
		if(node->ID<0){ //node is unlabeled
			labelnode = labelnode - 1;
			node->ID=labelnode;
                        DOFs = node->getDOFs();
                        for(dof_iter=DOFs.begin();dof_iter!=DOFs.end();++dof_iter){
                           if((*dof_iter)->get_status()==DOF_Free){
                              labeldof=labeldof-1;
                              if(labeldof<0){
                                       cout << "ERROR! labeldof<0!\n";
                                       return;
                              }
                              (*dof_iter)->set_eqnumber(labeldof);
                           }
                        }
		}
		
		if(entity->get_dimensions()==0){ //entity is a vertex
			//cout << "Loop through edges of vertex\n";
			MeshVertex* vertex = (MeshVertex*) entity;
			for(vector<MeshEdge*>::iterator edge_iter=vertex->getFirstEdge();edge_iter!=vertex->getLastEdge();++edge_iter){
				MeshEdge* edge = *edge_iter;
				//cout << "Loop through faces of edge #" << edge->ID << "\n";
				for(vector<MeshFace*>::iterator face_iter=edge->getFirstFace();face_iter!=edge->getLastFace();++face_iter){
					MeshFace* face = *face_iter;
					if(face->ID<0){ //face is unlabeled
						labelface = labelface - 1;
						face->ID = labelface;
					}
					if(face->node!=NULL && face->node->ID<-1){
						q.push(face);
						face->node->ID=-1;
					}
				}
				othervertex = edge->otherVertex(vertex);
				if(edge->node != NULL){  //if edge has a node
					//cout << "Edge has a node\n";
					if(othervertex->node->ID >= -1 && edge->node->ID < -1){
						//cout << "Labeling node directly\n";
						labelnode = labelnode - 1;
						edge->node->ID = labelnode;
                                                DOFs = edge->node->getDOFs();
                                                for(dof_iter=DOFs.begin();dof_iter!=DOFs.end();++dof_iter){
                                                   if((*dof_iter)->get_status()==DOF_Free){
                                                      labeldof=labeldof-1;
                                                      if(labeldof<0){
                                                               cout << "ERROR! labeldof<0!\n";
                                                               return;
                                                      }
                                                      (*dof_iter)->set_eqnumber(labeldof);
                                                   }
                                                }
					}else if(othervertex->node->ID<-1){
						//cout << "Queueing edge\n";
						q.push(edge);
						list.push(othervertex);
						othervertex->node->ID=-1;
					}
				}else{
					if(othervertex->node->ID<-1){
						//cout << "Queue edge's other vertex\n";
						list.push(othervertex);
						othervertex->node->ID=-1;
					}
				}
			}
		}
		while(list.size()>0){
			//cout << "Queue list\n";
			q.push(list.front());
			list.pop();
		}
		//cout << "Get next entity...\n";
	}
}

MeshEntity* Mesh::getStart(){
   MeshVertex* start_vertex = MeshVertexes[0];
   int min_edges = 9999;
   for(int i=0;i<numVertexes();i++){
#ifdef MESHSIM
   	if(GEN_type(MeshVertexes[i]->getClassification())==0){
		if(PList_size(GV_edges((pGVertex)MeshVertexes[i]->getClassification()))<min_edges){
		start_vertex = MeshVertexes[i];
		}
	}
#endif
   }
   return (MeshEntity*)start_vertex;
}

void Mesh::exportDX(string out_file){
   int num_edges;
   cout << "Creating OpenDX output file..\n";
   map<int, Node*> node_map;
   for(int i=0; i<numNodes(); i++){
      cout << "Mapping node #" << i << " to #" << Nodes[i]->ID << "\n";
      node_map[Nodes[i]->ID] = Nodes[i];
   }
   cout << "Finished sorting nodes by ID..\n";
   ofstream fout(out_file.c_str()); // Open for writing
   fout << "object 1 class array type float rank 1 shape 3\n";
   fout << "items " << numNodes() << " data follows\n";
   fout << "\n";
   map<int, Node*>::iterator map_iter;
   for(map_iter=node_map.begin();map_iter!=node_map.end();map_iter++){
      cout << "Listing node #" << (*map_iter).second->ID << "\n";
      fout << "   " << (*map_iter).second->x() << "   " << (*map_iter).second->y() << "   " << (*map_iter).second->z() << "\n";
   }
   if(MeshFaces[0]->numEdges()==3){
      	 num_edges=3;
      }else{
         num_edges=4;
      }
   cout << "Finished listing node positions...\n";
   fout << "\n";
   fout << "object 2 class array type int rank 1 shape " << num_edges << "\n";
   fout << "items " << numFaces() << " data follows\n";
   fout << "\n";
   set<Node*> nodes;
   for(vector<MeshFace*>::iterator face_iter=getFirstFace();face_iter!=getLastFace();face_iter++){
      nodes.clear();
      
      for(vector<MeshEdge*>::iterator edge_iter=(*face_iter)->getFirstEdge();edge_iter!=(*face_iter)->getLastEdge();edge_iter++){
         nodes.insert((*edge_iter)->getVertex(0)->node);
	 nodes.insert((*edge_iter)->getVertex(1)->node);
      }
      for(set<Node*>::iterator node_iter=nodes.begin();node_iter!=nodes.end();node_iter++){
         fout << "   " << (*node_iter)->ID;
      }
      fout << "\n";
   }
   cout << "Finished listing connection info...\n";
   fout << "\n";
   if (num_edges==3){
      fout << "attribute \"element type\" string \"triangles\"\n"; 
   }else{
      fout << "attribute \"element type\" string \"quads\"\n"; 
   }
   fout << "attribute \"ref\" string \"positions\"\n";
   fout << "\n"; 
   fout << "object 3 class array type float rank 0 items " << numFaces() << " data follows\n";
   fout << "\n";
   for(vector<MeshFace*>::iterator face_iter=getFirstFace();face_iter!=getLastFace();face_iter++){
      fout << (*face_iter)->ID << "\n";
   }
   fout << "attribute \"dep\" string \"connections\"\n";
   fout << "\n";
   fout << "object 4 class array type float rank 0 items " << numNodes() << " data follows\n";
   fout << "\n";
   for(int i=0; i<numNodes(); i++){
      fout << i << "\n";
   }
   fout << "attribute \"dep\" string \"positions\"\n";
   fout << "\n";
   fout << "object \"irregular positions irregular connections\" class field\n";
   fout << "component \"positions\" value 1\n";
   fout << "component \"connections\" value 2\n";
   fout << "component \"elnum\" value 3\n";
   fout << "component \"ndnum\" value 4\n";
   fout << "end\n";

}

int getNumNodes(int type)
{
  switch (type) {
  case 15: return 1;              // point
  case 1 : return 2;              // line 1
  case 8 : return 3;          // line 2
  case 2 : return 3;              // triangle 1
  case 9 : return 6;          // triangle 2
  case 3 : return 4;              // quadrangle 1
  case 10: return 9;      // quadrangle 2
  case 4 : return 4;              // tetrahedron 1
  case 11: return 4 + 6;          // tetrahedron 2
  case 5 : return 8;              // hexahedron 1
  case 12: return 8 + 12 + 6 + 1; // hexahedron 2 
  case 6 : return 6;              // prism 1
  case 13: return 6 + 9 + 3;      // prism 2
  case 7 : return 5;              // pyramid 1
  case 14: return 5 + 8 + 1;      // pyramid 2
  default: return 0;
  }
}

int getNumEdges(int type)
{
  switch (type) {
  case 15: return 0;              // point
  case 1 : return 1;              // line 1
  case 8 : return 1;          // line 2
  case 2 : return 3;              // triangle 1
  case 9 : return 3;          // triangle 2
  case 3 : return 4;              // quadrangle 1
  case 10: return 4;      // quadrangle 2
  case 4 : return 4;              // tetrahedron 1
  case 11: return 4;          // tetrahedron 2
  case 5 : return 8;              // hexahedron 1
  case 12: return 8; // hexahedron 2 
  case 6 : return 6;              // prism 1
  case 13: return 6;      // prism 2
  case 7 : return 5;              // pyramid 1
  case 14: return 5;      // pyramid 2
  default: return 0;
  }
}

void Mesh::readMesh(const char* filename)
{
   double version = 1.0;
   
   char meshfile[256];
   strcpy(meshfile, filename);
   FILE* fp = fopen(strcat(meshfile, ".msh"), "r");

   while(1) {
      char str[256];
      do {
         fgets(str, sizeof(str), fp);
         if(feof(fp)){
            break;
         }
      } while(str[0] != '$');
    
      if(feof(fp)){
         break; //I hate "break"s...
      }

      if(!strncmp(&str[1], "MeshFormat", 10)) {
         int format, size;
         fscanf(fp, "%lf %d %d\n", &version, &format, &size);
         if(version < 2.0){
            fprintf(stderr, "Error: Wrong msh file version %g\n", version);
            exit(1);
         }
         if(format){
            fprintf(stderr, "Error: Unknown data format for mesh\n");
            exit(1);
         }
      }
      else if(!strncmp(&str[1], "Nodes", 5)) {
         int num_nodes;
         fscanf(fp, "%d", &num_nodes);
         for(int i = 0; i < num_nodes; i++) {
            int num;
            double x, y, z;
            fscanf(fp, "%d %lf %lf %lf", &num, &x, &y, &z);
            if(numNodes()==num){
               fprintf(stderr, "Error: node %d already exists\n", num);
               exit(1);
            } else {
               Node* new_node = newNode(); //newNode() adds a new Node to the Nodes list
               point pt;
               pt.x = x;
               pt.y = y;
               pt.z = z;
               new_node->pt(pt);
               
               new_node->ID = num;
            }
         }
      }
      else if(!strncmp(&str[1], "Elements", 8)) {
         //"Elements" in gmsh terms can be vertexes, edges, faces or regions
         //For 2D meshes, all faces are listed, as well as edges and vertexes that are
         //located on what gmsh calls "physical entities".
         int numElements;
         fscanf(fp, "%d", &numElements);
         //cout << "# of elements = " << numElements << endl;
         for(int i = 0; i < numElements; i++) {
            int num, type, physical, elementary, partition = 1, numNodes, numTags;
            
            fscanf(fp, "%d %d %d", &num, &type, &numTags);
            //cout << "Reading element #" << num << ", type " << type << endl;
            elementary = physical = partition = 1;
            for(int j = 0; j < numTags; j++){
               int tag;
               fscanf(fp, "%d", &tag);    
               if(j == 0){
                  physical = tag;
               }else if(j == 1){
                  elementary = tag;
               }else if(j == 2){
                  partition = tag;
               }
               // ignore any other tags for now
            }
            //cout << "Physical tag = " << physical << endl;
            numNodes = getNumNodes(type);
            int numEdges = getNumEdges(type);
            if(!numNodes){
               fprintf(stderr, "Error: Unknown type %d for element %d\n", type, i); 
               exit(1);
            }
            
            if(type==15){
               //this is a point, read in node #
               int nodenum;
               fscanf(fp, "%d", &nodenum);
               MeshVertex* vertex = findVertexbyNode(nodenum);
               if(!vertex){
                  vertex = newVertex();
                  vertex->node = findNodebyID(nodenum); //Nodes[nodenum-1];
                  vertex->ID = MeshVertexes.size();
               }
               vertex->setClassification(GeomEntities[physical]);
            }else if(type==1 || type==8){
               //this is a line, read in node #
               int numNode1;
               int numNode2;
               fscanf(fp, "%d %d", &numNode1, &numNode2);
               MeshVertex* vertex1 = findVertexbyNode(numNode1);
               if(!vertex1){
                  vertex1 = newVertex();
                  vertex1->node = findNodebyID(numNode1); //Nodes[numNode1-1];
                  vertex1->setClassification(GeomEntities[0]);
                  vertex1->ID = MeshVertexes.size();
               }
               MeshVertex* vertex2 = findVertexbyNode(numNode2);
               if(!vertex2){
                  vertex2 = newVertex();
                  vertex2->node = findNodebyID(numNode2); //Nodes[numNode2-1];
                  vertex2->setClassification(GeomEntities[0]);
                  vertex2->ID = MeshVertexes.size();
               }
               MeshEdge* new_edge = findEdgebyVertexes(vertex1, vertex2);
               if(!new_edge){ //edge hasn't been added yet
                  new_edge = newEdge();
                  new_edge->addVertex(vertex1, 0);
                  new_edge->addVertex(vertex2, 1);
                  vertex1->addEdge(new_edge);
                  vertex2->addEdge(new_edge);
                  new_edge->ID = MeshEdges.size();
               }
               new_edge->setClassification(GeomEntities[physical]);
               if(type==8){
                  int numNode3;
                  fscanf(fp, "%d", &numNode3);
                  new_edge->node = findNodebyID(numNode3);
               }
            }else if(type==2 || type==3 || type==9 || type==10){ //2D
               
               //Assuming 2D for now
               int firstNode;
               int numNode1;
               int numNode2;
               MeshFace *e = newFace();
               //cout << "Reading Face#" << MeshFaces.size() << endl;
               //cout << "# edges = " << numEdges << endl;
               fscanf(fp, "%d", &firstNode);
               numNode2 = firstNode;
               for(int j=0;j<numEdges;j++){
                  numNode1 = numNode2;
                  if(j<(numEdges-1)){
                     fscanf(fp, "%d", &numNode2);
                  }else{
                     numNode2 = firstNode;
                  }
                  //cout << "Setting up edge " << numNode1 << "-" << numNode2 << endl;
                  MeshVertex* vertex1 = findVertexbyNode(numNode1);
                  if(!vertex1){
                     vertex1 = newVertex();
                     vertex1->node = findNodebyID(numNode1); //Nodes[numNode1-1];
                     vertex1->setClassification(GeomEntities[0]);
                     vertex1->ID = MeshVertexes.size();
                  }
                  MeshVertex* vertex2 = findVertexbyNode(numNode2);
                  if(!vertex2){
                     vertex2 = newVertex();
                     vertex2->node = findNodebyID(numNode2); //Nodes[numNode2-1];
                     vertex2->setClassification(GeomEntities[0]);
                     vertex2->ID = MeshVertexes.size();
                  }
                  MeshEdge* new_edge = findEdgebyVertexes(vertex1, vertex2);
                  if(!new_edge){ //edge hasn't been added yet
                     new_edge = newEdge();
                     new_edge->addVertex(vertex1, 0);
                     new_edge->addVertex(vertex2, 1);
                     new_edge->setClassification(GeomEntities[0]);
                     vertex1->addEdge(new_edge);
                     vertex2->addEdge(new_edge);
                     new_edge->ID = MeshEdges.size();
                  }
                  new_edge->addFace(e);
                  e->addEdge(new_edge);
                  e->ID = MeshFaces.size();
               }
               e->setClassification(GeomEntities[physical]);
               if(type==9){ //2nd order triangle
                  //get edge nodes
                  for(int n=0;n<3;n++){
                     int edge_node;
                     fscanf(fp, "%d", &edge_node);
                     e->getEdge(n)->node = findNodebyID(edge_node);
                  }
               }
               if(type==10){ //2nd order quad
                  //get edge nodes
                  for(int n=0;n<4;n++){
                     int edge_node;
                     fscanf(fp, "%d", &edge_node);
                     e->getEdge(n)->node = findNodebyID(edge_node);
                  }
                  //get face node
                  int face_node;
                  fscanf(fp, "%d", &face_node);
                  e->node = findNodebyID(face_node);
               }
            }else if(type==4){ //tetrahedron
               int numNode1;
               int numNode2;
               int numNode3;
               int numNode4;
               fscanf(fp, "%d %d %d %d", &numNode1, &numNode2, &numNode3, &numNode4);
               MeshVertex* vertex1 = findVertexbyNode(numNode1);
               if(!vertex1){
                  vertex1 = newVertex();
                  vertex1->node = findNodebyID(numNode1); //Nodes[numNode1-1];
                  vertex1->setClassification(GeomEntities[0]);
                  vertex1->ID = MeshVertexes.size();
               }
               MeshVertex* vertex2 = findVertexbyNode(numNode2);
               if(!vertex2){
                  vertex2 = newVertex();
                  vertex2->node = findNodebyID(numNode2); //Nodes[numNode2-1];
                  vertex2->setClassification(GeomEntities[0]);
                  vertex2->ID = MeshVertexes.size();
               }
               MeshVertex* vertex3 = findVertexbyNode(numNode3);
               if(!vertex3){
                  vertex3 = newVertex();
                  vertex3->node = findNodebyID(numNode3); //Nodes[numNode2-1];
                  vertex3->setClassification(GeomEntities[0]);
                  vertex3->ID = MeshVertexes.size();
               }
               MeshVertex* vertex4 = findVertexbyNode(numNode4);
               if(!vertex4){
                  vertex4 = newVertex();
                  vertex4->node = findNodebyID(numNode4); //Nodes[numNode2-1];
                  vertex4->setClassification(GeomEntities[0]);
                  vertex4->ID = MeshVertexes.size();
               }
               MeshEdge* edge1 = findEdgebyVertexes(vertex1, vertex2);
               MeshEdge* edge2 = findEdgebyVertexes(vertex2, vertex3);
               MeshEdge* edge3 = findEdgebyVertexes(vertex3, vertex1);
               MeshEdge* edge4 = findEdgebyVertexes(vertex1, vertex2);
               MeshEdge* edge5 = findEdgebyVertexes(vertex4, vertex3);
               MeshEdge* edge6 = findEdgebyVertexes(vertex2, vertex4);
               
               //tets have 4 faces, we need to loop through each face and check to
               //see if the face has already been added
               //if not, add the face
               //first up, Face #1 - 1-2-3
               pair<MeshFace*, bool> face1 = findFacebyEdge(edge1, edge2, edge3);
               pair<MeshFace*, bool> face2 = findFacebyEdge(edge3, edge5, edge4);
               pair<MeshFace*, bool> face3 = findFacebyEdge(edge6, edge5, edge2);
               pair<MeshFace*, bool> face4 = findFacebyEdge(edge4, edge6, edge1);
               MeshRegion* region = newRegion();
               region->addFace(face1);
               region->addFace(face2);
               region->addFace(face3);
               region->addFace(face4);
               face1.first->addRegion(region);
               face2.first->addRegion(region);
               face3.first->addRegion(region);
               face4.first->addRegion(region);
               region->setClassification(GeomEntities[physical]);
               //one all 4 faces have been added, add the face to the region
            }else{
               cerr << "Unsupported element type!" << endl;
            }
         }
      }

      do {
         fgets(str, sizeof(str), fp);
         if(feof(fp)){
            fprintf(stderr, "Error: Premature end of mesh file\n");
            exit(1);
         }
      } while(str[0] != '$');
    
   }

   fclose(fp);

}

MeshVertex* Mesh::findVertexbyNode(int n){
   vector<MeshVertex*>::iterator vertex_iter;
   if(MeshVertexes.size()>1){
      for(vertex_iter = MeshVertexes.begin();vertex_iter != MeshVertexes.end(); ++vertex_iter){
         if((*vertex_iter)->node->ID == n){
            return((*vertex_iter));
         }
      }
   }
   return NULL;
};

MeshEdge* Mesh::findEdgebyVertexes(MeshVertex* vertex1, MeshVertex* vertex2){
   vector<MeshEdge*>::iterator edge_iter;
   for(edge_iter=vertex1->getFirstEdge();edge_iter!=vertex1->getLastEdge();++edge_iter){
      if((*edge_iter)->getVertex(0)==vertex2 || (*edge_iter)->getVertex(1)==vertex2){
         return (*edge_iter);
      }
   }
   //edge hasn't been added yet
   MeshEdge* new_edge = newEdge();
   new_edge->addVertex(vertex1, 0);
   new_edge->addVertex(vertex2, 1);
   new_edge->setClassification(GeomEntities[0]);
   vertex1->addEdge(new_edge);
   vertex2->addEdge(new_edge);
   new_edge->ID = MeshEdges.size();
   return new_edge;
};

pair<MeshFace*, bool> Mesh::findFacebyEdge(MeshEdge* edge1, MeshEdge* edge2, MeshEdge* edge3){
   //FIXME this only works for triangles!
   vector<MeshFace*>::iterator face_iter;
   for(face_iter=edge1->getFirstFace();face_iter!=edge1->getLastFace();++face_iter){
      if((*face_iter)->getEdge(1)==edge2 || (*face_iter)->getEdge(2)==edge2){
         pair<MeshFace*, bool> f((*face_iter), 1);  //face already added, so this region uses face in opposite direction
         return f;
      }
   }
   MeshFace* face1 = newFace();
   face1->addEdge(edge1);
   face1->addEdge(edge2);
   face1->addEdge(edge3);
   edge1->addFace(face1);
   edge2->addFace(face1);
   edge3->addFace(face1);
   face1->setClassification(GeomEntities[0]);
   pair<MeshFace*, bool> f((face1), 0);
   return f;
};

Node* Mesh::findNodebyID(int n){
   vector<Node*>::iterator node_iter;
   for(node_iter=Nodes.begin(); node_iter!=Nodes.end(); ++node_iter){
      if((*node_iter)->ID==n){
         return (*node_iter);
      }
   }
   return NULL;
}

void Mesh::readAttributes(const char* filename){
   string key;
   double value;
   int idx;
   GeomEntity* entity;
   char attribfile[256];
   strcpy(attribfile, filename);
   
   ifstream fs(strcat(attribfile, ".att"));
   
   while(!fs.eof() && !fs.fail()){
	  fs >> key >> value;
	  
      if(key=="GeomEntity"){
         entity = new GeomEntity();
         idx = (int) value;
         cout << "Adding GeomEntity at index " << idx << endl;
         GeomEntities[idx] = entity;
      }else{
         cout << "Adding key " << key << " = " << value << endl;
         //Warning: if a GeomEntity key is not found (and therefore
         //a GeomEntity is not created) we will crash here on access!!!
         entity->addAttribute(key, value);
      }
   }
};


ostream& operator<<(ostream &os, const Mesh& meshout) {
   os << "This is a mesh\n";
   return os;
}
