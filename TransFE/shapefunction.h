/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#ifndef SHAPEFUNCTION_H
#define SHAPEFUNCTION_H

/// This class represents a generic shape function. 

#include "MeshDB/meshentity.h"
#include "typedefs.h"
#include "MeshDB/point.h"
#include <vector>

class ShapeFunction {

public:

   ShapeFunction(MeshEntity* mElement){
      Element = mElement;
   };
   
   virtual ~ShapeFunction(){}; //Need to loop through mIntPt and trash the points!!!

   virtual Vector N(point) = 0;
   virtual Matrix dNds(point) = 0;
   
   virtual vector<point> IntPts() = 0;
   virtual Vector Weights() = 0;
   virtual int numIntPts() = 0;
   
protected:
  
private:

   MeshEntity* Element;
      
};
#endif //SHAPEFUNCTION_H

