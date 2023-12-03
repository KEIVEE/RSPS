#include <iostream>
#include "Button.h"


Button::Button(Vector2f position, Font& font) {
    buttonShape.setSize(Vector2f(200, 70)); // ��ư ũ�� ����
    buttonShape.setPosition(position);
    buttonShape.setFillColor(Color::Green);


    buttonText.setString("Start");
    buttonText.setFont(font);
    buttonText.setCharacterSize(40);
    buttonText.setPosition(position.x + 45, position.y + 8); // �ؽ�Ʈ ��ġ ����
    buttonText.setFillColor(Color::White);
}

void Button::handleEvent(Event event, RenderWindow& window, bool& hasStarted) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePosition = Mouse::getPosition(window);

        if (buttonShape.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition)) && !isButtonPressed) {
            // ��ư�� Ŭ���Ǿ��� �� ó���� �۾�

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

            isButtonPressed = true; // ��ư�� ���� ���·� �÷��� ����
        }
    }
    else if (event.type == Event::MouseButtonReleased) {
        isButtonPressed = false; // ��ư�� ���� ���·� �÷��� ����
    }
}

void Button::draw(RenderWindow& window) {
    window.draw(buttonShape);
    window.draw(buttonText);
}