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

#pragma once

#include "Core.h"
#include "gmshFile.h"
#include "..\TransFE\MeshDB\Mesh.h"
#include <sstream>
#include "..\TransFE\feprog.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Xml::Serialization;
using namespace System::Diagnostics;
//using namespace System::Drawing::Drawing2D;

ref class Winding;

public ref class Transformer
{
public:
	Transformer(void);
	String^ name;
	List<Winding^>^ windings;
	Core^ core;
	double dist_WdgTnk;
	int numPhases;
	double I_base;
	double X_pu;

	[XmlIgnore]
	Mesh* feaMesh;

	[XmlIgnore]
	String^ filename;

	[XmlIgnore]
	FEProg* feprog;

	//[XmlIgnore]
	//ostringstream* outStream;

	Winding^ addWinding();
	void deleteWinding(Winding^ deletedWinding);
	void writeWindingsGmsh(gmshFile^ outFile);
	void writeTransformerGmsh(String^ filename);
	void writeAttributes(String^ filename);
	void runFEA();
	void calcX();
	void CalcF();
	double A(double r, double y);
	void contourPlot();
	void setFilename(String^ filename);
//	ostringstream* getStream();

	int formulation;
	int ElementOrder;
};
