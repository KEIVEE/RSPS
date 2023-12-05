#pragma once
#include "RSP.h"
class Rock;
class Paper;
class Scissors :public RSP {

public:
	
	Scissors();
	Scissors(const Scissors&, Texture& texturePtr);
	Scissors(Vector2f& pos, Texture& texturePtr);
	bool hitby(Rock& rock);
};