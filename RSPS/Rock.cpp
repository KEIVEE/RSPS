#include "Rock.h"
#include <exception>

Rock::Rock() {
	if(!texture.loadFromFile("Rock.png")) throw exception("image error");

	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(30.f, 30.f));
}

