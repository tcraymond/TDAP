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

#ifndef MESHENTITY_H
#define MESHENTITY_H

#include "node.h"
#include <vector>

#ifdef MESHSIM
#include "MeshSim.h" //For pGEntity
typedef GEntity GeomEntity;
#else
#include "geomentity.h"
#endif

/// This is the class that all mesh entity classes (Regions, Faces, etc.) inherit from.
/// This class contains basic functions for getting and setting classifications, setting an
/// integer ID, and assigning a node to the entity.  By allowing a node to be assigned to 
/// any entity, we can begin to allow higher-order elements.  This would be further 
/// facilitated by allowing more than one node per entity.  Note that all vertices must
/// contain at least one node.

class MeshEntity {

public:

  /// An integer for assigned a unique ID to an entity.  This is not assigned unless done so explicitly.
  int ID;
  
  /// Default constructor.  Currently empty. Not anymore...
  MeshEntity ( );
  
  /// Returns the number of dimensions for an entity.  This is useful in identifying the entity type.
  virtual int get_dimensions() const = 0;
  
  /// Pointer to a node.  Required for vertices, optional for all others.
  Node* node;
  
  /// Returns the GeomEntity that this mesh entity is classified on
  GeomEntity* getClassification();
  
  /// Sets the GeomEntity that this mesh entity is classified on
  void setClassification(GeomEntity*);
  
  /// Returns an ordered list of nodes for the mesh entity
  virtual vector<Node*> getNodes() = 0;
    
protected:

private:

  /// variable for number of dimensions
  int dimensions;
  
  /// GeomEntity representing the model object this mesh entity is classified on
  GeomEntity* myClassification;
  
};
#endif //MESHENTITY_H

