#include <SFML/Graphics.hpp>
#include <string>
#include <exception>
#include <vector>
#include <sstream>
#include <iostream>
#include "RSP.h"
#include "Rock.h"
#include "Scissors.h"
#include "Paper.h"
#include "Slider.h"

int main(void)
{
    RenderWindow window(VideoMode(1500, 900), "RSPS", sf::Style::Titlebar | sf::Style::Close);
   
    
    Vector2f sliderPos1 = Vector2f(50.f, 20.f);
    Vector2f sliderPos2 = Vector2f(50.f, 60.f);
    Vector2f sliderPos3 = Vector2f(50.f, 100.f);
    Slider slider1(sliderPos1);
    Slider slider2(sliderPos2);
    Slider slider3(sliderPos3);

    Font font;
    if (!font.loadFromFile("Maplestory Light.ttf")) {
        throw exception("font error");
    }

    Text text; //rock�����̴� text
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setCharacterSize(24);
    text.setPosition(380.f, 20.f);
    stringstream rockOffset;
    rockOffset << "Rocks: " << slider1.getOffset();


    Text textSci; //scissors�����̴� text
    textSci.setFont(font);
    textSci.setFillColor(Color::White);
    textSci.setCharacterSize(24);
    textSci.setPosition(380.f, 60.f);
    stringstream scissorsoffset;
    scissorsoffset << "Scissors: " << slider2.getOffset();


    Text textPap; //paper �����̴� text
    textPap.setFont(font);
    textPap.setFillColor(Color::White);
    textPap.setCharacterSize(24);
    textPap.setPosition(380.f, 100.f);
    stringstream paperoffset;
    paperoffset << "Papaer: " << slider3.getOffset();




    Rock rock;
    Scissors scissors;
    Paper paper;
    //rock.getSprite().setPosition(500.f, 500.f);

    vector<Rock> rocks(270);
    vector<Scissors> scissorss(270);
    vector<Paper> papers(270);


   
   

    Vector2f leftSpeed = Vector2f(-0.1f, 0.f);
    Vector2f rightSpeed = Vector2f(0.1f, 0.f);
    Vector2f upSpeed = Vector2f(0.f, -0.1f);
    Vector2f downSpeed = Vector2f(0.f, 0.1f);

    int initnum = 0;
    int rockinitnum = 0;
    int scisinitnum = 0;
    int paperinitnum = 0;



    // ������ ���� ����
    while (window.isOpen())
    {
        sf::Event event;

        // ���� ���� üũ
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (initnum == 0 || rockinitnum == 1 || scisinitnum == 1 || paperinitnum == 1) { //�� ó�� �ƴϸ� �����̴��� ���������� ��ü ���� ���߱�
            if (initnum == 0 || rockinitnum == 1) {
                if (rocks.size() < slider1.getOffset()) {
                    while (rocks.size() < slider1.getOffset()) {
                        Rock newRock = Rock(rock);
                        rocks.push_back(newRock); // ���ο� Rock ��ü �߰�
                    }
                }
                else if (rocks.size() > slider1.getOffset()) {
                    rocks.resize(slider1.getOffset()); // Rock ���� ���̱�
                }
                rockinitnum = 0;
            }
            if (initnum == 0 || scisinitnum == 1) {
                if (scissorss.size() < slider2.getOffset()) {
                    while (scissorss.size() < slider2.getOffset()) {
                        Scissors newScissors = Scissors(scissors);
                        scissorss.push_back(newScissors); // ���ο� scissors ��ü �߰�
                    }
                }
                else if (scissorss.size() > slider2.getOffset()) {
                    scissorss.resize(slider2.getOffset()); // scissors ���� ���̱�
                }
                scisinitnum = 0;
            }
            if (initnum == 0 || paperinitnum == 1) {
                if (papers.size() < slider3.getOffset()) {
                    while (papers.size() < slider3.getOffset()) {
                        Paper newPaper = Paper(paper);
                        papers.push_back(newPaper); // ���ο� paper ��ü �߰�
                    }
                }
                else if (papers.size() > slider3.getOffset()) {
                    papers.resize(slider3.getOffset()); // paper ���� ���̱�
                }
                paperinitnum = 0;
            }
        }
        initnum++;

        for (int i = 0; i < rocks.size(); ++i) { //rocks �������� �����̱�
            if (rocks[i].getSprite().getPosition().x > 0 && (rocks[i].getSprite().getPosition().x < window.getSize().x - rocks[i].getSprite().getGlobalBounds().width) && rocks[i].getSprite().getPosition().y > 0 && rocks[i].getSprite().getPosition().y < window.getSize().y - rocks[i].getSprite().getGlobalBounds().height)
                rocks[i].moveRandom();
            else if (rocks[i].getSprite().getPosition().x <= 0)//x��ǥ�� ������â ������ ������Ҷ�
                rocks[i].move(rightSpeed);
            else if (rocks[i].getSprite().getPosition().x >= window.getSize().x - rocks[i].getSprite().getGlobalBounds().width)//x��ǥ�� ������â �������� ������Ҷ�
                rocks[i].move(leftSpeed);
            else if (rocks[i].getSprite().getPosition().y <= 0)//y��ǥ�� ������â ������ ������Ҷ�
                rocks[i].move(downSpeed);
            else ////y��ǥ�� ������â �Ʒ����� ������Ҷ�
                rocks[i].move(upSpeed);
        }
        for (int i = 0; i < scissorss.size(); ++i) { //scissorss �������� �����̱�
            if (scissorss[i].getSprite().getPosition().x > 0 && (scissorss[i].getSprite().getPosition().x < window.getSize().x - scissorss[i].getSprite().getGlobalBounds().width) && scissorss[i].getSprite().getPosition().y > 0 && scissorss[i].getSprite().getPosition().y < window.getSize().y - scissorss[i].getSprite().getGlobalBounds().height)
                scissorss[i].moveRandom();
            else if (scissorss[i].getSprite().getPosition().x <= 0)//x��ǥ�� ������â ������ ������Ҷ�
                scissorss[i].move(rightSpeed);
            else if (scissorss[i].getSprite().getPosition().x >= window.getSize().x - scissorss[i].getSprite().getGlobalBounds().width)//x��ǥ�� ������â �������� ������Ҷ�
                scissorss[i].move(leftSpeed);
            else if (scissorss[i].getSprite().getPosition().y <= 0)//y��ǥ�� ������â ������ ������Ҷ�
                scissorss[i].move(downSpeed);
            else ////y��ǥ�� ������â �Ʒ����� ������Ҷ�
                scissorss[i].move(upSpeed);
        }
        for (int i = 0; i < papers.size(); ++i) { //papers �������� �����̱�
            if (papers[i].getSprite().getPosition().x > 0 && (papers[i].getSprite().getPosition().x < window.getSize().x - papers[i].getSprite().getGlobalBounds().width) && papers[i].getSprite().getPosition().y > 0 && papers[i].getSprite().getPosition().y < window.getSize().y - papers[i].getSprite().getGlobalBounds().height)
                papers[i].moveRandom();
            else if (papers[i].getSprite().getPosition().x <= 0)//x��ǥ�� ������â ������ ������Ҷ�
                papers[i].move(rightSpeed);
            else if (papers[i].getSprite().getPosition().x >= window.getSize().x - papers[i].getSprite().getGlobalBounds().width)//x��ǥ�� ������â �������� ������Ҷ�
                papers[i].move(leftSpeed);
            else if (papers[i].getSprite().getPosition().y <= 0)//y��ǥ�� ������â ������ ������Ҷ�
                papers[i].move(downSpeed);
            else ////y��ǥ�� ������â �Ʒ����� ������Ҷ�
                papers[i].move(upSpeed);
        }
        int scissize = scissorss.size();

        for (int i = 0; i < scissorss.size(); i++) { //������ ���ڱ⸦ ������ ��
            for (int j = 0; j < papers.size(); j++) {
                if (scissorss[i].getSprite().getPosition().x - papers[j].getSprite().getPosition().x <= 1.0f && scissorss[i].getSprite().getPosition().y - papers[j].getSprite().getPosition().y <= 1.0f) {
                    Scissors newScissors = Scissors(scissors, papers[j].getSprite().getPosition().x, papers[j].getSprite().getPosition().y);


                    scissorss.push_back(newScissors);
                    papers.erase(papers.begin() + j);
                    j--;
                }

            }
        }


        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rock.getSprite().getPosition().x > 0) {
            rock.move(leftSpeed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sGood.getPosition().x < window.getSize().x - sGood.getGlobalBounds().width) {
            sGood.move(speed, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sGood.getPosition().y > 0) {
            sGood.move(0, -speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sGood.getPosition().y < window.getSize().y - sGood.getGlobalBounds().height) {
            sGood.move(0, speed);
        }
        */


        slider1.handleEvent(event, window);
        text.setString("Rocks: " + to_string(slider1.getOffset()));
        if (slider1.getstoredValue() == 1) {
            rockinitnum = 1;
            slider1.setstoredValue(0);
        }
        slider2.handleEvent(event, window);
        textSci.setString("Scissors: " + to_string(slider2.getOffset()));
        if (slider2.getstoredValue() == 1) {
            scisinitnum = 1;
            slider2.setstoredValue(0);
        }
        slider3.handleEvent(event, window);
        textPap.setString("Papers: " + to_string(slider3.getOffset()));
        if (slider3.getstoredValue() == 1) {
            paperinitnum = 1;
            slider3.setstoredValue(0);
        }


        // ȭ�� û��
        window.clear();

        // ȭ�鿡 �۾� ����
        slider1.draw(window);
        slider2.draw(window);
        slider3.draw(window);

        for (int i = 0; i < rocks.size(); i++) {
            rocks[i].draw(window);
        }
        for (int i = 0; i < scissorss.size(); i++) {
            scissorss[i].draw(window);
        }
        for (int i = 0; i < papers.size(); i++) {
            papers[i].draw(window);
        }
        window.draw(text);
        window.draw(textSci);
        window.draw(textPap);

        // ����
        window.display();
    }
}