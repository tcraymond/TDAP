#pragma once

#include "gmshPoint.h"
#include "gmshLine.h"
#include "gmshLineLoop.h"

ref class gmshFile
{
public:
	gmshFile(void);
	gmshFile(String^ out_file);
	String^ filename;
	List<gmshPoint^>^ points;
	List<gmshLine^>^ lines;
	List<gmshLineLoop^>^ line_loops;
	void gmshRectangle(double ll_x, double ll_y, double ur_x, double ur_y);
	void writeFile();
	int ElementOrder;
};
