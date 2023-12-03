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
   
    
    Vector2f sliderRockPos = Vector2f(50.f, 20.f);
    Vector2f sliderSciPos = Vector2f(50.f, 60.f);
    Vector2f sliderPaperPos = Vector2f(50.f, 100.f);
    Slider slider1(sliderRockPos);
    Slider slider2(sliderSciPos);
    Slider slider3(sliderPaperPos);

    Font font;
    if (!font.loadFromFile("Maplestory Light.ttf")) {
        throw exception("font error");
    }

    Text textRock; //rock슬라이더 text
    textRock.setFont(font);
    textRock.setFillColor(Color::White);
    textRock.setCharacterSize(24);
    textRock.setPosition(380.f, 20.f);



    Text textSci; //scissors슬라이더 text
    textSci.setFont(font);
    textSci.setFillColor(Color::White);
    textSci.setCharacterSize(24);
    textSci.setPosition(380.f, 60.f);



    Text textPap; //paper 슬라이더 text
    textPap.setFont(font);
    textPap.setFillColor(Color::White);
    textPap.setCharacterSize(24);
    textPap.setPosition(380.f, 100.f);



    Rock rock;
    Scissors scissors;
    Paper paper;

    vector<Rock> rocks(270);
    vector<Scissors> scissorss(270);
    vector<Paper> papers(270);


   
   

    Vector2f leftSpeed = Vector2f(-0.1f, 0.f);
    Vector2f rightSpeed = Vector2f(0.1f, 0.f);
    Vector2f upSpeed = Vector2f(0.f, -0.1f);
    Vector2f downSpeed = Vector2f(0.f, 0.1f);

    bool hasStarted = false;
    //스타트 버튼을 누르면 hasstarted가 true가 될 것이다. 슬라이더는 이게 false일 때만 나타나고, true면 숨길 것


    // 윈도우 루프 시작
    while (window.isOpen())
    {
        sf::Event event;

        // 종료 여부 체크
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (hasStarted == false) { //맨 처음 아니면 슬라이더를 조정했을때 객체 개수 맞추기
                if (rocks.size() < slider1.getOffset()) {
                    while (rocks.size() < slider1.getOffset()) {
                        Rock newRock = Rock(rock);
                        rocks.push_back(newRock); // 새로운 Rock 객체 추가
                    }
                }
                else if (rocks.size() > slider1.getOffset()) {
                    rocks.resize(slider1.getOffset()); // Rock 개수 줄이기
                }
                if (scissorss.size() < slider2.getOffset()) {
                    while (scissorss.size() < slider2.getOffset()) {
                        Scissors newScissors = Scissors(scissors);
                        scissorss.push_back(newScissors); // 새로운 scissors 객체 추가
                    }
                }
                else if (scissorss.size() > slider2.getOffset()) {
                    scissorss.resize(slider2.getOffset()); // scissors 개수 줄이기
                }
                if (papers.size() < slider3.getOffset()) {
                    while (papers.size() < slider3.getOffset()) {
                        Paper newPaper = Paper(paper);
                        papers.push_back(newPaper); // 새로운 paper 객체 추가
                    }
                }
                else if (papers.size() > slider3.getOffset()) {
                    papers.resize(slider3.getOffset()); // paper 개수 줄이기
            }
        }



        slider1.handleEvent(event, window);
        textRock.setString("Rocks: " + to_string(slider1.getOffset()));

        slider2.handleEvent(event, window);
        textSci.setString("Scissors: " + to_string(slider2.getOffset()));

        slider3.handleEvent(event, window);
        textPap.setString("Papers: " + to_string(slider3.getOffset()));
        
        if (rocks.size() > 0 && scissorss.size() > 0 && papers.size() > 0) { //셋 다 1개라도 있을 때: 버튼이 생기면 버튼의 조건까지 추가
            //어느 하나라도 0일 때 버튼을 누르면? 이 코드는 돌아가지 않는데,
            //그 상태에서는 또 다른 버튼이 나타나 다시 슬라이더 조정하라고 하는 기능을 구현할 생각.

            for (int i = 0; i < rocks.size(); i++) { //rock의 경우
                float rockChaseMagnitude = sqrt(rocks[i].nearest(scissorss).x * rocks[i].nearest(scissorss).x + rocks[i].nearest(scissorss).y * rocks[i].nearest(scissorss).y) * 2;
                //가장 가까운 가위와의 거리: 쫓아가야 함
                float rockAvoidMagnitude = sqrt(rocks[i].nearest(papers).x * rocks[i].nearest(papers).x + rocks[i].nearest(papers).y * rocks[i].nearest(papers).y) * 2;
                //가장 가까운 보자기와의 거리: 피해야 함
                
                Vector2f rockChaseVelocity = Vector2f(rocks[i].nearest(scissorss).x / rockChaseMagnitude, rocks[i].nearest(scissorss).y / rockChaseMagnitude);
                //가장 가까운 가위와의 위치 차이를 바탕으로 단위 속도(1이 아니긴 함) 벡터를 생성
                Vector2f rockAvoidVelocity = Vector2f(-rocks[i].nearest(papers).x / rockAvoidMagnitude, -rocks[i].nearest(papers).y / rockAvoidMagnitude);
                //가장 가까운 보자기와의 위치 차이를 바탕으로 단위 속도(1이 아니긴 함) 벡터를 생성
                
                Vector2f rockVelocity = (rockChaseMagnitude >= rockAvoidMagnitude ? rockAvoidVelocity : rockChaseVelocity);
                //둘 중에 어떤 벡터를 쓸 것인가: 가장 가까운 보자기와 가장 가까운 가위의 거리를 생각: 그 중 보자기가 가깝다 하면 피해야 하고, 그 중 가위가 가깝다 하면 쫓아야 하고
                //결론은, 가위랑 가까우면 가위를 쫓는 벡터를 선택, 보자기랑 가까우면 보자기를 피하는 벡터를 선택
                rocks[i].move(rockVelocity, window);
            }
            
            for (int i = 0; i < scissorss.size(); i++) {
                float scissorsChaseMagnitude = sqrt(scissorss[i].nearest(papers).x * scissorss[i].nearest(papers).x + scissorss[i].nearest(papers).y * scissorss[i].nearest(papers).y) * 2;
                //가장 가까운 보자기와의 거리: 쫓아야 함
                float scissorsAvoidMagnitude = sqrt(scissorss[i].nearest(rocks).x * scissorss[i].nearest(rocks).x + scissorss[i].nearest(rocks).y * scissorss[i].nearest(rocks).y) * 2;
                //가장 가까운 바위와의 거리

                Vector2f scissorsChaseVelocity = Vector2f(scissorss[i].nearest(papers).x / scissorsChaseMagnitude, scissorss[i].nearest(papers).y / scissorsChaseMagnitude);
                //보자기를 쫓는 속도 벡터
                Vector2f scissorsAvoidVelocity = Vector2f(-scissorss[i].nearest(rocks).x / scissorsAvoidMagnitude, -scissorss[i].nearest(rocks).y / scissorsAvoidMagnitude);
                //바위를 피하는 속도 벡터

                
                Vector2f scissorsVelocity = (scissorsChaseMagnitude >= scissorsAvoidMagnitude ? scissorsAvoidVelocity : scissorsChaseVelocity);
                //벡터 중 작은 크기의 거리를 가진 벡터를 선택
                scissorss[i].move(scissorsVelocity, window);
            }

            for (int i = 0; i < papers.size(); i++) {
                float paperChaseMagnitude = sqrt(papers[i].nearest(rocks).x * papers[i].nearest(rocks).x + papers[i].nearest(rocks).y * papers[i].nearest(rocks).y) * 2;
                //가장 가까운 바위와의 거리
                float paperAvoidMagnitude = sqrt(papers[i].nearest(scissorss).x * papers[i].nearest(scissorss).x + papers[i].nearest(scissorss).y * papers[i].nearest(scissorss).y) * 2;
                //가장 가까운 가위와의 거리

                Vector2f paperChaseVelocity = Vector2f(papers[i].nearest(rocks).x / paperChaseMagnitude, papers[i].nearest(rocks).y / paperChaseMagnitude);
                //가장 가까운 바위를 쫓는 벡터
                Vector2f paperAvoidVelocity = Vector2f(-papers[i].nearest(scissorss).x / paperAvoidMagnitude, -papers[i].nearest(scissorss).y / paperAvoidMagnitude);
                //가장 가까운 가위를 피하는 벡터

                Vector2f paperVelocity = (paperChaseMagnitude >= paperAvoidMagnitude ? paperAvoidVelocity : paperChaseVelocity);
                //두 벡터 중 더 가까운 놈의 벡터를 선택

                papers[i].move(paperVelocity, window);
            }
            
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
        window.draw(textRock);
        window.draw(textSci);
        window.draw(textPap);

        // 띄우기
        window.display();
    }
}
