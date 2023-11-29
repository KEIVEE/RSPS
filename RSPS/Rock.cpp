#include "Rock.h"
#include <exception>
#include <random>

Rock::Rock() {
	if(!texture.loadFromFile("Rock.png")) throw exception("image error");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> disX(0.0f, 1480.0f); // x ��ǥ ���� (0���� 800����)
    uniform_real_distribution<float> disY(0.0f, 880.0f); // y ��ǥ ���� (0���� 600����)

    float randomX = disX(gen);
    float randomY = disY(gen);

    sprite.setTexture(texture);
    sprite.setPosition(Vector2f(randomX, randomY));
}

