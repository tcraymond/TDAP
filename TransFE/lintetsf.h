/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#ifndef LINTETSF_H
#define LINTETSF_H

/// This class represents the shape functions for a first order (linear) tetrahedron. 

#include "shapefunction.h"
#include "MeshDB/meshregion.h"
#include "typedefs.h"
#include "MeshDB/point.h"
#include <vector>

class LinTetSF : public ShapeFunction {

public:

   LinTetSF(MeshRegion* Element) : ShapeFunction(Element) {};

   virtual Vector N(point);
   virtual Matrix dNds(point);
      
   virtual vector<point> IntPts();
   virtual Vector Weights();
   virtual int numIntPts();
  
protected:
  
private:

};
#endif //LINTETSF_H

