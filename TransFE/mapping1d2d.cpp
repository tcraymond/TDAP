/***************************************************************************
 *   Copyright (c) 2012 by Timothy C. Raymond                              *
 *   tc.raymond@ieee.org												   *
 *   All rights reserved.												   *
 *                                                                         *
 *   Redistribution and use in source and binary forms, with or without    *
 *   modification, are permitted provided that the following conditions    *
 *   are met:                                                              *
 *      - Redistributions of source code must retain the above copyright   *
 *        notice, this list of conditions and the following disclaimer.    *
 *      - Redistributions in binary form must reproduce the above          *
 *        copyright notice, this list of conditions and the following      *
 *		  disclaimer in the documentation and/or other materials provided  *
 *		  with the distribution.                                           *
 *                                                                         *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS     *
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  *
 *   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
 *   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      *
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      *
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT    *
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN     *
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
 *   POSSIBILITY OF SUCH DAMAGE.                                           *
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
