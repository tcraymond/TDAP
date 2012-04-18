#include "StdAfx.h"
#include "gmshLineLoop.h"

gmshLineLoop::gmshLineLoop(void)
{
	lines = nullptr;
}

gmshLineLoop::gmshLineLoop(List<gmshLine^>^ in_lines){
	lines = in_lines;
}

void gmshLineLoop::write(StreamWriter^ sw){
	//fprintf(stream, "Line Loop (%d) = {%d, %d, %d, %d};", next_section, next_line, next_line + 1, next_line + 2, next_line + 3);
	sw->Write("Line Loop ({0}) = {{", ID);
	bool firstLine = true;
	for each (gmshLine^ line in lines) {
		if(!firstLine){
			sw->Write(", ");
		}else{
			firstLine = false;
		}
		sw->Write("{0}", line->ID);
	}
	sw->WriteLine("};");
}