#ifndef FEPROG_H
#define FEPROG_H

#include "MeshDB/mesh.h"
#include "magaxistaticanalysis.h"
//#include <sstream>

class FEProg {

public:
	MagAxiStaticAnalysis* theAnalysis;
	FEProg();
	~FEProg();
	Mesh* run_FEA(char* filename, int formulation);
	//ostringstream outStream;

};
	
#endif