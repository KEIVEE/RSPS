#include "Rock.h"
#include <exception>

Rock::Rock() {
	if(!texture.loadFromFile("Rock.png")) throw exception("image error");

	vel_x = 0.0f;
	vel_y = 0.0f;

	sprite.setTexture(texture);
	sprite.setPosition(30.f, 30.f);
}

