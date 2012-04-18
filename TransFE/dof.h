/************************************************************************
  			dof.h - Copyright T. C. Raymond

**************************************************************************/

#ifndef DOF_H
#define DOF_H

#define DOF_STATUS int
#define DOF_Free 1
#define DOF_Zero 2
#define DOF_Fixed 3

extern int ndof;

/// This class represents a Degree of Freedom (DOF). 

class DOF {

public:

   ///Default constructor
   DOF(){
      value=0;
      status=DOF_Free;
      eq_number=0;
      ndof++;
   }

   ~DOF(){
	   if(status==DOF_Free){
	      ndof--;
	   }
   }

   void set_value(double);
   double get_value();
   
   void set_status(DOF_STATUS);
   DOF_STATUS get_status();
   
   void set_eqnumber(long);
   long get_eqnumber();
  
protected:
  
private:

   double value;
   DOF_STATUS status;
   long eq_number;  //the number of nodes could be limited by the size of this variable
  
};

#endif //DOF_H

