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

#ifndef NODE_H
#define NODE_H

#include "..\dof.h"
#include "point.h"
#include <vector>

using namespace std;

/// This class represents a Node.  A node is the geometric (or parametric?)
/// manifestation of a point on the mesh.  A node may also be termed a
/// "degree of freedom holder".  Each vertex must have one node.  In addition, edges
/// may also have a node for 2nd order elements.

class Node {

public:

   /// The x-coordinates
   double x(){
      return m_pt.X(0);
   }
   
   /// The y-coordinate
   double y(){
      return m_pt.X(1);
   }
   
   /// The z-coordinate
   double z(){
      return m_pt.X(2);
   }
   
   /// Set the nodes point
   void pt(point in_pt){
      m_pt = in_pt;
   }
   
   ///Retrieve the nodes point
   point pt(){
      return m_pt;
   }
   
   /// An optional integer ID
   int ID;
  
   /// Default constructor.
   Node ( ) { }

   ~Node();
  
   /// The equals operator is overridden in attempt to provide a meaningful definition
   friend bool operator== (Node&, Node&);
  
   /// Returns ordering based upon the x-dimension
   friend bool operator< (Node&, Node&);
   
   /// Return a vector with pointers to the nodal DOFs
   vector<DOF*> getDOFs();
   
   /// Create a new DOF for this node
   DOF* newDOF();
  
protected:
  
private:
   /// A vector with pointers to all of the nodal DOFs
   vector<DOF*> DOFs;
   /// A point for the spatial coordinates of this node
   point m_pt;
  
};
#endif //NODE_H

