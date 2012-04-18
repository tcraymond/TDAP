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


#include "discretesystem.h"
#include "precisiontimer.h"

DiscreteSystem::~DiscreteSystem(){
	list<StiffnessContributor*>::iterator stiff_iter;
	for(stiff_iter=StiffnessContributors.begin();stiff_iter!=StiffnessContributors.end();++stiff_iter){
		delete (*stiff_iter);
	}

	list<ForceContributor*>::iterator force_iter;
	for(force_iter=ForceContributors.begin();force_iter!=ForceContributors.end();++force_iter){
		delete (*force_iter);
	}

	list<Constraint*>::iterator cons_iter;
	for(cons_iter=Constraints.begin();cons_iter!=Constraints.end();++cons_iter){
		delete (*cons_iter);
	}
};

void DiscreteSystem::add(StiffnessContributor* sc){
   StiffnessContributors.push_back(sc);
};

void DiscreteSystem::add(ForceContributor* fc){
   ForceContributors.push_back(fc);
};

void DiscreteSystem::add(Constraint* c){
   Constraints.push_back(c);
};

void DiscreteSystem::initializeSystem(){
   list<Constraint*>::iterator constraint_iter;
   for(constraint_iter=Constraints.begin();constraint_iter!=Constraints.end();++constraint_iter){
      (*constraint_iter)->apply(); //each essential boundary condition will eliminate possible dof from the global system
                               //in the case of non-zero essential boundary conditions must also get the non-zero value
   }
}

void DiscreteSystem::formSystem(Assembler* assem){
   cout << "Forming system" << endl;
   list<ForceContributor*>::iterator FC_iter;
   for(FC_iter=ForceContributors.begin();FC_iter!=ForceContributors.end();++FC_iter){
      cout << "Evaluating force contributor" << endl;
      (*FC_iter)->evaluate(assem);
   }
      
   list<StiffnessContributor*>::iterator SC_iter;
   for(SC_iter=StiffnessContributors.begin();SC_iter!=StiffnessContributors.end();++SC_iter){
	   cout << "Evaluating stiffness contributor" << endl;
      (*SC_iter)->evaluate(assem);
   }
}
