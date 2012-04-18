/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#include "linquadsf.h"

Vector LinQuadSF::N(point pt){
   Vector mN(4);
   double xi = pt.x;
   double eta = pt.y;
   mN[0]=(1.-xi)*(1.-eta)/4.;
   mN[1]=(1.+xi)*(1.-eta)/4.;
   mN[2]=(1.+xi)*(1.+eta)/4.;
   mN[3]=(1.-xi)*(1.+eta)/4.;
   return mN;
};

Matrix LinQuadSF::dNds(point pt){
   Matrix dN(4,2);
   double xi = pt.x;
   double eta = pt.y;
   dN[0][0]=(-1.+eta)/4.;
   dN[0][1]=(-1.+xi)/4.;
   dN[1][0]=(1.-eta)/4.;
   dN[1][1]=(-1.-xi)/4.;
   dN[2][0]=(1.+eta)/4.;
   dN[2][1]=(1.+xi)/4.;
   dN[3][0]=(-1.-eta)/4.;
   dN[3][1]=(1.-xi)/4.;
   return dN;
};

vector<point> LinQuadSF::IntPts(){
   //Should use explicit numbers to avoid extra floating point ops
   //for now leave as is so things are readable
   vector<point> int_pts(numIntPts());
   double n = 1/sqrt(3.);
   int_pts[0].x = -n;
   int_pts[0].y = -n;
   int_pts[1].x = n;
   int_pts[1].y = -n;
   int_pts[2].x = n;
   int_pts[2].y = n;
   int_pts[3].x = -n;
   int_pts[3].y = n;
   
   return int_pts;
};

Vector LinQuadSF::Weights(){
   Vector weights(numIntPts());
   weights[0] = 1.;
   weights[1] = 1.;
   weights[2] = 1.;
   weights[3] = 1.;
   
   return weights;
};

int LinQuadSF::numIntPts(){
   return 4;
};
