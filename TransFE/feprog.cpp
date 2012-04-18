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


#ifdef HAVE_CONFIG_H
//#include <config.h>
#endif

#include "feprog.h"

#include <iostream>
#include <cstdlib>
#include "MeshDB/mesh.h"
#include "elasticityanalysis.h"
#include "magaxistaticanalysis.h"

#include "MeshDB/meshface.h"
#include "lintrisf.h"
#include "mapping2d.h"

#include "precisiontimer.h"

using namespace std;

FEProg::FEProg(){
	theAnalysis = new MagAxiStaticAnalysis(0);
}

FEProg::~FEProg(){
	delete theAnalysis;
}

Mesh* FEProg::run_FEA(char* filename, int formulation)
{  
	
	if(theAnalysis!=NULL){
		delete theAnalysis;
		//theAnalysis = new MagAxiStaticAnalysis();
	}

	theAnalysis = new MagAxiStaticAnalysis(formulation);
//   outStream << "Running 2D magnetostatic analysis" << endl;
//   outStream << "Reading attrbiutes from " << filename << ".att" << endl;
   theAnalysis->getMesh()->readAttributes(filename);
//   outStream << "Finished reading attributes" << endl;
//   outStream << "Reading mesh from " << filename << ".msh" << endl;
   theAnalysis->getMesh()->readMesh(filename);
//   outStream << "Finished reading mesh" << endl;
   theAnalysis->getMesh()->reorder();
//   outStream << "Running the analysis" << endl;
   theAnalysis->run();
   theAnalysis->saveOut(filename);
//   outStream << "Finished running the analysis" << endl;
   
   return theAnalysis->getMesh();
   
	return new Mesh();
}

