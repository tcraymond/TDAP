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

#include "algebraicsystem.h"

#include "itl/interface/mtl.h"
#include "itl/preconditioner/ssor.h"
#include "itl/krylov/qmr.h"
#include "itl/krylov/bicgstab.h"

using namespace itl;

AlgebraicSystem::~AlgebraicSystem(){
	
//	delete d;
//	delete f;
}

void AlgebraicSystem::solve(){
   DS->initializeSystem();
   createGlobalSystem();
   A->initialize(&K, &f);
   DS->formSystem(A);
   solveLinearSystem();
};

void AlgebraicSystem::createGlobalSystem(){
   mesh->reorder2();
   K = SparseMatrix(ndof, ndof);
   d = BigVector(ndof);
   f = BigVector(ndof);
};

void AlgebraicSystem::solveLinearSystem(){
   //Solve Kd = f
   int max_iter = 1000;
/*   
   cout << "K = :" << endl;
  for(unsigned int i=0;i<ndof; i++){
	  for(unsigned int j=0;j<ndof;j++){

			cout << K[i][j] << "  ";
	  }
	  cout << endl;
  }
   
   cout << "f = :" << endl;
  for(unsigned int i=0;i<ndof; i++){
   cout << f[i] << endl;
  }
  */
#if 1   
   //SSOR preconditioner
  SSOR<SparseMatrix> precond(K);
  //identity_preconditioner precond;
  //iteration
  noisy_iteration<double> iter(f, max_iter, 1e-6);
  //qmr algorithm
  qmr(K, d, f, precond.left(), precond.right(), iter);
  //end
  
#else
  
  //SSOR preconditioner
  itl::SSOR<SparseMatrix> precond(K);
  //iteration
  itl::noisy_iteration<double> iter(f, max_iter, 1e-6);
  //bicgstab algorithm
  itl::bicgstab(K, d, f, precond(), iter);
  //end
#endif
  
  //cout << "d = :" << endl;
  //for(int i=0;i<ndof; i++){
  // cout << d[i] << endl;
  //}
};

BigVector AlgebraicSystem::get_d(){
   return d;
};
