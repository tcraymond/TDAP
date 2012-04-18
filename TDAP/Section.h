#pragma once

#include "gmshFile.h"

using namespace System;
using namespace System::Xml::Serialization;

ref class Winding;

public ref class Section
{
public:
	Section(void);

	[XmlIgnore]
	Winding^ winding;

	String^ name;
	int turns_rad;
	int turns_axi;
	int strands_per_turn;
	double radius_inner;
	double radius_outer;
	double height;
	double h_abv_yoke;

	//Calculated values (ignore for input file)
	[XmlIgnore]
	double F_r; //Total radial force for section
	[XmlIgnore]
	double F_z; //Total axial force for section
	
	void writeSectionGmsh(gmshFile^ outFile);

	double Area();
	int Turns();
	double CurrentDensity();
};
