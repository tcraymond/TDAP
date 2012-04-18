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

#include "elasticityfc.h"

Vector ElasticityFC::evaluatePt(point pt){
   Vector forces(nnd * nen);
   Vector forces_x(nen);
   Vector forces_y(nen);
   
   Matrix dXds = Map->dXds(pt);
   
   double F_x = Element->getClassification()->getAttribute("F_x");
   double F_y = Element->getClassification()->getAttribute("F_y");
   
   //In the case of surface tractions, F_x is the tangential traction and
   //F_y is the normal traction
      
   forces_x = SF->N(pt) * (F_x*dXds[0][0]+F_y*dXds[1][0]);
   forces_y = SF->N(pt) * (F_x*dXds[1][0]-F_y*dXds[0][0]);
   
   for(int i=0;i<nen;i++){
      forces[2*i] = forces_x[i];
      forces[2*i+1] = forces_y[i];
   }
   
   return forces;
   
};



