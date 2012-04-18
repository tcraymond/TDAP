/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#include "elasticityfc.h"

Vector ElasticityFC::evaluatePt(point pt){
   Vector forces(nnd * nen);
   Vector forces_x(nen);
   Vector forces_y(nen);
   
   Matrix dXds = Map->dXds(pt);
   
   double F_x = Element->getClassification()->getAttribute("F_x");
   double F_y = Element->getClassification()->getAttribute("F_y");
   
   //In the case of surface tractions, F_x is the tangential traction and
   //F_y is the normal traction
      
   forces_x = SF->N(pt) * (F_x*dXds[0][0]+F_y*dXds[1][0]);
   forces_y = SF->N(pt) * (F_x*dXds[1][0]-F_y*dXds[0][0]);
   
   for(int i=0;i<nen;i++){
      forces[2*i] = forces_x[i];
      forces[2*i+1] = forces_y[i];
   }
   
   return forces;
   
};



