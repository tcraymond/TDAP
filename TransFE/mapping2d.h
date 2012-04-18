/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
 
#ifndef MAPPING2D_H
#define MAPPING2D_H

#include "mapping.h"
#include "MeshDB/point.h"
#include "MeshDB/meshface.h"
#include "shapefunction.h"

class Mapping2D : public Mapping{
public:
    Mapping2D(MeshFace* Element, ShapeFunction* SF):Mapping(Element, SF){
      nsd=2;
      npd=2;
    };

	~Mapping2D(){};
    
    virtual Matrix jacobianInverse(point pt);
    
    virtual Matrix dXds(point pt);
    
    virtual double detJacobian(point pt);

};

#endif
