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
