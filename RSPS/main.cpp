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

    Text text; //rock슬라이더 text
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setCharacterSize(24);
    text.setPosition(380.f, 20.f);
    stringstream rockOffset;
    rockOffset << "Rocks: " << slider1.getOffset();


    Text textSci; //scissors슬라이더 text
    textSci.setFont(font);
    textSci.setFillColor(Color::White);
    textSci.setCharacterSize(24);
    textSci.setPosition(380.f, 60.f);
    stringstream scissorsoffset;
    scissorsoffset << "Scissors: " << slider2.getOffset();


    Text textPap; //paper 슬라이더 text
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



    // 윈도우 루프 시작
    while (window.isOpen())
    {
        sf::Event event;

        // 종료 여부 체크
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (initnum == 0 || rockinitnum == 1 || scisinitnum == 1 || paperinitnum == 1) { //맨 처음 아니면 슬라이더를 조정했을때 객체 개수 맞추기
            if (initnum == 0 || rockinitnum == 1) {
                if (rocks.size() < slider1.getOffset()) {
                    while (rocks.size() < slider1.getOffset()) {
                        Rock newRock = Rock(rock);
                        rocks.push_back(newRock); // 새로운 Rock 객체 추가
                    }
                }
                else if (rocks.size() > slider1.getOffset()) {
                    rocks.resize(slider1.getOffset()); // Rock 개수 줄이기
                }
                rockinitnum = 0;
            }
            if (initnum == 0 || scisinitnum == 1) {
                if (scissorss.size() < slider2.getOffset()) {
                    while (scissorss.size() < slider2.getOffset()) {
                        Scissors newScissors = Scissors(scissors);
                        scissorss.push_back(newScissors); // 새로운 scissors 객체 추가
                    }
                }
                else if (scissorss.size() > slider2.getOffset()) {
                    scissorss.resize(slider2.getOffset()); // scissors 개수 줄이기
                }
                scisinitnum = 0;
            }
            if (initnum == 0 || paperinitnum == 1) {
                if (papers.size() < slider3.getOffset()) {
                    while (papers.size() < slider3.getOffset()) {
                        Paper newPaper = Paper(paper);
                        papers.push_back(newPaper); // 새로운 paper 객체 추가
                    }
                }
                else if (papers.size() > slider3.getOffset()) {
                    papers.resize(slider3.getOffset()); // paper 개수 줄이기
                }
                paperinitnum = 0;
            }
        }
        initnum++;

        for (int i = 0; i < rocks.size(); ++i) { //rocks 랜덤으로 움직이기
            if (rocks[i].getSprite().getPosition().x > 0 && (rocks[i].getSprite().getPosition().x < window.getSize().x - rocks[i].getSprite().getGlobalBounds().width) && rocks[i].getSprite().getPosition().y > 0 && rocks[i].getSprite().getPosition().y < window.getSize().y - rocks[i].getSprite().getGlobalBounds().height)
                rocks[i].moveRandom();
            else if (rocks[i].getSprite().getPosition().x <= 0)//x좌표가 윈도우창 왼쪽을 벗어나려할때
                rocks[i].move(rightSpeed);
            else if (rocks[i].getSprite().getPosition().x >= window.getSize().x - rocks[i].getSprite().getGlobalBounds().width)//x좌표가 윈도우창 오른쪽을 벗어나려할때
                rocks[i].move(leftSpeed);
            else if (rocks[i].getSprite().getPosition().y <= 0)//y좌표가 윈도우창 위쪽을 벗어나려할때
                rocks[i].move(downSpeed);
            else ////y좌표가 윈도우창 아래쪽을 벗어나려할때
                rocks[i].move(upSpeed);
        }
        for (int i = 0; i < scissorss.size(); ++i) { //scissorss 랜덤으로 움직이기
            if (scissorss[i].getSprite().getPosition().x > 0 && (scissorss[i].getSprite().getPosition().x < window.getSize().x - scissorss[i].getSprite().getGlobalBounds().width) && scissorss[i].getSprite().getPosition().y > 0 && scissorss[i].getSprite().getPosition().y < window.getSize().y - scissorss[i].getSprite().getGlobalBounds().height)
                scissorss[i].moveRandom();
            else if (scissorss[i].getSprite().getPosition().x <= 0)//x좌표가 윈도우창 왼쪽을 벗어나려할때
                scissorss[i].move(rightSpeed);
            else if (scissorss[i].getSprite().getPosition().x >= window.getSize().x - scissorss[i].getSprite().getGlobalBounds().width)//x좌표가 윈도우창 오른쪽을 벗어나려할때
                scissorss[i].move(leftSpeed);
            else if (scissorss[i].getSprite().getPosition().y <= 0)//y좌표가 윈도우창 위쪽을 벗어나려할때
                scissorss[i].move(downSpeed);
            else ////y좌표가 윈도우창 아래쪽을 벗어나려할때
                scissorss[i].move(upSpeed);
        }
        for (int i = 0; i < papers.size(); ++i) { //papers 랜덤으로 움직이기
            if (papers[i].getSprite().getPosition().x > 0 && (papers[i].getSprite().getPosition().x < window.getSize().x - papers[i].getSprite().getGlobalBounds().width) && papers[i].getSprite().getPosition().y > 0 && papers[i].getSprite().getPosition().y < window.getSize().y - papers[i].getSprite().getGlobalBounds().height)
                papers[i].moveRandom();
            else if (papers[i].getSprite().getPosition().x <= 0)//x좌표가 윈도우창 왼쪽을 벗어나려할때
                papers[i].move(rightSpeed);
            else if (papers[i].getSprite().getPosition().x >= window.getSize().x - papers[i].getSprite().getGlobalBounds().width)//x좌표가 윈도우창 오른쪽을 벗어나려할때
                papers[i].move(leftSpeed);
            else if (papers[i].getSprite().getPosition().y <= 0)//y좌표가 윈도우창 위쪽을 벗어나려할때
                papers[i].move(downSpeed);
            else ////y좌표가 윈도우창 아래쪽을 벗어나려할때
                papers[i].move(upSpeed);
        }
        int scissize = scissorss.size();

        for (int i = 0; i < scissorss.size(); i++) { //가위가 보자기를 만났을 때
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


        // 화면 청소
        window.clear();

        // 화면에 글씨 쓰기
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

        // 띄우기
        window.display();
    }
}