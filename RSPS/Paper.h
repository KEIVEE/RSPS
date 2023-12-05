#pragma once
#include "RSP.h"
class Rock;
class Scissors;
class Paper :public RSP {

public:
	Paper();
	Paper(const Paper&, Texture& texturePtr);
	Paper(Vector2f& pos, Texture& texturePtr);
	bool hitby(Scissors& scissors);
};