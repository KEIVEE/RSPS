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

    Text textRock; //rock�����̴� text
    textRock.setFont(font);
    textRock.setFillColor(Color::White);
    textRock.setCharacterSize(24);
    textRock.setPosition(380.f, 20.f);



    Text textSci; //scissors�����̴� text
    textSci.setFont(font);
    textSci.setFillColor(Color::White);
    textSci.setCharacterSize(24);
    textSci.setPosition(380.f, 60.f);



    Text textPap; //paper �����̴� text
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
    //��ŸƮ ��ư�� ������ hasstarted�� true�� �� ���̴�. �����̴��� �̰� false�� ���� ��Ÿ����, true�� ���� ��


    // ������ ���� ����
    while (window.isOpen())
    {
        sf::Event event;

        // ���� ���� üũ
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (hasStarted == false) { //�� ó�� �ƴϸ� �����̴��� ���������� ��ü ���� ���߱�
                if (rocks.size() < slider1.getOffset()) {
                    while (rocks.size() < slider1.getOffset()) {
                        Rock newRock = Rock(rock);
                        rocks.push_back(newRock); // ���ο� Rock ��ü �߰�
                    }
                }
                else if (rocks.size() > slider1.getOffset()) {
                    rocks.resize(slider1.getOffset()); // Rock ���� ���̱�
                }
                if (scissorss.size() < slider2.getOffset()) {
                    while (scissorss.size() < slider2.getOffset()) {
                        Scissors newScissors = Scissors(scissors);
                        scissorss.push_back(newScissors); // ���ο� scissors ��ü �߰�
                    }
                }
                else if (scissorss.size() > slider2.getOffset()) {
                    scissorss.resize(slider2.getOffset()); // scissors ���� ���̱�
                }
                if (papers.size() < slider3.getOffset()) {
                    while (papers.size() < slider3.getOffset()) {
                        Paper newPaper = Paper(paper);
                        papers.push_back(newPaper); // ���ο� paper ��ü �߰�
                    }
                }
                else if (papers.size() > slider3.getOffset()) {
                    papers.resize(slider3.getOffset()); // paper ���� ���̱�
            }
        }



        slider1.handleEvent(event, window);
        textRock.setString("Rocks: " + to_string(slider1.getOffset()));

        slider2.handleEvent(event, window);
        textSci.setString("Scissors: " + to_string(slider2.getOffset()));

        slider3.handleEvent(event, window);
        textPap.setString("Papers: " + to_string(slider3.getOffset()));
        
        if (rocks.size() > 0 && scissorss.size() > 0 && papers.size() > 0) { //�� �� 1���� ���� ��: ��ư�� ����� ��ư�� ���Ǳ��� �߰�
            //��� �ϳ��� 0�� �� ��ư�� ������? �� �ڵ�� ���ư��� �ʴµ�,
            //�� ���¿����� �� �ٸ� ��ư�� ��Ÿ�� �ٽ� �����̴� �����϶�� �ϴ� ����� ������ ����.

            for (int i = 0; i < rocks.size(); i++) { //rock�� ���
                float rockChaseMagnitude = sqrt(rocks[i].nearest(scissorss).x * rocks[i].nearest(scissorss).x + rocks[i].nearest(scissorss).y * rocks[i].nearest(scissorss).y) * 2;
                //���� ����� �������� �Ÿ�: �Ѿư��� ��
                float rockAvoidMagnitude = sqrt(rocks[i].nearest(papers).x * rocks[i].nearest(papers).x + rocks[i].nearest(papers).y * rocks[i].nearest(papers).y) * 2;
                //���� ����� ���ڱ���� �Ÿ�: ���ؾ� ��
                
                Vector2f rockChaseVelocity = Vector2f(rocks[i].nearest(scissorss).x / rockChaseMagnitude, rocks[i].nearest(scissorss).y / rockChaseMagnitude);
                //���� ����� �������� ��ġ ���̸� �������� ���� �ӵ�(1�� �ƴϱ� ��) ���͸� ����
                Vector2f rockAvoidVelocity = Vector2f(-rocks[i].nearest(papers).x / rockAvoidMagnitude, -rocks[i].nearest(papers).y / rockAvoidMagnitude);
                //���� ����� ���ڱ���� ��ġ ���̸� �������� ���� �ӵ�(1�� �ƴϱ� ��) ���͸� ����
                
                Vector2f rockVelocity = (rockChaseMagnitude >= rockAvoidMagnitude ? rockAvoidVelocity : rockChaseVelocity);
                //�� �߿� � ���͸� �� ���ΰ�: ���� ����� ���ڱ�� ���� ����� ������ �Ÿ��� ����: �� �� ���ڱⰡ ������ �ϸ� ���ؾ� �ϰ�, �� �� ������ ������ �ϸ� �Ѿƾ� �ϰ�
                //�����, ������ ������ ������ �Ѵ� ���͸� ����, ���ڱ�� ������ ���ڱ⸦ ���ϴ� ���͸� ����
                rocks[i].move(rockVelocity, window);
            }
            
            for (int i = 0; i < scissorss.size(); i++) {
                float scissorsChaseMagnitude = sqrt(scissorss[i].nearest(papers).x * scissorss[i].nearest(papers).x + scissorss[i].nearest(papers).y * scissorss[i].nearest(papers).y) * 2;
                //���� ����� ���ڱ���� �Ÿ�: �Ѿƾ� ��
                float scissorsAvoidMagnitude = sqrt(scissorss[i].nearest(rocks).x * scissorss[i].nearest(rocks).x + scissorss[i].nearest(rocks).y * scissorss[i].nearest(rocks).y) * 2;
                //���� ����� �������� �Ÿ�

                Vector2f scissorsChaseVelocity = Vector2f(scissorss[i].nearest(papers).x / scissorsChaseMagnitude, scissorss[i].nearest(papers).y / scissorsChaseMagnitude);
                //���ڱ⸦ �Ѵ� �ӵ� ����
                Vector2f scissorsAvoidVelocity = Vector2f(-scissorss[i].nearest(rocks).x / scissorsAvoidMagnitude, -scissorss[i].nearest(rocks).y / scissorsAvoidMagnitude);
                //������ ���ϴ� �ӵ� ����

                
                Vector2f scissorsVelocity = (scissorsChaseMagnitude >= scissorsAvoidMagnitude ? scissorsAvoidVelocity : scissorsChaseVelocity);
                //���� �� ���� ũ���� �Ÿ��� ���� ���͸� ����
                scissorss[i].move(scissorsVelocity, window);
            }

            for (int i = 0; i < papers.size(); i++) {
                float paperChaseMagnitude = sqrt(papers[i].nearest(rocks).x * papers[i].nearest(rocks).x + papers[i].nearest(rocks).y * papers[i].nearest(rocks).y) * 2;
                //���� ����� �������� �Ÿ�
                float paperAvoidMagnitude = sqrt(papers[i].nearest(scissorss).x * papers[i].nearest(scissorss).x + papers[i].nearest(scissorss).y * papers[i].nearest(scissorss).y) * 2;
                //���� ����� �������� �Ÿ�

                Vector2f paperChaseVelocity = Vector2f(papers[i].nearest(rocks).x / paperChaseMagnitude, papers[i].nearest(rocks).y / paperChaseMagnitude);
                //���� ����� ������ �Ѵ� ����
                Vector2f paperAvoidVelocity = Vector2f(-papers[i].nearest(scissorss).x / paperAvoidMagnitude, -papers[i].nearest(scissorss).y / paperAvoidMagnitude);
                //���� ����� ������ ���ϴ� ����

                Vector2f paperVelocity = (paperChaseMagnitude >= paperAvoidMagnitude ? paperAvoidVelocity : paperChaseVelocity);
                //�� ���� �� �� ����� ���� ���͸� ����

                papers[i].move(paperVelocity, window);
            }
            
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
        window.draw(textRock);
        window.draw(textSci);
        window.draw(textPap);

        // ����
        window.display();
    }
}
