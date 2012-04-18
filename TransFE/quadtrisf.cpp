/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#include "quadtrisf.h"

Vector QuadTriSF::N(point pt){
   Vector mN(6);
   double r = pt.x;
   double s = pt.y;
   double t = 1.-r-s;
   mN[0]=r*(2.*r-1.);
   mN[1]=s*(2.*s-1.);
   mN[2]=t*(2.*t-1.); //=(1-r-s)*(2*(1-r-s)-1)=
   mN[3]=4.*r*s;
   mN[4]=4.*s*t; //=4s-4rs-4s^2
   mN[5]=4.*r*t; //=4r-4rs-4r^2
   return mN;
};

Matrix QuadTriSF::dNds(point pt){
   Matrix dN(6,2);
   double r = pt.x;
   double s = pt.y;
   dN[0][0]=4.*r-1.;
   dN[0][1]=0.;
   dN[1][0]=0.;
   dN[1][1]=4.*s-1.;
   dN[2][0]=-3.+4.*s+4.*r;
   dN[2][1]=-3.+4.*r+4.*s;
   dN[3][0]=4.*s;
   dN[3][1]=4.*r;
   dN[4][0]=-4.*s;
   dN[4][1]=4.-4.*r-8.*s;
   dN[5][0]=4.-4.*s-8.*r;
   dN[5][1]=-4.*r;
   
   return dN;
};

vector<point> QuadTriSF::IntPts(){
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

Vector QuadTriSF::Weights(){
   Vector weights(numIntPts());
   weights[0] = 1./6.;
   weights[1] = 1./6.;
   weights[2] = 1./6.;
   
   return weights;
};

int QuadTriSF::numIntPts(){
   return 3;
};
