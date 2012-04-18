#include "StdAfx.h"
#include "gmshLine.h"

gmshLine::gmshLine(void)
{
	pt1 = nullptr;
	pt2 = nullptr;
	ID = -9999;
}

gmshLine::gmshLine(gmshPoint^ in_pt1, gmshPoint^ in_pt2){
	pt1 = in_pt1;
	pt2 = in_pt2;
	ID = -9999;
}

void gmshLine::write(StreamWriter^ sw){
	sw->WriteLine("Line ({0}) = {{{1}, {2}}};", ID, pt1->ID, pt2->ID);
}