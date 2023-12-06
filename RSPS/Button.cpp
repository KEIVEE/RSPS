#include <iostream>
#include "Button.h"


Button::Button(Vector2f position, Text& text) {
    isButtonPressed = false;
    buttonShape.setSize(Vector2f(200, 70)); // 버튼 크기 설정
    buttonShape.setPosition(position);
    //원래는 게임이 끝나면 화면 가운데에 다른 버튼을 만들 생각으로 버튼 생성자에 position을 만들어달라 했었는데
    //이것도 나쁘지 않은듯
    buttonShape.setFillColor(Color::Green);

    text.setCharacterSize(40);
    text.setPosition(position.x + 45, position.y + 8); // 텍스트 위치 조정
    text.setFillColor(Color::White);
}

void Button::handleEvent(Event event, RenderWindow& window, bool& hasStarted, bool& reset, bool& resume, Text& text) {
    //원래 제공받은 인자에서 하나 더 추가: pause를 구현하기 위함
    if (event.type == Event::MouseButtonPressed) {
        Vector2i mousePosition = Mouse::getPosition(window);

        if (buttonShape.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition)) && !isButtonPressed) {
            // 버튼이 클릭되었을 때 처리할 작업

            if (text.getString()=="Start"){ //start는 두가지 경우가 있다. 게임 시작을 위한 start, 게임 계속 진행을 위한 start
                if (hasStarted == false) { //만약 전자다: 게임 시작을 위한 start
                    buttonShape.setFillColor(Color::Red);
                    text.setString("Pause");
                    hasStarted = true; //게임 시작
                    resume = true; //게임 진행
                }
                else {
                    buttonShape.setFillColor(Color::Red);//만약 후자다: 게임 재개를 위한 start
                    text.setString("Pause"); 
                    resume = true; //게임 진행만.
                }
            }
            else if(text.getString()=="Pause" && hasStarted == true){ //pause는 게임 일시정지의 역할을 한다
                buttonShape.setFillColor(Color::Green);
                text.setString("Start");
                resume = false;//이 작업을 함으로써 객체 움직임만 멈출 수 있게 됨.
            }
            else if(text.getString()=="Restart" && hasStarted == true){  //restart일 때
                buttonShape.setFillColor(Color::Green);
                text.setString("Start");
                text.setPosition(buttonShape.getPosition().x + 45, buttonShape.getPosition().y + 8);
                

                reset = true;
                resume = false; //게임 진행중이 아니도록.
                hasStarted = false; //게임 시작 전으로 돌리도록.
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