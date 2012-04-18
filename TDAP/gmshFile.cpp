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
#include "gmshFile.h"

gmshFile::gmshFile(void)
{
	filename = "";
	points = gcnew List<gmshPoint^>;
	lines = gcnew List<gmshLine^>;
	line_loops = gcnew List<gmshLineLoop^>;
}

gmshFile::gmshFile(String^ out_file){
	filename = out_file;
	points = gcnew List<gmshPoint^>;
	lines = gcnew List<gmshLine^>;
	line_loops = gcnew List<gmshLineLoop^>;
}

void gmshFile::gmshRectangle(double ll_x, double ll_y, double ur_x, double ur_y){
	gmshPoint^ ll = gcnew gmshPoint(ll_x, ll_y, 0);
	gmshPoint^ lr = gcnew gmshPoint(ur_x, ll_y, 0);
	gmshPoint^ ur = gcnew gmshPoint(ur_x, ur_y, 0);
	gmshPoint^ ul = gcnew gmshPoint(ll_x, ur_y, 0);
	points->Add(ll);
	points->Add(lr);
	points->Add(ur);
	points->Add(ul);
	gmshLine^ bottom = gcnew gmshLine(ll, lr);
	gmshLine^ right = gcnew gmshLine(lr, ur);
	gmshLine^ top = gcnew gmshLine(ur, ul);
	gmshLine^ left = gcnew gmshLine(ul, ll);
	lines->Add(bottom);
	lines->Add(right);
	lines->Add(top);
	lines->Add(left);
	List<gmshLine^>^ rect_lines = gcnew List<gmshLine^>;
	rect_lines->Add(bottom);
	rect_lines->Add(right);
	rect_lines->Add(top);
	rect_lines->Add(left);
	gmshLineLoop^ rect = gcnew gmshLineLoop(rect_lines);
	line_loops->Add(rect);
}

void gmshFile::writeFile(){
	StreamWriter^ sw = File::CreateText(filename);
	sw->WriteLine("lc = 0.02;");
	sw->WriteLine("Mesh.ElementOrder = " + ElementOrder + ";");

	int point_ID = 0;
	for each (gmshPoint^ point in points){
		point_ID++;
		point->ID = point_ID;
		point->write(sw);
	}

	int line_ID = 0;
	for each (gmshLine^ line in lines){
		line_ID++;
		line->ID = line_ID;
		line->write(sw);
	}

	int line_loop_ID = 0;
	for each (gmshLineLoop^ line_loop in line_loops){
		line_loop_ID++;
		line_loop->ID = line_loop_ID;
		line_loop->write(sw);
	}

	sw->Write("Plane Surface (1) = {1, ");
	for (int i=2; i<=line_loop_ID; i++) {
		sw->Write("{0}", i);
		if(i<line_loop_ID){
			sw->Write(", ");
		}
	}
	sw->WriteLine("};");

	for (int i=2; i<=line_loop_ID; i++) {
		sw->WriteLine("Plane Surface ({0}) = {{{1}}};", i, i);
	}

	sw->WriteLine("Physical Point (1) = {1};");

	for (int i=1; i<=line_loop_ID; i++) {
		sw->WriteLine("Physical Surface ({0}) = {{{1}}};", i+1, i);
	}

	sw->WriteLine("Mesh.MshFileVersion = 2;");
	sw->Close();
}
