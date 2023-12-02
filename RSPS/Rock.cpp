#include "Rock.h"
#include "Paper.h"
#include "Scissors.h"
#include <exception>
#include <random>
#include <cmath>



Rock::Rock() { //수정 예정: 텍스트와 sprite만 설정하도록.
    if (!texture.loadFromFile("rock.png")) throw exception("image error");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> disX(0.0f, 1480.0f); // x 좌표 범위 (0에서 800까지)
    uniform_real_distribution<float> disY(0.0f, 880.0f); // y 좌표 범위 (0에서 600까지)

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
    return false;
}

Vector2f Rock::nearest(vector<Paper>& papers) {
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
    else return sprite.getPosition();

    return Vector2f(papers[shortestIndex].getSprite().getPosition().x-sprite.getPosition().x, papers[shortestIndex].getSprite().getPosition().y - sprite.getPosition().y);

}