#pragma once

#include "gmshLine.h"

using namespace System;
using namespace System::Collections::Generic;

ref class gmshLineLoop
{
public:
	gmshLineLoop(void);
	gmshLineLoop(List<gmshLine^>^);
	void write(StreamWriter^ sw);
	int ID;
	List<gmshLine^>^ lines;
};

