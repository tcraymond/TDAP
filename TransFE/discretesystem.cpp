/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
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
