/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#include "dof.h"

int ndof;

void DOF::set_value(double dof_value){
   value = dof_value;
}

double DOF::get_value(){
   return value;
}
   
void DOF::set_status(DOF_STATUS dof_status){
   
   if(status==DOF_Free && dof_status!=DOF_Free){
      ndof=ndof-1;
   }
   status = dof_status;
}

DOF_STATUS DOF::get_status(){
   return status;
}

void DOF::set_eqnumber(long eqnumber){
   eq_number = eqnumber; //probably should check for overflow here
}

long DOF::get_eqnumber(){
   return eq_number;
}
