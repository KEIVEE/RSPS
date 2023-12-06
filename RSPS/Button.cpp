#include <iostream>
#include "Button.h"


Button::Button(Vector2f position, Text& text) {
    isButtonPressed = false;
    buttonShape.setSize(Vector2f(200, 70)); // ��ư ũ�� ����
    buttonShape.setPosition(position);
    //������ ������ ������ ȭ�� ����� �ٸ� ��ư�� ���� �������� ��ư �����ڿ� position�� �����޶� �߾��µ�
    //�̰͵� ������ ������
    buttonShape.setFillColor(Color::Green);

    text.setCharacterSize(40);
    text.setPosition(position.x + 45, position.y + 8); // �ؽ�Ʈ ��ġ ����
    text.setFillColor(Color::White);
}

void Button::handleEvent(Event event, RenderWindow& window, bool& hasStarted, bool& reset, bool& resume, Text& text) {
    //���� �������� ���ڿ��� �ϳ� �� �߰�: pause�� �����ϱ� ����
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePosition = Mouse::getPosition(window);

        if (buttonShape.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition)) && !isButtonPressed) {
            // ��ư�� Ŭ���Ǿ��� �� ó���� �۾�

            if (text.getString()=="Start"){ //start�� �ΰ��� ��찡 �ִ�. ���� ������ ���� start, ���� ��� ������ ���� start
                if (hasStarted == false) { //���� ���ڴ�: ���� ������ ���� start
                    buttonShape.setFillColor(Color::Red);
                    text.setString("Pause");
                    hasStarted = true; //���� ����
                    resume = true; //���� ����
                }
                else {
                    buttonShape.setFillColor(Color::Red);//���� ���ڴ�: ���� �簳�� ���� start
                    text.setString("Pause"); 
                    resume = true; //���� ���ุ.
                }
            }
            else if(text.getString()=="Pause" && hasStarted == true){ //pause�� ���� �Ͻ������� ������ �Ѵ�
                buttonShape.setFillColor(Color::Green);
                text.setString("Start");
                resume = false;//�� �۾��� �����ν� ��ü �����Ӹ� ���� �� �ְ� ��.
            }
            else if(text.getString()=="Restart" && hasStarted == true){  //restart�� ��
                buttonShape.setFillColor(Color::Green);
                text.setString("Start");
                text.setPosition(buttonShape.getPosition().x + 45, buttonShape.getPosition().y + 8);
                

                reset = true;
                resume = false; //���� �������� �ƴϵ���.
                hasStarted = false; //���� ���� ������ ��������.
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