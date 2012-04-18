/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/
#include "lin1dsf.h"

Vector Lin1DSF::N(point pt){
   Vector mN(2);
   double eta = pt.x;
   
   mN[0]=0.5*(1-eta);
   mN[1]=0.5*(1+eta);
   
   return mN;
};

Matrix Lin1DSF::dNds(point pt){
   Matrix dN(2,1);
   double eta = pt.x;
   
   dN[0][0]=-0.5;
   dN[1][0]=0.5;
   
   return dN;
};

vector<point> Lin1DSF::IntPts(){
   //Should use explicit numbers to avoid extra floating point ops
   //for now leave as is so things are readable
   vector<point> int_pts(numIntPts());
   int_pts[0].x = -1/sqrt(3.);
   int_pts[1].x = 1/sqrt(3.);
      
   return int_pts;
};

Vector Lin1DSF::Weights(){
   Vector weights(numIntPts());
   weights[0] = 1;
   weights[1] = 1;
   
   return weights;
};

int Lin1DSF::numIntPts(){
   return 2;
};
