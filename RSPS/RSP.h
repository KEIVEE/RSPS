#pragma once

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class RSP {
protected:

	float vel_x;
	float vel_y;

	Texture texture;
	Sprite sprite;
private:

public:
	void setVelocity(float, float);
	void move(float, float);
	Sprite getSprite();
};