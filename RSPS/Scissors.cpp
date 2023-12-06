#include "Scissors.h"
#include "Rock.h"
#include "Paper.h"
#include <exception>
#include <random>
/*
Rock, Scissors, Paper는 다 비슷하기 때문에 Rock만 대표로 주석 작성하겠습니다. Rock.cpp참고.
*/
Scissors::Scissors() {
    if (!texture.loadFromFile("scissors.png")) throw exception("image error");
    sprite.setTexture(texture);
}




Scissors::Scissors(const Scissors& original, Texture& texturePtr) {
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

Vector2f Scissors::nearest(vector<Rock>& rocks) {
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
    else return Vector2f(0, 0);

    return Vector2f(rocks[shortestIndex].getSprite().getPosition().x - sprite.getPosition().x, rocks[shortestIndex].getSprite().getPosition().y - sprite.getPosition().y);

}


Vector2f Scissors::nearest(vector<Paper>& papers) {
    float shortestDistance = 1800.f;
    int shortestIndex = 0;

    if (papers.size() > 0) {
        for (int i = 0; i < papers.size(); i++) {
            float distance;

            float distanceX = papers[i].getSprite().getPosition().x - sprite.getPosition().x;
            float distanceY = papers[i].getSprite().getPosition().y - sprite.getPosition().y;

            distance = sqrt(distanceX * distanceX + distanceY * distanceY);


            if (shortestDistance > distance) {
                shortestDistance = distance;
                shortestIndex = i;
            }
        }
    }
    else return Vector2f(0, 0);

    return Vector2f(papers[shortestIndex].getSprite().getPosition().x - sprite.getPosition().x, papers[shortestIndex].getSprite().getPosition().y - sprite.getPosition().y);

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