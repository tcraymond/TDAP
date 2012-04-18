/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
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

