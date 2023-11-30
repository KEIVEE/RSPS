#include "Scissors.h"
#include <exception>
#include <random>

Scissors::Scissors(const Scissors& original, float x, float y) {
    texture = original.texture;
    sprite.setTexture(texture);
    sprite.setPosition(Vector2f(x, y));
}

Scissors::Scissors() {
    if (!texture.loadFromFile("scissors.png")) throw exception("image error");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> disX(0.0f, 1480.0f); // x ��ǥ ���� (0���� 800����)
    uniform_real_distribution<float> disY(0.0f, 880.0f); // y ��ǥ ���� (0���� 600����)

    float randomX = disX(gen);
    float randomY = disY(gen);

    sprite.setTexture(texture);
    sprite.setPosition(Vector2f(randomX, randomY));
}

Scissors::Scissors(const Scissors& original) {
    texture = original.texture;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> disX(0.0f, 1480.0f); // x ��ǥ ���� (0���� 800����)
    uniform_real_distribution<float> disY(0.0f, 880.0f); // y ��ǥ ���� (0���� 600����)

    float randomX = disX(gen);
    float randomY = disY(gen);

    sprite.setTexture(texture);
    sprite.setPosition(Vector2f(randomX, randomY));
}