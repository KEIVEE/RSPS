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
	void move(Vector2f&, RenderWindow& window); //����: x�ӵ� y�ӵ�. ����ŭ �����̱�
	Vector2f const getVelocity();
	Sprite getSprite();
	void draw(RenderWindow& window);
	virtual bool hitby(RSP& other);
	//virtual nearest ����. �ʿ䰡 ����
};