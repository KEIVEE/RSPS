#include "RSP.h"
#include <random>

Sprite RSP::getSprite() {
    return sprite;
}

void RSP::move(Vector2f& v, RenderWindow& window) {
    if (sprite.getPosition().x < window.getSize().x - sprite.getGlobalBounds().width && 
        sprite.getPosition().y < window.getSize().y - sprite.getGlobalBounds().height &&
        sprite.getPosition().x > 0 && sprite.getPosition().y > 0) {
        sprite.move(v);
        velocity = v;

    }//hitby완성시 수정 필요할듯.
    else if (sprite.getPosition().x == window.getSize().x - sprite.getGlobalBounds().width || sprite.getPosition().x == 0) {
        sprite.move(0, v.y);
        velocity = Vector2f(0, v.y);
    }
    else if (sprite.getPosition().y == window.getSize().y - sprite.getGlobalBounds().height || sprite.getPosition().y == 0) {
        sprite.move(v.x, 0);
        velocity = Vector2f(v.x, 0);
    }
    else {
        sprite.move(0, 0);
        velocity = Vector2f(0, 0);
    }
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

Vector2f const RSP::getVelocity() {
    return velocity;
}