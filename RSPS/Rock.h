#pragma once
#include "RSP.h"
#include "Paper.h"
class Rock :public RSP {

public:
	Rock();
	Rock(const Rock&);
	bool hitby(Paper& paper);
	Vector2f nearest(vector<Paper>&);//위치가 아닌 두 객체 간의 차이만큼.
};