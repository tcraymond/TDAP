#include "StdAfx.h"
#include "Section.h"
#include "Winding.h"

Section::Section(void)
{
}

void Section::writeSectionGmsh(gmshFile^ outFile){
	outFile->gmshRectangle(radius_inner, h_abv_yoke, radius_outer, h_abv_yoke + height);
/*	fprintf(stream, "Point (%d) = {%f, %f, 0, lc};", next_pt, radius_inner, h_abv_yoke); //lower left corner
	fprintf(stream, "Point (%d) = {%f, %f, 0, lc};", next_pt + 1, radius_inner, h_abv_yoke + height); //upper left corner
	fprintf(stream, "Point (%d) = {%f, %f, 0, lc};", next_pt + 2, radius_outer, h_abv_yoke); //lower right corner
	fprintf(stream, "Point (%d) = {%f, %f, 0, lc};", next_pt + 3, radius_outer, h_abv_yoke + height); //upper right corner
	fprintf(stream, "Line (%d) = {%d, %d};", next_line, next_pt, next_pt + 1); //left side
	fprintf(stream, "Line (%d) = {%d, %d};", next_line + 1, next_pt + 1, next_pt + 3); //top
	fprintf(stream, "Line (%d) = {%d, %d};", next_line + 1, next_pt + 3, next_pt + 2); //right side
	fprintf(stream, "Line (%d) = {%d, %d};", next_line + 1, next_pt + 2, next_pt); //bottom
	fprintf(stream, "Line Loop (%d) = {%d, %d, %d, %d};", next_section, next_line, next_line + 1, next_line + 2, next_line + 3);
*/
}

double Section::Area(){
	double area = height * (radius_outer - radius_inner);
	return area;
}

int Section::NumTurns(){
	int turns = turns_rad * turns_axi;
	return turns;
}

double Section::CurrentDensity(){
	double J;
	J = 3600 / winding->totalArea();
	return J;
}

void Section::BuildTurns(){
	turns->Add(
}