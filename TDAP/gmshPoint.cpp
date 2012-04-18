#include "StdAfx.h"
#include "gmshPoint.h"

gmshPoint::gmshPoint(void)
{
	x=0;
	y=0;
	z=0;
	ID=-9999;
}

gmshPoint::gmshPoint(double in_x, double in_y, double in_z)
{
	x=in_x;
	y=in_y;
	z=in_z;
	ID=-9999;
}

void gmshPoint::write(StreamWriter^ sw){
	sw->WriteLine("Point ({0}) = {{{1}, {2}, {3}, lc}};", ID, x, y, z);
}