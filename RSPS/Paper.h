#pragma once
#include "RSP.h"
class Paper :public RSP {

public:
	Paper();
	Paper(const Paper&);
	Paper(Vector2f& pos);
};