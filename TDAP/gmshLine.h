#pragma once

#include "gmshPoint.h"

ref class gmshLine
{
public:
	gmshLine(void);
	gmshLine(gmshPoint^ in_pt1, gmshPoint^ in_pt2);
	void write(StreamWriter^ sw);
	int ID;
	gmshPoint^ pt1;
	gmshPoint^ pt2;
};
