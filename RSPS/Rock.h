#pragma once
#include "RSP.h"
class Rock :RSP {
	Texture texture;
	Sprite sprite;

public:
	Rock();
	Sprite getSprite();
	void move(float, float);
};