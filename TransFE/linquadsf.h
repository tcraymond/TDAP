/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#ifndef LINQUADSF_H
#define LINQUADSF_H

/// This class represents the shape functions for a first order (linear) quadrilateral. 

#include "shapefunction.h"
#include "MeshDB/meshface.h"
#include "typedefs.h"
#include "MeshDB/point.h"
#include <vector>

class LinQuadSF : public ShapeFunction {

public:

   LinQuadSF(MeshFace* Element) : ShapeFunction(Element) {};

   virtual Vector N(point);
   virtual Matrix dNds(point);
      
   virtual vector<point> IntPts();
   virtual Vector Weights();
   virtual int numIntPts();
  
protected:
  
private:

};
#endif //LINQUADSF_H

