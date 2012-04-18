/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
 
#include "magaxistaticsc.h"

#define PI 3.141592653589793238512808959406186204433

Matrix MagAxiStaticSC::evaluatePt(point pt){
   //nnd = # DOF/node
   //nen = # nodes/element   
	
   Matrix k(nnd*nen, nnd*nen);
   
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
   
   //The following call is a bit wasteful...
   //Matrix dsdx = Map->jacobianInverse(pt);
   
   //Get the interpolated radius of point pt.
   Vector N = SF->N(pt);
   double r = 0;
   vector<Node*> nodes = Element->getNodes();
   for(int i=0; i<nen; i++){
		r = r + nodes[i]->x() * N[i];
   }

   double s = r*r;
   
   double mu_r = Element->getClassification()->getAttribute("mu");
   double mu = mu_r * 4*PI*pow(10., -7);

   // The matrix dNdx contains the derivatives of the shape function
   // with respect to the global coordinates (x, y, z)
   // The first index of dNdx refers to the shape function number, in
   // this case the node number.  The second index refers to the global
   // coordinate number (ie. x=0, y=1, z=2)
	for(int i=0; i<nen; i++){
		for(int j=0; j<nen; j++){
			//k[i][j] = (1/mu)*(r*(dNdx[i][0]*dNdx[j][0]+dNdx[i][1]*dNdx[j][1])+(N[i]*dNdx[j][0]+N[j]*dNdx[i][0])+(N[i]*N[j])/r);
			//k[i][j] = (dNdx[i][0]*dNdx[j][0]+dNdx[i][1]*dNdx[j][1]);
			
			if (formulation==0){ //Approach 1: Do Nothing
				k[i][j] = (1/mu)*(r*(dNdx[i][0]*dNdx[j][0]+dNdx[i][1]*dNdx[j][1])+(N[i]*dNdx[j][0]+N[j]*dNdx[i][0])+(N[i]*N[j])/r);
			}else if(formulation==1){ //Approach 2: A' = A/sqrt(r) and J' = J/sqrt(r)
				k[i][j] = (1/mu)*(r*r*(dNdx[i][0]*dNdx[j][0]+dNdx[i][1]*dNdx[j][1])+1.5*r*(N[i]*dNdx[j][0]+N[j]*dNdx[i][0])+2.25*(N[i]*N[j]));
			}else{ //Approach 3: Transform s = r^2, W=rA
				k[i][j] = (1/mu)*(4*dNdx[i][0]*dNdx[j][0]+(1/s)*dNdx[i][1]*dNdx[j][1]);
			}
		}
	}
   
   return k;
   
}

