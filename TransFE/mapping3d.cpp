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
 
#include "mapping3d.h"

Matrix Mapping3D::jacobianInverse(point pt){
   Matrix j_inv(npd, nsd);
   Matrix mdXds = dXds(pt);
   double j = detJacobian(pt);
   
   // j_inv = dSdX
   // [drdx, drdy]
   // [dsdx, dsdy]
   // -equals-
   // 1/j * [dyds, -dxds]
   //       [-dydr, dxdr]

   double cof_11 = mdXds[1][1]*mdXds[2][2]-mdXds[1][2]*mdXds[2][1];
   double cof_12 = mdXds[1][2]*mdXds[2][0]-mdXds[1][0]*mdXds[2][2];
   double cof_13 = mdXds[1][0]*mdXds[2][1]-mdXds[1][1]*mdXds[2][0];
   double cof_21 = mdXds[2][1]*mdXds[0][2]-mdXds[2][2]*mdXds[0][1];
   double cof_22 = mdXds[2][2]*mdXds[0][0]-mdXds[2][0]*mdXds[0][2];
   double cof_23 = mdXds[2][0]*mdXds[0][1]-mdXds[2][1]*mdXds[0][0];
   double cof_31 = mdXds[0][1]*mdXds[1][2]-mdXds[0][2]*mdXds[1][1];
   double cof_32 = mdXds[0][2]*mdXds[1][0]-mdXds[0][0]*mdXds[1][2];
   double cof_33 = mdXds[0][0]*mdXds[1][1]-mdXds[0][1]*mdXds[1][0];
   
   j_inv[0][0]=cof_11/j;
   j_inv[1][0]=cof_12/j;
   j_inv[2][0]=cof_13/j;
   j_inv[0][1]=cof_21/j;
   j_inv[1][1]=cof_22/j;
   j_inv[2][1]=cof_23/j;
   j_inv[0][2]=cof_31/j;
   j_inv[1][2]=cof_32/j;
   j_inv[2][2]=cof_33/j;

   vector<Node*> nodes = Element->getNodes();
   cout << "Nodes in region" << endl;
   for(int j=0;j<4;j++){
      cout << "Node #" << j << ": x=" << nodes[j]->pt().X(0) << " y=" << nodes[j]->pt().X(1) << " z=" << nodes[j]->pt().X(2) << endl;
   }

   cout << "dSdX:" << endl;
   cout << j_inv << endl;   
   
   return j_inv;
};
    
Matrix Mapping3D::dXds(point pt){
   int i;
   int j;
   int k;
   
   // dXds:
   // [dXdxi, dXdeta, dXdzeta]
   // [dYdxi, dYdeta, dYdzeta]
   // [dZdxi, dZdeta, dZdzeta]
      
   Matrix dXds(nsd, npd);
   Matrix dNds = SF->dNds(pt);
   vector<Node*> nodes = Element->getNodes(); //assumes nodes are ordered
   
   //cout << "dNds:" << endl;
   //cout << dNds << endl;

   //for(i=0;i<nen;i++){
   //   cout << "Node #" << i << ": x=" << nodes[i]->pt().X(0) << " y=" << nodes[i]->pt().X(1) << " z=" << nodes[i]->pt().X(2) << endl;
   //}
   
   for(i=0;i<nen;i++){ //loop over shape functions (one per node)
      for(j=0;j<nsd; j++){ //loop over global dimension (X)
         for(k=0;k<npd;k++){ //loop over local (shape) dimension (R)
	    dXds[j][k]=dXds[j][k] + dNds[i][k] * nodes[i]->pt().X(j);
         }
      }
   }
   
   return dXds;
    
};

double Mapping3D::detJacobian(point pt){
   Matrix mdXds = dXds(pt);
   //cout << "dXds:" << endl;
   //cout << mdXds << endl;
   double cof_11 = mdXds[1][1]*mdXds[2][2]-mdXds[1][2]*mdXds[2][1];
   double cof_12 = mdXds[1][2]*mdXds[2][0]-mdXds[1][0]*mdXds[2][2];
   double cof_13 = mdXds[1][0]*mdXds[2][1]-mdXds[1][1]*mdXds[2][0];
   
   double j = mdXds[0][0]*cof_11+mdXds[0][1]*cof_12+mdXds[0][2]*cof_13;
   if(j==0){
      cerr << "Zero jacobian!" << endl;
      exit(1);
   }
   //cout << "j=" << j << endl;
   return j;
};


