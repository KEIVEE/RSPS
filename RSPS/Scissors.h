#pragma once
#include "RSP.h"
class Scissors :public RSP {

public:
	Scissors(const Scissors& original, float x, float y);
	Scissors();
	Scissors(const Scissors&);

};