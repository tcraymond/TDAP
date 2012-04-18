/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#include "lintrisf.h"

Vector LinTriSF::N(point pt){
   Vector mN(3);
   double r = pt.x;
   double s = pt.y;
   double t = 1.-r-s;
   mN[0]=r;
   mN[1]=s;
   mN[2]=t;
   return mN;
};

Matrix LinTriSF::dNds(point pt){
   Matrix dN(3,2);
   double r = pt.x;
   double s = pt.y;
   dN[0][0]=1.;
   dN[0][1]=0.;
   dN[1][0]=0.;
   dN[1][1]=1.;
   dN[2][0]=-1.;
   dN[2][1]=-1.;
   return dN;
};

vector<point> LinTriSF::IntPts(){
   //Should use explicit numbers to avoid extra floating point ops
   //for now leave as is so things are readable
   vector<point> int_pts(numIntPts());
   int_pts[0].x = 2./3.;
   int_pts[0].y = 1./6.;
   int_pts[1].x = 1./6.;
   int_pts[1].y = 1./6.;
   int_pts[2].x = 1./6.;
   int_pts[2].y = 2./3.;
   
   return int_pts;
};

Vector LinTriSF::Weights(){
   Vector weights(numIntPts());
   weights[0] = 1./6.;
   weights[1] = 1./6.;
   weights[2] = 1./6.;
   
   return weights;
};

int LinTriSF::numIntPts(){
   return 3;
};
