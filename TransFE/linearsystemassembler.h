/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#ifndef LINEARSYSTEMASSEMBLER_H
#define LINEARSYSTEMASSEMBLER_H

#include "assembler.h"
#include <vector>
#include "dof.h"
#include "typedefs.h"

class DOF;

/// This class represents a linear system assembler. 

class LinearSystemAssembler : public Assembler{

public:

   virtual void accept(Matrix, vector<DOF*> dofs);   

   virtual void accept(Vector, vector<DOF*> dofs);
  
protected:
  
private:

};
#endif //LINEARSYSTEMASSEMBLER_H

