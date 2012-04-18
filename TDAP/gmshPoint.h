#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;

public ref class gmshPoint
{
public:
	gmshPoint(void);
	gmshPoint(double in_x, double in_y, double in_z);
	void write(StreamWriter^ sw);
	int ID;
	double x;
	double y;
	double z;
};