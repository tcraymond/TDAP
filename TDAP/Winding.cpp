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