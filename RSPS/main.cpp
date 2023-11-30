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
    //������ ũ�⸦ ��üȭ������ ���� �ʰ� �����ϴ� ����:
    /*
    ��üȭ�� �� �� �����̴� Ŭ�� �νĿ� ������ �߻�, ���콺�� �� �����̴��� �����̴� ������ �߻�
    ��üȭ���� �ƴ� ���� ���ϴ´�� ������

    ȭ�� ũ�⸦ �����ϸ� �� ������ ���� ȭ���� �����ϰ� �Ǿ� �׷����� ������,
    �����̴��� Ŭ���ص� �� �˾ƸԱ� ������ ���� �Ұ� ��ġ
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






    // ������ ���� ����
    while (window.isOpen())
    {
        Event event;

        // ���� ���� üũ
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
                rocks.push_back(newRock); // ���ο� Rock ��ü �߰�
            }
        }
        else if (rocks.size() > slider1.getOffset()) {
            rocks.resize(slider1.getOffset()); // Rock ���� ���̱�
        }
        // ȭ�� û��
        window.clear();

        // ȭ�鿡 �۾� ����
        slider1.draw(window);
        for (int i = 0; i < rocks.size(); i++) {
            rocks[i].draw(window);
        }
        
        window.draw(text);

        // ����
        window.display();
    }
}

