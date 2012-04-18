/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#include "linearsystemassembler.h"

void LinearSystemAssembler::accept(Matrix k, vector<DOF*> dofs){
	//given a stiffness contributor stiffness matrix and list of associated DOF objects
	//add into global matrix
	int i, j;
	int ki, kj, kc;
	int size = dofs.size();
	for(i=0; i< size; i++){ //loop over rows of stiffness contributor
		DOF* idof = dofs[i]; //get ith degree of freedom from the DOF list
		ki = idof->get_eqnumber(); //get global equation number for row from the DOF object
		//cout << "ki=" << ki << endl;
		for(j=0; j < size; j++){ //for the current row, loop over the columns of the local stiffness matrix
			DOF* jdof = dofs[j]; //get jth degree of freedom from the DOF list
			kj = jdof->get_eqnumber();  //get global equation number for the column from the DOF object
			//cout << "kj=" << kj << endl;
			if(kj >= ki){ //check to make sure this term is in the upper triangle
				if(jdof->get_status()==DOF_Free && idof->get_status()==DOF_Free){
					(*K)(ki,kj) = (*K)(ki,kj) + k[i][j]; //add the local stifness term to the global stiffness matrix
				}else{ //if both not free, then one or both are constrained
					//If one of the dofs is constrained as Fixed and the other is free, proper term must
					//go in load vector
					DOF* cdof=NULL; //weill need the value of the non-zero essential BC from the DOF
					if(jdof->get_status()==DOF_Free && idof->get_status()==DOF_Fixed){ //adds to the kj force term
						kc = kj;
						cdof = idof;
					}else if(idof->get_status()==DOF_Free && jdof->get_status()==DOF_Fixed){ //adds to the ki force term
						kc = ki;
						cdof = jdof;
					}
					//kc is the equation number, cdof is the constrained dof
					//cout << "Stiffness value = " << endl << k << endl;
					if(cdof!=NULL){
						(*f)[kc] = (*f)[kc] - cdof->get_value()*k[i][j];
					}
				}
			}
		}
	}
}

void LinearSystemAssembler::accept(Vector local_f, vector<DOF*>dofs){
	int i;
	int ki;
	int size = dofs.size();
	for(i=0; i< size; i++){ //loop over rows of force contributor
		DOF* idof = dofs[i]; //get ith degree of freedom from the DOF list
		ki = idof->get_eqnumber(); //get global equation number for row from the DOF object
		if(idof->get_status()==DOF_Free){
			//cout << "Adding force term..." << endl;
			(*f)[ki] = (*f)[ki] + local_f[i]; //add the local force term to the global force vector
		}else{ //if not free, then constrained
			//doing nothing...
		}
	}
};
