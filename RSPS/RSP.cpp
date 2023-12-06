#include "RSP.h"
#include <random>

Sprite RSP::getSprite() {
    return sprite;
}

void RSP::move(Vector2f& v, RenderWindow& window) {
    if (sprite.getPosition().x <= window.getSize().x - sprite.getGlobalBounds().width && 
        sprite.getPosition().y <= window.getSize().y - sprite.getGlobalBounds().height &&
        sprite.getPosition().x >= 0 && sprite.getPosition().y >= 0) {


        
            sprite.move(v);
            velocity = v;

        


    }//hitby�ϼ��� ���� �ʿ��ҵ�.
    
    if ((sprite.getPosition().x >= window.getSize().x - sprite.getGlobalBounds().width-1 || sprite.getPosition().x <= 1) &&
        (sprite.getPosition().y <= window.getSize().y - sprite.getGlobalBounds().height-1 && sprite.getPosition().y >= 1)) {
        sprite.move(-v.x, v.y);
    }

    if ((sprite.getPosition().y >= window.getSize().y - sprite.getGlobalBounds().height-1 || sprite.getPosition().y <= 1) &&
        (sprite.getPosition().x <= window.getSize().x - sprite.getGlobalBounds().width-1 && sprite.getPosition().x >= 1)) {
        sprite.move(v.x, -v.y);
    }

}

void RSP::draw(RenderWindow& window) {
    window.draw(sprite);
} 


void RSP::moveRandom() {
    // ������ ���� ����
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
    sf::Vector2f direction(dis(gen), dis(gen));


    float moveSpeed = 0.5f;

    // ����� �ӵ��� ���Ͽ� �̵�
    sprite.move(direction * moveSpeed);

}

bool RSP::hitby(RSP& other) {
    return false;
}

Vector2f const RSP::getVelocity() {
    return velocity;
}


void RSP::setPosition(Vector2f& position) {
    sprite.setPosition(position);
}