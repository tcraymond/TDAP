/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#include "quad1dsf.h"

Vector Quad1DSF::N(point pt){
   Vector mN(3);
   double xi = pt.x;
   
   //note: the node ordering convention for this program is that end points
   //are listed first, followed by the point on the edge
   mN[0]=0.5*xi*(xi-1.); //xi^2/2-xi/2
   mN[1]=0.5*xi*(xi+1.); //xi^2/2+xi/2
   mN[2]=1.-xi*xi; //1-xi^2
   
   return mN;
};

Matrix Quad1DSF::dNds(point pt){
   Matrix dN(3,1);
   double xi = pt.x;
   
   dN[0][0]=xi-0.5;
   dN[1][0]=xi+0.5;
   dN[2][0]=-2.*xi;
   
   return dN;
};

vector<point> Quad1DSF::IntPts(){
   //Should use explicit numbers to avoid extra floating point ops
   //for now leave as is so things are readable
   vector<point> int_pts(numIntPts());
   int_pts[0].x = -1./sqrt(3.);
   int_pts[1].x = 1./sqrt(3.);
      
   return int_pts;
};

Vector Quad1DSF::Weights(){
   Vector weights(numIntPts());
   weights[0] = 1.;
   weights[1] = 1.;
   
   return weights;
};

int Quad1DSF::numIntPts(){
   return 2;
};
