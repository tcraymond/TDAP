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
 
#ifndef POINT_H
#define POINT_H

///The point class is a container for 3D (and 2D) spatial coordinates.

class point{
public:

   ///Default contructor
   point(){
      //initialize to an oddball number in hopes of catching unitialized uses
      x=-999;
      y=-999;
      z=-999;
   };
   
   ///A contructor for 2D points, passing in x & y coordinates
   point(double in_x, double in_y){
      x=in_x;
      y=in_y;
      z=0;
   };
   
   ///A contructor for 3D points, passing in x, y & z coordinates
   point(double in_x, double in_y, double in_z){
      x=in_x;
      y=in_y;
      z=in_z;
   };

   ///Default destructor
   ~point(){};
   
   ///The x coordinate
   double x;
   ///The y coordinate
   double y;
   ///The z coordinate
   double z;
   
   ///Returns the i-th coordinate.  This is useful in loops.
   double X(int n){
      if(n==0){
         return x;
      } else if(n==1){
         return y;
      } else if(n==2){
         return z;
      } else {
         return -1;
      }
   };

};

#endif
