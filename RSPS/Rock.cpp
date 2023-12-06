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
    float shortestDistance = 1800.f; //����� ũ�� ����: �밢���� �ص� 1800�� �� ���ð�
    int shortestIndex = 0;

    if (scissors.size() > 0) { //������ ���� ��: ������ �׳� ������ ��ġ�� ��ȯ
        /*
        �� �Լ��� �ڷ����� Scissors�� �ϴ� �� �� ���� �� �ִµ�,
        �׷��� �� ���ϱ� ���� ��ü�� ���� �� �� �������� �𸣰ڴ����
        */
        for (int i = 0; i < scissors.size(); i++) {
            float distance;
            
            float distanceX = scissors[i].getSprite().getPosition().x - sprite.getPosition().x;
            float distanceY = scissors[i].getSprite().getPosition().y - sprite.getPosition().y;
            
            distance = sqrt(distanceX * distanceX + distanceY * distanceY); //�Ÿ� ���ϱ�

            if (shortestDistance > distance) {
                shortestDistance = distance;//�ּ� �Ÿ� ���ϱ�
                shortestIndex = i;//�ּ� �Ÿ��� ������ �ε���
            }
        }
    }
    else return sprite.getPosition();

    return Vector2f(scissors[shortestIndex].getSprite().getPosition().x-sprite.getPosition().x, scissors[shortestIndex].getSprite().getPosition().y - sprite.getPosition().y);
    //�ּ� �Ÿ� �ε����� �ִ� ������ �� ���� ��ü���� ��ġ ���̸� ����.
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