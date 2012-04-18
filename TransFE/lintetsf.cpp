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
