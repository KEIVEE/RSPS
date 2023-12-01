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
	void moveRandom();
	void move(Vector2f&);
	Sprite getSprite();
	void draw(RenderWindow& window);
	//virtual bool hitby(RSP& other); 다른 객체와 만났을 때 어떻게 할 것인가.
};