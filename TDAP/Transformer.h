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
