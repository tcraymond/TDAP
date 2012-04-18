#pragma once

using namespace System;

namespace TDAP {

ref class Turn
{
public:
	double lower_left_r;
	double lower_left_y;
	double upper_right_r;
	double upper_right_y;

	Turn(void);
};

}
