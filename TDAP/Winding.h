#pragma once

#include "Section.h"
#include "gmshFile.h"

using namespace System;
using namespace System::Collections::Generic;

ref class Transformer;

public ref class Winding
{
public:
	
	Winding(void);
	String^ name;
	double voltage;
	String^ connection;
	double MVA;
	int currDir;
	List<Section^>^ sections;

	[XmlIgnore]
	Transformer^ transformer; //To link back to parent

	Section^ addSection();
	void writeSectionsGmsh(gmshFile^ outFile);

	double totalArea();
	int totalTurns();
	double Current();
};
