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