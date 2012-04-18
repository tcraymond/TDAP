/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#include "lintetsf.h"

Vector LinTetSF::N(point pt){
   Vector mN(4);
   double r = pt.x;
   double s = pt.y;
   double t = pt.z;
   mN[0]=r;
   mN[1]=s;
   mN[2]=t;
   mN[3]=1-r-s-t;
   return mN;
};

Matrix LinTetSF::dNds(point pt){
   Matrix dN(4,3);
   double r = pt.x;
   double s = pt.y;
   double t = pt.z;
   dN[0][0]=1.;
   dN[0][1]=0.;
   dN[0][2]=0.;
   dN[1][0]=0.;
   dN[1][1]=1.;
   dN[1][2]=0.;
   dN[2][0]=0.;
   dN[2][1]=0.;
   dN[2][2]=1.;
   dN[3][0]=-1.;
   dN[3][1]=-1.;
   dN[3][2]=-1.;
   return dN;
};

vector<point> LinTetSF::IntPts(){
   //Should use explicit numbers to avoid extra floating point ops
   //for now leave as is so things are readable
   vector<point> int_pts(numIntPts());
   int_pts[0].x = 0.25;
   int_pts[0].y = 0.25;
   int_pts[0].z = 0.25;
      
   return int_pts;
};

Vector LinTetSF::Weights(){
   Vector weights(numIntPts());
   weights[0] = 1./6.;
      
   return weights;
};

int LinTetSF::numIntPts(){
   return 1;
};
