#include "Paper.h"
#include "Scissors.h"
#include <exception>
#include <random>



Paper::Paper() {
    if (!texture.loadFromFile("paper.png")) throw exception("image error");
    sprite.setTexture(texture);
}

Paper::Paper(const Paper& original, Texture& texturePtr) {
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

Paper::Paper(Vector2f& pos, Texture& texturePtr) {
    
    sprite.setTexture(texturePtr);
    sprite.setPosition(pos);
}

bool Paper::hitby(Scissors& scissors) {
    if (this->getSprite().getGlobalBounds().intersects(scissors.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}