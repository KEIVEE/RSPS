#pragma once
#include "RSP.h"
#include "Paper.h"
class Rock :public RSP {

public:
	Rock();
	Rock(const Rock&);
	bool hitby(Paper& paper);
};