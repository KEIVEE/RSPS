#include "Slider.h"
#include <iostream>

Slider::Slider(Vector2f& position) { //위치를 결정해주면 슬라이더 생성
    sliderBar.setSize(Vector2f(300.f, 15.f)); //가만히 있는 부분
    floatingBar.setSize(Vector2f(30.f, 30.f)); //드래그해서 움직일 부분
    sliderBar.setPosition(position);
    floatingBar.setPosition(Vector2f(position.x, position.y - 7.5f)); //두 직사각형 위아래 조정
    sliderBar.setFillColor(Color::White);
    floatingBar.setFillColor(Color::Blue);

    isDragging = false; //드래그하지 않고 있다고 가정하고,
    offsetX = 0; //offset은 0으로 두기: floatingbar와 sliderbar의 x위치가 같으니까.
}


void Slider::handleEvent(Event event, RenderWindow& window) { //이벤트 핸들링
    if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {//마우스 왼쪽 버튼을 눌렀다:
            if (floatingBar.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {//그게 파란색 부분이다:
                isDragging = true;//드래그를 true로 설정


            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == Mouse::Left) {
            isDragging = false;

        }

    }
    else if (event.type == Event::MouseMoved) {//마우스를 움직였다:
        if (isDragging) {//드래그하는 동안에만
            float x = event.mouseMove.x; //움직인 마우스의 x위치
            if (x >= sliderBar.getPosition().x && x <= sliderBar.getPosition().x + sliderBar.getSize().x - floatingBar.getSize().x) {
                //움직인 마우스의 위치가 하얀 슬라이더바의 왼쪽 끝부터 오른쪽 끝-플로팅바의 크기다: 쉽게 말해서
                //파란 플로팅바가 하얀 슬라이더바를 넘어가지 않는 한에서
                floatingBar.setPosition(x, floatingBar.getPosition().y);
                //플로팅바의 위치를 마우스 위치로 설정.
            }
            offsetX = (((int)floatingBar.getPosition().x - (int)sliderBar.getPosition().x) / 3);
            //오프셋은 (플로팅바 위치 - 슬라이더바 위치) / 3
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