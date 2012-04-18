/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#ifndef LIN1DMAPPING_H
#define LIN1DMAPPING_H

#include "mapping.h"
#include "MeshDB/point.h"
#include "MeshDB/meshedge.h"
#include "shapefunction.h"

class Mapping1D2D : public Mapping{
public:
    Mapping1D2D(MeshEdge* Element, ShapeFunction* SF):Mapping(Element, SF){
      nsd=2;
      npd=1;
    };

	virtual ~Mapping1D2D(){};
    
    virtual Matrix jacobianInverse(point pt);
    
    virtual Matrix dXds(point pt);
    
    virtual double detJacobian(point pt);

};

#endif
