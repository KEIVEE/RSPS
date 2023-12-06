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
	void setPosition(Vector2f& position);
	//virtual Vector2f nearest(vector <RSP>&); //��ü �ϳ�(������� ����)�� �������� ���� ����� �ٸ� ����(�ָ�)�� ã�Ƽ� �� �ָ��� ��ġ�� ��ȯ.
};