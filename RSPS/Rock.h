#pragma once
#include "RSP.h"
class Paper;
class Scissors;

class Rock :public RSP {
	
public:
	
	Rock();
	Rock(const Rock&, Texture& texturePtr);
	Rock(Vector2f& pos, Texture& texturePtr);
	bool hitby(Paper& paper);
};