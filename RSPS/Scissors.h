#pragma once
#include "RSP.h"
class Rock;
class Paper;

class Scissors :public RSP {

public:
	
	Scissors();
	Scissors(const Scissors&, Texture&);
	Scissors(Vector2f&, Texture&);
	Vector2f nearest(vector<Rock>&);
	Vector2f nearest(vector<Paper>&);
	bool hitby(Rock&);
};