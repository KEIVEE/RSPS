#include "RSP.h"


Sprite RSP::getSprite() {
	return sprite;
}

void RSP::move(Vector2f v) {
	sprite.move(v);
	velocity = v;
}

void RSP::draw(RenderWindow& window) {
	window.draw(sprite);
}