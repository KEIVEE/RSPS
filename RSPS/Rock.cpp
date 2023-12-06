#include "Rock.h"
#include "Paper.h"
#include "Scissors.h"
#include <exception>
#include <random>
#include <cmath>



Rock::Rock() {
    if (!texture.loadFromFile("rock.png")) throw exception("image error");


    sprite.setTexture(texture);
}

Rock::Rock(const Rock& original, Texture& texturePtr) {
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


Rock::Rock(Vector2f& pos, Texture& texturePtr) {
    
    sprite.setTexture(texturePtr);
    sprite.setPosition(pos);
}

bool Rock::hitby(Paper& paper) {
    if (this->getSprite().getGlobalBounds().intersects(paper.getSprite().getGlobalBounds())) {
        return true;
    }
    return false;
    return false;
}

Vector2f Rock::nearest(vector<Scissors>& scissors) {
    float shortestDistance = 1800.f; //충분히 크게 세팅: 대각선을 해도 1800은 안 나올걸
    int shortestIndex = 0;

    if (scissors.size() > 0) { //가위가 있을 때: 없으면 그냥 본인의 위치를 반환
        /*
        이 함수의 자료형을 Scissors로 하는 게 더 편할 수 있는데,
        그렇게 해 보니까 가위 객체가 없을 때 뭘 리턴할지 모르겠더라고
        */
        for (int i = 0; i < scissors.size(); i++) {
            float distance;
            
            float distanceX = scissors[i].getSprite().getPosition().x - sprite.getPosition().x;
            float distanceY = scissors[i].getSprite().getPosition().y - sprite.getPosition().y;
            
            distance = sqrt(distanceX * distanceX + distanceY * distanceY); //거리 구하기

            if (shortestDistance > distance) {
                shortestDistance = distance;//최소 거리 구하기
                shortestIndex = i;//최소 거리인 가위의 인덱스
            }
        }
    }
    else return sprite.getPosition();

    return Vector2f(scissors[shortestIndex].getSprite().getPosition().x-sprite.getPosition().x, scissors[shortestIndex].getSprite().getPosition().y - sprite.getPosition().y);
    //최소 거리 인덱스에 있는 가위와 이 바위 객체와의 위치 차이를 리턴.
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

    return Vector2f(papers[shortestIndex].getSprite().getPosition().x - sprite.getPosition().x, papers[shortestIndex].getSprite().getPosition().y - sprite.getPosition().y);

}