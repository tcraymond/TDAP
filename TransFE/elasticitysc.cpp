/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
 
#include "elasticitysc.h"

Matrix ElasticitySC::evaluatePt(point pt){
   //nnd = # DOF/node
   //nen = # nodes/element   

   Matrix B_t(nnd*nen, 3);
   Matrix B(3, nnd*nen);
   Matrix D(3,3);
   Matrix Bt_D_B(nnd*nen, nnd*nen);
   
   // dsdx:
   // [drdx, drdy]
   // [dsdx, dsdy]
   // dNds:
   // [dN1dr, dN1ds]
   // [dN2dr, dN2ds]
   // [dN3dr, dN3ds]
   // dNds * dsdx
   // [dN1dr*drdx+dN1ds*dsdx, dN1dr*drdy+dN1ds*dsdy]
   // [dN2dr*drdx+dN2ds*dsdx, dN2dr*drdy+dN2ds*dsdy]
   // [dN2dr*drdx+dN2ds*dsdx, dN2dr*drdy+dN2ds*dsdy]
   // -equals-
   // 1    [dN1dr*dyds-dN1ds*dydr, -dN1dr*dxds+dN1ds*dxdr]
   //--- * [dN2dr*dyds-dN1ds*dydr, -dN2dr*dxds+dN1ds*dxdr]
   // J    [dN3dr*dyds-dN1ds*dydr, -dN3dr*dxds+dN1ds*dxdr]
   // -equals-
   // [dN1dx, dN1dy]
   // [dN2dx, dN2dy]
   // [dN3dx, dN3dy]
   
   Matrix dNds = SF->dNds(pt);
   Matrix dsdx = Map->jacobianInverse(pt);
   Matrix dNdx = dNds * dsdx;
   
   double nu = Element->getClassification()->getAttribute("nu");
   double E = Element->getClassification()->getAttribute("E");
      
   double lambda = nu * E / ((1 + nu) * (1 - 2 * nu));
   double mu = E / (2 * (1 + nu));
   
   //Set D for Plane Strain     
   D[0][0] = lambda + 2 * mu;
   D[0][1] = lambda;
   D[0][2] = 0;
   D[1][0] = lambda;
   D[1][1] = lambda + 2 * mu;
   D[1][2] = 0;
   D[2][0] = 0;
   D[2][1] = 0;
   D[2][2] = mu;
   
   // B1:
   // [dN1dx    0  ]
   // [  0    dN1dy]
   // [dN1dy  dN1dx]
   //
   // Repeat for other nodes
      
   for(int i=0; i<nen; i++){
      B[0][2*i] = dNdx[i][0];
      B[0][2*i+1] = 0;
      B[1][2*i] = 0;
      B[1][2*i+1] = dNdx[i][1];
      B[2][2*i] = dNdx[i][1];
      B[2][2*i+1] = dNdx[i][0];
   }
      
   B_t = B.T();
   Bt_D_B = B_t * D * B;
   
   return Bt_D_B;
   
}

