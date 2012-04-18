/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
 
#include "mapping2d.h"

//There has to be a better way to do this...
//jacobianInverse calls dXds, detJacobian calls dXds and stiffnesscontributor::evaluate
//calls detJacobian.  Therefore, dXds is called three times and detJacobian twice to
//get the exact same answer.

Matrix Mapping2D::jacobianInverse(point pt){
   Matrix j_inv(npd, nsd);
   Matrix mdXds = dXds(pt);
   double j = detJacobian(pt);
   
   // j_inv = dSdX
   // [drdx, drdy]
   // [dsdx, dsdy]
   // -equals-
   // 1/j * [dyds, -dxds]
   //       [-dydr, dxdr]
   
   j_inv[0][0]=mdXds[1][1]/j;
   j_inv[0][1]=-1*mdXds[0][1]/j;
   j_inv[1][0]=-1*mdXds[1][0]/j;
   j_inv[1][1]=mdXds[0][0]/j;
   
   return j_inv;
};
    
Matrix Mapping2D::dXds(point pt){
   int i;
   int j;
   int k;
   
   // dXds:
   // [dXdr, dXds]
   // [dYdr, dYds]
      
   Matrix dXds(nsd, npd);
   for (i=0;i<nsd;i++){
	   for(j=0;j<npd;j++){
		   dXds[i][j] = 0;
	   }
   }
   Matrix dNds = SF->dNds(pt);
   vector<Node*> nodes = Element->getNodes(); //assumes nodes are ordered
   
   for(i=0;i<nen;i++){ //loop over shape functions (one per node)
      for(j=0;j<nsd; j++){ //loop over global dimension (X)
         for(k=0;k<npd;k++){ //loop over local (shape) dimension (R)
			dXds[j][k]=dXds[j][k] + dNds[i][k] * nodes[i]->pt().X(j);
         }
      }
   }
   
   return dXds;
    
};

double Mapping2D::detJacobian(point pt){
   Matrix mdXds = dXds(pt);
   double j = mdXds[0][0] * mdXds[1][1] - mdXds[0][1] * mdXds[1][0];
   
   return j;
};


