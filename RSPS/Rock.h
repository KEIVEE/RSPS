#pragma once
#include "RSP.h"

class Paper;
class Scissors;

class Rock :public RSP {

public:
	Rock();
	Rock(const Rock&);
	bool hitby(Paper& paper);
	Vector2f nearest(vector<Scissors>&);//위치가 아닌 두 객체 간의 차이만큼.
	Vector2f nearest(vector<Paper>&);//위치가 아닌 두 객체 간의 차이만큼.
};