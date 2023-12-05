#include "Rock.h"
#include "Paper.h"
#include <exception>
#include <random>



Rock::Rock() { //수정 예정: 텍스트와 sprite만 설정하도록.
    if (!texture.loadFromFile("rock.png")) throw exception("image error");


    sprite.setTexture(texture);
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
    return false;
}