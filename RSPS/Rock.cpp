#include "Rock.h"
#include "Paper.h"
#include <exception>
#include <random>



Rock::Rock() { //���� ����: �ؽ�Ʈ�� sprite�� �����ϵ���.
    if (!texture.loadFromFile("rock.png")) throw exception("image error");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> disX(0.0f, 1480.0f); // x ��ǥ ���� (0���� 800����)
    uniform_real_distribution<float> disY(0.0f, 880.0f); // y ��ǥ ���� (0���� 600����)

    float randomX = disX(gen);
    float randomY = disY(gen);

    sprite.setTexture(texture);
    sprite.setPosition(Vector2f(randomX, randomY));
}

Rock::Rock(const Rock& original) {
    texture = original.texture;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> disX(0.0f, 1480.0f);
    uniform_real_distribution<float> disY(0.0f, 880.0f);

    float randomX = disX(gen);
    float randomY = disY(gen);

    sprite.setTexture(texture);
    sprite.setPosition(Vector2f(randomX, randomY));
}

bool Rock::hitby(Paper& paper) {
    if (this->getSprite().getGlobalBounds().intersects(paper.getSprite().getGlobalBounds())) {
        return true;
    }
}