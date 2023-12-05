#include <iostream>
#include "Button.h"


Button::Button(Vector2f position, Text& text) {
    buttonShape.setSize(Vector2f(200, 70)); // 버튼 크기 설정
    buttonShape.setPosition(position);
    buttonShape.setFillColor(Color::Green);

    text.setCharacterSize(40);
    text.setPosition(position.x + 45, position.y + 8); // 텍스트 위치 조정
    text.setFillColor(Color::White);
}

void Button::handleEvent(Event event, RenderWindow& window, bool& hasStarted,bool&reset, Text& text) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePosition = Mouse::getPosition(window);

        if (buttonShape.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition)) && !isButtonPressed) {
            // 버튼이 클릭되었을 때 처리할 작업

            if (text.getString()=="Start"){
                buttonShape.setFillColor(Color::Red);
                text.setString("Pause");
                hasStarted = true;
            }
            else if(text.getString()=="Pause"){
                buttonShape.setFillColor(Color::Green);
                text.setString("Start");
                hasStarted = false;
            }
            else if(text.getString()=="Restart"&&hasStarted==false){  //restart일 때
                buttonShape.setFillColor(Color::Green);
                text.setString("Start");
                text.setPosition(buttonShape.getPosition().x + 45, buttonShape.getPosition().y + 8);
                

                reset = true;
                

            }

            isButtonPressed = true; // 버튼이 눌린 상태로 플래그 설정
        }
    }
    else if (event.type == Event::MouseButtonReleased) {
        isButtonPressed = false; // 버튼이 떼진 상태로 플래그 해제
    }
}

void Button::draw(RenderWindow& window) {
    window.draw(buttonShape);
}