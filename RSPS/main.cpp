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

    Text debug;
    debug.setFont(font);
    debug.setFillColor(Color::White);
    debug.setCharacterSize(24);
    debug.setPosition(380.f, 200.f);



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

        //���� �����̱⵵ ���� ���� ������ ����: �ٸ� ��Ŀ������ ������ ����.
        //���ϱ�, �ѱ�
        //�ӷ��� ���͸� ���� �׻� 1�� �����ǵ���.

        /*for (int i = 0; i < rocks.size(); ++i) { //rocks �������� �����̱�
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
 */
        //�浹 �κе� hitby�� ���� ������ ����. hitby�� bool��, ������Ʈ3�� hasintersected�� �� ����� �Լ��� �� �� ����.
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
        textRock.setString("Rocks: " + to_string(slider1.getOffset()));

        slider2.handleEvent(event, window);
        textSci.setString("Scissors: " + to_string(slider2.getOffset()));

        slider3.handleEvent(event, window);
        textPap.setString("Papers: " + to_string(slider3.getOffset()));
        
        if (rocks.size() > 0 && papers.size() > 0) {
            float magnitude = sqrt(rocks[0].nearest(papers).x * rocks[0].nearest(papers).x + rocks[0].nearest(papers).y * rocks[0].nearest(papers).y) * 5;
            Vector2f hellothere = Vector2f(rocks[0].nearest(papers).x / magnitude, rocks[0].nearest(papers).y / magnitude);
            rocks[0].move(hellothere);
            debug.setString(to_string(rocks[0].nearest(papers).x) + " " + to_string(rocks[0].nearest(papers).y));
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
        if (rocks.size() > 0 && papers.size() > 0) {
            window.draw(debug);
        }

        // ����
        window.display();
    }
}
