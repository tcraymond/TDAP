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
#include "Winding.h"
#include "Transformer.h"
#include <math.h>

Winding::Winding(void)
{
	sections = gcnew List<Section^>();

}

Section^ Winding::addSection(){
	Section^ newSection = gcnew Section;
	newSection->winding = this;
	sections->Add(newSection);
	return newSection;
}

void Winding::writeSectionsGmsh(gmshFile^ outFile){
	for each (Section^ section in sections){
		section->writeSectionGmsh(outFile);
	}
}

double Winding::totalArea(){
	double area = 0;
	for each (Section^ section in sections){
		area = area + section->Area();
	}
	return area;
}

int Winding::totalTurns(){
	int turns = 0;
	for each (Section^ section in sections){
		turns = turns + section->Turns();
	}
	return turns;
}

double Winding::Current(){
	double I;
	if (transformer->numPhases == 1) { //Single phase
		I = MVA / (voltage / sqrt(3.)) * 1000 * currDir;
	} else if (transformer->numPhases == 3) { //Three phase
		I = MVA / 3 / (voltage / sqrt(3.)) * 1000 * currDir;
	} else {
		//error
	}
	return I;
}