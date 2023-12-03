#include <iostream>
#include "Button.h"


Button::Button(Vector2f position, Font& font) {
    buttonShape.setSize(Vector2f(200, 70)); // 버튼 크기 설정
    buttonShape.setPosition(position);
    buttonShape.setFillColor(Color::Green);


    buttonText.setString("Start");
    buttonText.setFont(font);
    buttonText.setCharacterSize(40);
    buttonText.setPosition(position.x + 45, position.y + 8); // 텍스트 위치 조정
    buttonText.setFillColor(Color::White);
}

void Button::handleEvent(Event event, RenderWindow& window, bool& hasStarted) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePosition = Mouse::getPosition(window);

        if (buttonShape.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition)) && !isButtonPressed) {
            // 버튼이 클릭되었을 때 처리할 작업

            if (hasStarted == false) {
                buttonShape.setFillColor(Color::Red);
                buttonText.setString("Pause");
                Vector2f position = buttonShape.getPosition();
                hasStarted = true;
            }
            else {
                buttonShape.setFillColor(Color::Green);
                buttonText.setString("Start");
                Vector2f position = buttonShape.getPosition();
                hasStarted = false;
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
    window.draw(buttonText);
}