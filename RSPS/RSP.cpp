#include "RSP.h"
#include <random>

Sprite RSP::getSprite() {
    return sprite;
}

void RSP::move(Vector2f& v) {
    sprite.move(v);
    velocity = v;
}

void RSP::draw(RenderWindow& window) {
    window.draw(sprite);
}

void RSP::moveRandom() {
    // 랜덤한 방향 설정
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
    sf::Vector2f direction(dis(gen), dis(gen));


    float moveSpeed = 0.5f;

    // 방향과 속도를 곱하여 이동
    sprite.move(direction * moveSpeed);

}

bool RSP::hitby(RSP& other) {
    return false;
}


void RSP::setPosition(Vector2f& position) {
    sprite.setPosition(position);
}