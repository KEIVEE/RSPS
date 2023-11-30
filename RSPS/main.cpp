#include <string>
#include <exception>
#include <vector>
#include <sstream>
#include <iostream>
#include "RSP.h"
#include "Rock.h"
#include "Slider.h"

int main(void)
{
    RenderWindow window(VideoMode(1500, 900), "RSPS", sf::Style::Titlebar | sf::Style::Close);
    //윈도우 크기를 전체화면으로 하지 않고 고정하는 이유:
    /*
    전체화면 할 시 슬라이더 클릭 인식에 오류가 발생, 마우스를 뗴도 슬라이더가 움직이는 현상이 발생
    전체화면이 아닐 때는 원하는대로 움직임

    화면 크기를 조정하면 그 비율에 따라 화면을 조정하게 되어 그래픽이 깨지고,
    슬라이더를 클릭해도 못 알아먹기 때문에 조절 불가 조치
    */
    Vector2f sliderPos = Vector2f(50.f, 20.f);
    Slider slider1(sliderPos);

    Font font;
    if (!font.loadFromFile("Maplestory Light.ttf")) {
        throw exception("font error");
    }

    Text text;
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setCharacterSize(24);
    text.setPosition(380.f, 20.f);

    stringstream rockOffset;
    rockOffset << "Rocks: " << slider1.getOffset();
    
    
    Rock rock;
    //rock.getSprite().setPosition(500.f, 500.f);
    
    vector<Rock> rocks(90);




    Vector2f leftSpeed = Vector2f(-0.1f, 0.f);
    Vector2f rightSpeed = Vector2f(0.1f, 0.f);
    Vector2f upSpeed = Vector2f(0.f, -0.1f);
    Vector2f downSpeed = Vector2f(0.f, 0.1f);






    // 윈도우 루프 시작
    while (window.isOpen())
    {
        Event event;

        // 종료 여부 체크
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rock.getSprite().getPosition().x > 0) {
            rock.move(leftSpeed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rock.getSprite().getPosition().x < window.getSize().x - rock.getSprite().getGlobalBounds().width) {
            rock.move(rightSpeed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rock.getSprite().getPosition().y > 0) {
            rock.move(upSpeed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rock.getSprite().getPosition().y < window.getSize().y - rock.getSprite().getGlobalBounds().height) {
            rock.move(downSpeed);
        }
        */

        slider1.handleEvent(event, window);
        text.setString("Rocks: " + to_string(slider1.getOffset()));

        if (rocks.size() < slider1.getOffset()) {
            while (rocks.size() < slider1.getOffset()) {
                Rock newRock = Rock(rock);
                rocks.push_back(newRock); // 새로운 Rock 객체 추가
            }
        }
        else if (rocks.size() > slider1.getOffset()) {
            rocks.resize(slider1.getOffset()); // Rock 개수 줄이기
        }
        // 화면 청소
        window.clear();

        // 화면에 글씨 쓰기
        slider1.draw(window);
        for (int i = 0; i < rocks.size(); i++) {
            rocks[i].draw(window);
        }
        
        window.draw(text);

        // 띄우기
        window.display();
    }
}

