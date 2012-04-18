/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#ifndef CONSTRAINT_H
#define CONSTRAINT_H

/// This class represents a generic constraint. 

#include "MeshDB/meshentity.h"
#include "mapping.h"
#include "shapefunction.h"

class Constraint{

public:

   Constraint(MeshEntity* Element_in){
      entity = Element_in;
      //map = Map_in;
      //SF = SF_in;
   }; 

   virtual ~Constraint() {};

   virtual void apply() = 0;
  
protected:

   MeshEntity* entity;
   //Mapping* map;
   //ShapeFunction* SF;
   
private:

};

#endif //CONSTRAINT_H
