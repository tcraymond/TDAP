/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
 
#ifndef MAPPING3D_H
#define MAPPING3D_H

#include "mapping.h"
#include "MeshDB/point.h"
#include "MeshDB/meshregion.h"
#include "shapefunction.h"

class Mapping3D : public Mapping{
public:
    Mapping3D(MeshRegion* Element, ShapeFunction* SF):Mapping(Element, SF){
      nsd=3;
      npd=3;
    };

    virtual ~Mapping3D();
    
    virtual Matrix jacobianInverse(point pt);
    
    virtual Matrix dXds(point pt);
    
    virtual double detJacobian(point pt);

};

#endif
