#include "Scissors.h"
#include "Rock.h"
#include <exception>
#include <random>




Scissors::Scissors() {
    if (!texture.loadFromFile("scissors.png")) throw exception("image error");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> disX(0.0f, 1480.0f); // x 좌표 범위 (0에서 800까지)
    uniform_real_distribution<float> disY(0.0f, 880.0f); // y 좌표 범위 (0에서 600까지)

    float randomX = disX(gen);
    float randomY = disY(gen);

    sprite.setTexture(texture);
    sprite.setPosition(Vector2f(randomX, randomY));
}

Scissors::Scissors(const Scissors& original, Texture& texturePtr) {
    texture = original.texture;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> disX(0.0f, 1480.0f); // x 좌표 범위 (0에서 800까지)
    uniform_real_distribution<float> disY(0.0f, 880.0f); // y 좌표 범위 (0에서 600까지)

    float randomX = disX(gen);
    float randomY = disY(gen);

    sprite.setTexture(texturePtr);
    sprite.setPosition(Vector2f(randomX, randomY));
}

Scissors::Scissors(Vector2f& pos, Texture& texturePtr) {

    sprite.setTexture(texturePtr);
    sprite.setPosition(pos);
}

bool Scissors::hitby(Rock& rock) {
    if (this->getSprite().getGlobalBounds().intersects(rock.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}