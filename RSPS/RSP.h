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
	void move(Vector2f&); //인자: x속도 y속도. 저만큼 움직이기
	Sprite getSprite();
	void draw(RenderWindow& window);
	virtual bool hitby(RSP& other);
	void setPosition(Vector2f& position);
	//virtual Vector2f nearest(vector <RSP>&); //객체 하나(가위라고 가정)를 기준으로 가장 가까운 다른 종류(주먹)을 찾아서 그 주먹의 위치를 반환.
};