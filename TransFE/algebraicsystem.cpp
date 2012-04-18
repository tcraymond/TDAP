/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
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
