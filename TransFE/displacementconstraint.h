/************************************************************************
  			displacementconstraint.h - Copyright T. C. Raymond

**************************************************************************/

#ifndef DISPLACEMENTCONSTRAINT_H
#define DISPLACEMENTCONSTRAINT_H

#include "constraint.h"
#include "MeshDB/meshedge.h"
#include "mapping.h"
#include "shapefunction.h"


/// This class represents a displacement constraint. 

class DisplacementConstraint : public Constraint {

public:

   DisplacementConstraint(MeshEntity* Element_in):Constraint(Element_in){};  

   ~DisplacementConstraint();

   void apply();
  
protected:
  
private:

};
#endif //DISPLACEMENTCONSTRAINT_H

