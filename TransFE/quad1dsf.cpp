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
