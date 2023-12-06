#include "Paper.h"
#include "Rock.h"
#include "Scissors.h"
#include <exception>
#include <random>
/*
Rock, Scissors, Paper�� �� ����ϱ� ������ Rock�� ��ǥ�� �ּ� �ۼ��ϰڽ��ϴ�. Rock.cpp����.
*/
Paper::Paper() {
    if (!texture.loadFromFile("paper.png")) throw exception("image error");
    sprite.setTexture(texture);
}

Paper::Paper(const Paper& original, Texture& texturePtr) {
    texture = original.texture;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> disX(0.0f, 1480.0f);
    uniform_real_distribution<float> disY(0.0f, 880.0f);

    float randomX = disX(gen);
    float randomY = disY(gen);

    sprite.setTexture(texturePtr);
    sprite.setPosition(Vector2f(randomX, randomY));
}


Vector2f Paper::nearest(vector<Rock>& rocks) { //rock.cpp�� �ִ� �ּ� ����
    float shortestDistance = 1800.f;
    int shortestIndex = 0;

    if (rocks.size() > 0) {
        for (int i = 0; i < rocks.size(); i++) {
            float distance;

            float distanceX = rocks[i].getSprite().getPosition().x - sprite.getPosition().x;
            float distanceY = rocks[i].getSprite().getPosition().y - sprite.getPosition().y;

            distance = sqrt(distanceX * distanceX + distanceY * distanceY);

            if (shortestDistance > distance) {
                shortestDistance = distance;
                shortestIndex = i;
            }
        }
    }
    else return Vector2f(0, 0);;

    return Vector2f(rocks[shortestIndex].getSprite().getPosition().x - sprite.getPosition().x, rocks[shortestIndex].getSprite().getPosition().y - sprite.getPosition().y);

}

Vector2f Paper::nearest(vector<Scissors>& Scissorss) {
    float shortestDistance = 1800.f;
    int shortestIndex = 0;

    if (Scissorss.size() > 0) {
        for (int i = 0; i < Scissorss.size(); i++) {
            float distance;

            float distanceX = Scissorss[i].getSprite().getPosition().x - sprite.getPosition().x;
            float distanceY = Scissorss[i].getSprite().getPosition().y - sprite.getPosition().y;

            distance = sqrt(distanceX * distanceX + distanceY * distanceY);

            if (shortestDistance > distance) {
                shortestDistance = distance;
                shortestIndex = i;
            }
        }
    }
    else return Vector2f(0, 0);

    return Vector2f(Scissorss[shortestIndex].getSprite().getPosition().x - sprite.getPosition().x, Scissorss[shortestIndex].getSprite().getPosition().y - sprite.getPosition().y);
}


bool Paper::hitby(Scissors& scissors) {
    if (this->getSprite().getGlobalBounds().intersects(scissors.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
}

Paper::Paper(Vector2f& pos, Texture& texturePtr) {
    sprite.setTexture(texturePtr);
    sprite.setPosition(pos);
}