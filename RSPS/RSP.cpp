#include "RSP.h"
#include <random>

Sprite RSP::getSprite() {
    return sprite;
}

void RSP::move(Vector2f& v, RenderWindow& window) {
    //��ü�� �����̴� ��Ŀ����
    if (sprite.getPosition().x <= window.getSize().x - sprite.getGlobalBounds().width && 
        sprite.getPosition().y <= window.getSize().y - sprite.getGlobalBounds().height &&
        sprite.getPosition().x >= 0 && sprite.getPosition().y >= 0) {
        //��ü�� ������ â�� ����� �ʴ� �Ͽ�
            sprite.move(v);
            //v�������� ����������
    }

    //�� ������ 1�ȼ��� ��´ٸ�: ���⼭ �߿��� ���� else�� ���� �ʴ´ٴ� ��. else�� ������� �� �Ʒ� if���� ����� ������� �ʴ´�.
    if ((sprite.getPosition().x >= window.getSize().x - sprite.getGlobalBounds().width-1 || sprite.getPosition().x <= 1) &&
        (sprite.getPosition().y <= window.getSize().y - sprite.getGlobalBounds().height-1 && sprite.getPosition().y >= 1)) {
        //���� Ȥ�� ������ �𼭸��� ��´ٸ�: �׷��鼭 y�� �������� ��ġ�� �ִٸ�
        //�������� ��ġ�� ���� ������ �ȿ� ���� ���� ���ϴ� ��: �� ���������� ���ϸ� y��ǥ 1���� 879����.
        sprite.move(-v.x, v.y);
        //�ݴ������� ƨ�ܳ� �ֱ�.
    }

    if ((sprite.getPosition().y >= window.getSize().y - sprite.getGlobalBounds().height-1 || sprite.getPosition().y <= 1) &&
        (sprite.getPosition().x <= window.getSize().x - sprite.getGlobalBounds().width-1 && sprite.getPosition().x >= 1)) {
        //�� Ȥ�� �Ʒ� �𼭸��� ��´ٸ�: �׷��鼭 x�� �������� ��ġ�� �ִٸ�
        sprite.move(v.x, -v.y);
        //�ݴ������� ƨ�ܳ� �ֱ�.
    }

    if ((sprite.getPosition().y >= window.getSize().y - sprite.getGlobalBounds().height - 1 || sprite.getPosition().y <= 1) &&
        (sprite.getPosition().x >= window.getSize().x - sprite.getGlobalBounds().width - 1 || sprite.getPosition().x <= 1)) {
        //���� �������� ����:
        sprite.move(-v.x, -v.y);
        //���� ���� �� ������ ƨ�ܳ� �ֱ�.
    }
    /*
    �� ó�� if�� ������ ���� �ȿ��� �����̰� �ϴµ�, �̰͸� �дٸ� �𼭸��� ����� �� �ٽ� �������� ������ ���ϴ� ������ �߻�
    �׷��� �� ���� 1�������� ���ְ� ������ �����̴� ���� �� 1�������� �����ϰ� �� ���ʿ����� �����̵��� �ϸ�
    �𼭸��� ��Ҵ�(���� ������ ������ ���� ��ó�� ���̴�) ��ü�� �� ���ƿͼ� �Ѱ� ���ϰ� �� �� �ִ�.
    */

}

void RSP::draw(RenderWindow& window) {
    window.draw(sprite);
} 


bool RSP::hitby(RSP& other) { //����� ���� ������ ��ǥ�� �� �� ����� �� ���� ���� ���߾� �Լ�.
    return false;
}


void RSP::setPosition(Vector2f& position) {
    sprite.setPosition(position);
}