#include "Slider.h"
#include <iostream>

Slider::Slider(Vector2f& position) { //��ġ�� �������ָ� �����̴� ����
    sliderBar.setSize(Vector2f(300.f, 15.f)); //������ �ִ� �κ�
    floatingBar.setSize(Vector2f(30.f, 30.f)); //�巡���ؼ� ������ �κ�
    sliderBar.setPosition(position);
    floatingBar.setPosition(Vector2f(position.x, position.y - 7.5f)); //�� ���簢�� ���Ʒ� ����
    sliderBar.setFillColor(Color::White);
    floatingBar.setFillColor(Color::Blue);

    isDragging = false; //�巡������ �ʰ� �ִٰ� �����ϰ�,
    offsetX = 0; //offset�� 0���� �α�: floatingbar�� sliderbar�� x��ġ�� �����ϱ�.
}


void Slider::handleEvent(Event event, RenderWindow& window) { //�̺�Ʈ �ڵ鸵
    if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {//���콺 ���� ��ư�� ������:
            if (floatingBar.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {//�װ� �Ķ��� �κ��̴�:
                isDragging = true;//�巡�׸� true�� ����


            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == Mouse::Left) {
            isDragging = false;

        }

    }
    else if (event.type == Event::MouseMoved) {//���콺�� ��������:
        if (isDragging) {//�巡���ϴ� ���ȿ���
            float x = event.mouseMove.x; //������ ���콺�� x��ġ
            if (x >= sliderBar.getPosition().x && x <= sliderBar.getPosition().x + sliderBar.getSize().x - floatingBar.getSize().x) {
                //������ ���콺�� ��ġ�� �Ͼ� �����̴����� ���� ������ ������ ��-�÷��ù��� ũ���: ���� ���ؼ�
                //�Ķ� �÷��ùٰ� �Ͼ� �����̴��ٸ� �Ѿ�� �ʴ� �ѿ���
                floatingBar.setPosition(x, floatingBar.getPosition().y);
                //�÷��ù��� ��ġ�� ���콺 ��ġ�� ����.
            }
            offsetX = (((int)floatingBar.getPosition().x - (int)sliderBar.getPosition().x) / 3);
            //�������� (�÷��ù� ��ġ - �����̴��� ��ġ) / 3
        }
    }
}

void Slider::draw(RenderWindow& window) {
    window.draw(sliderBar);
    window.draw(floatingBar);
}

int Slider::getOffset() {
    return offsetX;
}

void Slider::resetSlider() {
    floatingBar.setPosition(sliderBar.getPosition().x, sliderBar.getPosition().y - 7.5f);
    isDragging = false;
    offsetX = 0;
}