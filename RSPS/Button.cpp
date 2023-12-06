#include <iostream>
#include "Button.h"


Button::Button(Vector2f position, Text& text) {
    buttonShape.setSize(Vector2f(200, 70)); // ��ư ũ�� ����
    buttonShape.setPosition(position);
    buttonShape.setFillColor(Color::Green);

    text.setCharacterSize(40);
    text.setPosition(position.x + 45, position.y + 8); // �ؽ�Ʈ ��ġ ����
    text.setFillColor(Color::White);
}

void Button::handleEvent(Event event, RenderWindow& window, bool& hasStarted,bool&reset, Text& text) {
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePosition = Mouse::getPosition(window);

        if (buttonShape.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition)) && !isButtonPressed) {
            // ��ư�� Ŭ���Ǿ��� �� ó���� �۾�

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
            else if(text.getString()=="Restart"&&hasStarted==false){  //restart�� ��
                buttonShape.setFillColor(Color::Green);
                text.setString("Start");
                text.setPosition(buttonShape.getPosition().x + 45, buttonShape.getPosition().y + 8);
                

                reset = true;
                

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
}