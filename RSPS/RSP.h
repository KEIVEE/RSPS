#pragma once

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class RSP {
protected:

	Vector2f velocity;

	Texture texture;
	Sprite sprite;
private:

public:
	void move(Vector2f);
	Sprite getSprite();
	void draw(RenderWindow& window);
};