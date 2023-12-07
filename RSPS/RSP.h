#pragma once

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class RSP {
protected:

	Texture texture;
	Sprite sprite;
private:

public:
	void move(Vector2f&, RenderWindow& window); //인자: x속도 y속도. 저만큼 움직이기
	Sprite getSprite();
	void draw(RenderWindow& window);
	virtual bool hitby(RSP& other);
	void setPosition(Vector2f& position);
};