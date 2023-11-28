#include "RSP.h"


void RSP::setVelocity(float x, float y) {
	vel_x = x;
	vel_y = y;
}

Sprite RSP::getSprite() {
	return sprite;
}

void RSP::move(float x, float y) {
	sprite.move(x, y);
	vel_x = x;
	vel_y = y;
}