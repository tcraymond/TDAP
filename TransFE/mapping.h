/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
 
#ifndef MAPPING_H
#define MAPPING_H

#include "typedefs.h"
#include "MeshDB/point.h"
#include "MeshDB/meshentity.h"
#include "shapefunction.h"

class Mapping{
public:
    Mapping(MeshEntity* mElement, ShapeFunction* mSF){
       Element = mElement;
       SF = mSF;
       nen = Element->getNodes().size();
    };

	~Mapping(){};
    
    virtual Matrix jacobianInverse(point) = 0;
    
    virtual Matrix dXds(point) = 0;
    
    virtual double detJacobian(point) = 0;
    
protected:
    MeshEntity* Element;
    ShapeFunction* SF;
    
    int nsd; //# of spacial dimensions
    int npd; //# of parametric dimensions
    int nen; //# of element nodes
    
};

#endif
