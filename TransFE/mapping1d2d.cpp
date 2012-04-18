/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#include "mapping1d2d.h"

//This is a 2D mapping of a 1D line

Matrix Mapping1D2D::jacobianInverse(point pt){
   Matrix j_inv(nsd, nsd);
   Matrix mdXds = dXds(pt);
   double j = detJacobian(pt);
   
   //j_inv[0][0]=mdXds[1][1]/j;
   //j_inv[0][1]=-1*mdXds[0][1]/j;
   //j_inv[1][0]=-1*mdXds[1][0]/j;
   //j_inv[1][1]=mdXds[0][0]/j;
   
   return j_inv;
};
    
Matrix Mapping1D2D::dXds(point pt){
   int i;
   int j;
   int k;
   
   // dXds:
   // [dXdr]
   // [dYdr]
      
   Matrix dXds(nsd, npd);
   Matrix dNds = SF->dNds(pt);
   vector<Node*> nodes = Element->getNodes();
   
   for(i=0;i<nen;i++){
      for(j=0;j<nsd; j++){
         for(k=0;k<npd;k++){
	    dXds[j][k]=dXds[j][k] + dNds[i][k] * nodes[i]->pt().X(j);
         }
      }
   }
   
   return dXds;
    
};

double Mapping1D2D::detJacobian(point pt){
  /* Matrix mdXds = dXds(pt);
   double j;// = mdXds[0][0] * mdXds[1][1] - mdXds[0][1]*mdXds[1][0];
   
   return j; */
	return 0;
};
