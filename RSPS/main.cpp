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
#include "Button.h"

int main(void)
{ 
    RenderWindow window(VideoMode(1500, 900), "RSPS", sf::Style::Titlebar | sf::Style::Close);
    //1500 * 900 ũ�� â, ũ�� ���� �Ұ�, ��üȭ�� �Ұ�
    
    Vector2f sliderRockPos = Vector2f(50.f, 20.f); //���������̴� ��ġ
    Vector2f sliderSciPos = Vector2f(50.f, 60.f); //���� �����̴� ��ġ
    Vector2f sliderPaperPos = Vector2f(50.f, 100.f); //�� �����̴� ��ġ
    Slider slider1(sliderRockPos); //���� �����̴�
    Slider slider2(sliderSciPos); //���� �����̴�
    Slider slider3(sliderPaperPos); //�� �����̴�

    Font font;
    if (!font.loadFromFile("Maplestory Light.ttf")) { //�۾�ü
        throw exception("font error");
    }

    Text textRock; //rock ���� text
    textRock.setFont(font);
    textRock.setFillColor(Color::White);
    textRock.setCharacterSize(24);
    textRock.setPosition(380.f, 20.f);



    Text textSci; //scissors ���� text
    textSci.setFont(font);
    textSci.setFillColor(Color::White);
    textSci.setCharacterSize(24);
    textSci.setPosition(380.f, 60.f);



    Text textPap; //paper ���� text
    textPap.setFont(font);
    textPap.setFillColor(Color::White);
    textPap.setCharacterSize(24);
    textPap.setPosition(380.f, 100.f);


    Text result; //���� �̰���� �˷��ִ� �ؽ�Ʈ
    result.setFont(font);
    result.setFillColor(Color::White);
    result.setCharacterSize(80);
    result.setPosition(700.f, 420.f);

     
    // ��ư ��ü ����
  
    Vector2f buttonPos = Vector2f(1200.f, 50.f); //��ġ
    Text textButton; //����
    textButton.setFont(font);
    textButton.setString("Start");
    Button myButton(buttonPos,textButton);


    Rock rock; //copy constructor�� ���� ���� ����. copy constructor�� ��� �ؽ�ó�� ������ �ʾ���
    Scissors scissors;
    Paper paper;


    Texture rockTexture;
    if (!rockTexture.loadFromFile("rock.png")) {
        // �ؽ�ó �ε� ���� ó��
        return EXIT_FAILURE;
    }
    Texture scissorsTexture;
    if (!scissorsTexture.loadFromFile("scissors.png")) {
        // �ؽ�ó �ε� ���� ó��
        return EXIT_FAILURE;
    }
    Texture paperTexture;
    if (!paperTexture.loadFromFile("paper.png")) {
        // �ؽ�ó �ε� ���� ó��
        return EXIT_FAILURE;
    }

    vector<Rock> rocks(270); //rock�� �ִ��� ���� �� �ִ� ũ��� 270
    /*
    ó������ ���ġ ������ �־���
    ���ġ ������ ����
    Rock �����̴��� �÷� �ָ� 10��, 20�� �뿡�� ������ ���ο� ���� ��ġ�� ��� rock�� �̵��ϴ� ����
    �� ������ �̰ɷ� �ذ��ߴµ�, ������ ���� ������ 270�̶�� ������ ���� �ʾƵ� ���ġ�� �߻����� ������
    �׳� ��
    */
    vector<Scissors> scissorss(270);
    vector<Paper> papers(270);

    bool hasStarted = false; //������ �����߳�? ��ŸƮ ��ư�� ������ hasstarted�� true�� �� ���̴�. �����̴��� �̰� false�� ���� ��Ÿ����, true�� ���� ��
    bool reset = false; //������ �� ���ΰ�?
    bool resume = false; //������ ���� ���ΰ�?: hasStarted�ʹ� �ٸ� �����̴�. Pause��ư�� ���� ���� ���� ������� ���� �ȴ�.
    /*
    pause�� �� hasStarted�� false�� ��������� �����̴��� ��Ÿ�������� �׿� ���� ������ ��ü�� ä������ �Ѵ� ��ü�� �پ������ ���� �߻�
    �׷��� pause�� ���ٱ� ������ pause�� ����ΰ� ��¥�� ����ٰ� �����ϴ� ���� ����
    hasStarted�� true�� �ּ� �����̴��� ��Ÿ���� �ʰ� �ϸ鼭�� ��ü�� �������� �ʾƾ� �ϹǷ� �� ������ �߰�
    */
    bool ended = false; //������ ������?
    /*
    ������ ������ �� ��� ��ü�� ȭ�鿡�� ������� ������ �߻�
    �� �׷������� ������ �𸣰�����, ������ �����ٴ� ������ �߰��ϰ�
    ������ �����ٸ� ��ü�� �������� �ʰ� �����ν� ���� �ذ�
    */
    
    
    
    // ������ ���� ����
    while (window.isOpen())
    {
        sf::Event event;

        // ���� ���� üũ
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        

        if (hasStarted == false) {
            /*
            �ڵ� �̺�Ʈ �Լ��� ��ġ�� ����:
            �ڵ��̺�Ʈ�� �׻� ���ư��ٸ� �����̴��� �� �ڸ��� �������� Ŭ�� �巡�� �� ��ȭ�� ����� ������ �߻�
            �׷��� �̺�Ʈ �ڵ鸵�� ���� �ȿ� �����ϵ��� ��
            �̰� ���� �˱� ������ �׷��� ��ġ�� ���ݾ�
            */
            slider1.handleEvent(event, window);
            slider2.handleEvent(event, window);
            slider3.handleEvent(event, window);
                if (rocks.size() < slider1.getOffset()) {
                    while (rocks.size() < slider1.getOffset()) {
                        Rock newRock = Rock(rock, rockTexture);
                        
                        rocks.push_back(newRock); // ���ο� Rock ��ü �߰�
                    }
                }
                else if (rocks.size() > slider1.getOffset()) {
                    rocks.resize(slider1.getOffset()); // Rock ���� ���̱�
                }
                if (scissorss.size() < slider2.getOffset()) {
                    while (scissorss.size() < slider2.getOffset()) {
                        Scissors newScissors = Scissors(scissors,scissorsTexture);
                        scissorss.push_back(newScissors); // ���ο� scissors ��ü �߰�  
                    }
                }
                else if (scissorss.size() > slider2.getOffset()) {
                    scissorss.resize(slider2.getOffset()); // scissors ���� ���̱�
                }
                if (papers.size() < slider3.getOffset()) {
                    while (papers.size() < slider3.getOffset()) {
                        Paper newPaper = Paper(paper,paperTexture);
                        papers.push_back(newPaper); // ���ο� paper ��ü �߰�
                    }
                }
                else if (papers.size() > slider3.getOffset()) {
                    papers.resize(slider3.getOffset()); // paper ���� ���̱�
            }
                
        }

        
        if (hasStarted == true && resume == true && ended == false) {
            /*
            �����̴� ������ �߰���:
            hasStarted�� true�鼭: ������ ���������鼭
            resume�� true�鼭: pause���°� �ƴϸ鼭
            ended�� false�� ��: ������ ������ ���߰�. ended������ ������ �� �ּ����� ���ߵ�
            ������ ������ �� ���ڱ� �� �ִ� ��ü���� �����. �� �׷������� ��
            */
            for (int i = 0; i < rocks.size(); i++) { //rock�� ���
                float rockChaseMagnitude = sqrt(rocks[i].nearest(scissorss).x * rocks[i].nearest(scissorss).x + rocks[i].nearest(scissorss).y * rocks[i].nearest(scissorss).y);
                //���� ����� �������� �Ÿ�: �Ѿư��� ��
                float rockAvoidMagnitude = sqrt(rocks[i].nearest(papers).x * rocks[i].nearest(papers).x + rocks[i].nearest(papers).y * rocks[i].nearest(papers).y);
                //���� ����� ���ڱ���� �Ÿ�: ���ؾ� ��

                Vector2f rockChaseVelocity = Vector2f(rocks[i].nearest(scissorss).x / rockChaseMagnitude, rocks[i].nearest(scissorss).y / rockChaseMagnitude);
                //���� ����� �������� ��ġ ���̸� �������� ���� �ӵ� ���͸� ����
                Vector2f rockAvoidVelocity = Vector2f(-rocks[i].nearest(papers).x / rockAvoidMagnitude, -rocks[i].nearest(papers).y / rockAvoidMagnitude);
                //���� ����� ���ڱ���� ��ġ ���̸� �������� ���� �ӵ� ���͸� ����

                Vector2f rockVelocity = (rockChaseMagnitude >= rockAvoidMagnitude ? rockAvoidVelocity : rockChaseVelocity);
                //�� �߿� � ���͸� �� ���ΰ�: ���� ����� ���ڱ�� ���� ����� ������ �Ÿ��� ����
                //�� �� ���ڱⰡ ������ �ϸ� ���ؾ� �ϰ�, �� �� ������ ������ �ϸ� �Ѿƾ� �ϰ�
                //�����, ������ ������ ������ �Ѵ� ���͸� ����, ���ڱ�� ������ ���ڱ⸦ ���ϴ� ���͸� ����
                if (rockChaseMagnitude == 0) rockVelocity = rockAvoidVelocity;
                if (rockAvoidMagnitude == 0) rockVelocity = rockChaseVelocity;
                //�ٵ� ������ ��ü�� �׾���: rockChaseMagnitude�� 0�� �Ź����� ���� ���� �����ϴ� rockVelocity�� 0�� �ź��� ����� ������ �� ������
                //�׷��� ��� �� ���� 0�� �Ź����� ������ ���� ������ ��.

                rocks[i].move(rockVelocity, window);
            }

            for (int i = 0; i < scissorss.size(); i++) {
                float scissorsChaseMagnitude = sqrt(scissorss[i].nearest(papers).x * scissorss[i].nearest(papers).x + scissorss[i].nearest(papers).y * scissorss[i].nearest(papers).y);
                //���� ����� ���ڱ���� �Ÿ�: �Ѿƾ� ��
                float scissorsAvoidMagnitude = sqrt(scissorss[i].nearest(rocks).x * scissorss[i].nearest(rocks).x + scissorss[i].nearest(rocks).y * scissorss[i].nearest(rocks).y);
                //���� ����� �������� �Ÿ�

                Vector2f scissorsChaseVelocity = Vector2f(scissorss[i].nearest(papers).x / scissorsChaseMagnitude, scissorss[i].nearest(papers).y / scissorsChaseMagnitude);
                //���ڱ⸦ �Ѵ� �ӵ� ����
                Vector2f scissorsAvoidVelocity = Vector2f(-scissorss[i].nearest(rocks).x / scissorsAvoidMagnitude, -scissorss[i].nearest(rocks).y / scissorsAvoidMagnitude);
                //������ ���ϴ� �ӵ� ����


                Vector2f scissorsVelocity = (scissorsChaseMagnitude >= scissorsAvoidMagnitude ? scissorsAvoidVelocity : scissorsChaseVelocity);
                //���� �� ���� ũ���� �Ÿ��� ���� ���͸� ����
                if (scissorsChaseMagnitude == 0) scissorsVelocity = scissorsAvoidVelocity;
                if (scissorsAvoidMagnitude == 0) scissorsVelocity = scissorsChaseVelocity;
                //0�̸� �ٸ� �� ����
                scissorss[i].move(scissorsVelocity, window);
            }

            for (int i = 0; i < papers.size(); i++) {
                float paperChaseMagnitude = sqrt(papers[i].nearest(rocks).x * papers[i].nearest(rocks).x + papers[i].nearest(rocks).y * papers[i].nearest(rocks).y);
                //���� ����� �������� �Ÿ�
                float paperAvoidMagnitude = sqrt(papers[i].nearest(scissorss).x * papers[i].nearest(scissorss).x + papers[i].nearest(scissorss).y * papers[i].nearest(scissorss).y);
                //���� ����� �������� �Ÿ�

                Vector2f paperChaseVelocity = Vector2f(papers[i].nearest(rocks).x / paperChaseMagnitude, papers[i].nearest(rocks).y / paperChaseMagnitude);
                //���� ����� ������ �Ѵ� ����
                Vector2f paperAvoidVelocity = Vector2f(-papers[i].nearest(scissorss).x / paperAvoidMagnitude, -papers[i].nearest(scissorss).y / paperAvoidMagnitude);
                //���� ����� ������ ���ϴ� ����

                Vector2f paperVelocity = (paperChaseMagnitude >= paperAvoidMagnitude ? paperAvoidVelocity : paperChaseVelocity);
                //�� ���� �� �� ����� ���� ���͸� ����
                if (paperChaseMagnitude == 0) paperVelocity = paperAvoidVelocity;
                if (paperAvoidMagnitude == 0) paperVelocity = paperChaseVelocity;
                //0�̸� �ٸ� �� ����

                papers[i].move(paperVelocity, window);
            }
            
          

            for (int i = 0; i < papers.size(); i++) { //������ ���ڱ⸦ ������ ��
                for (int j = 0; j < rocks.size(); j++) {
                    if (rocks[j].hitby(papers[i])) {
                        int k = j;
                        
                        Vector2f originalPosition = Vector2f(rocks[j].getSprite().getPosition().x, rocks[j].getSprite().getPosition().y);
                        //���� ��ġ ����
                        
                        rocks.erase(rocks.begin() + j);
                        //�� ������ �����
                        Paper newPaper = Paper(originalPosition, paperTexture);
                        //�� ���� �� �ڸ��� �����: ������ �����ڸ��� �ٸ� ������ �̵��ϴ� ������ �߻�
                        papers.push_back(newPaper); 
                        //�� ���� �߰�
                        papers.back().setPosition(originalPosition);
                        //������ ���ߵ� �ڸ��� ������µ� �ٷ� �ٸ� ������ ������ ���淡 ��� �߰��� ���� ��ġ�� �ٽ� ����
                        break;

                    }
                    

                }
               
            }
            for (int i = 0; i < rocks.size(); i++) { //������ ������ ������ ��
                for (int j = 0; j < scissorss.size(); j++) {
                    if (scissorss[j].hitby(rocks[i])) {
                        int k = j;

                        Vector2f originalPosition = Vector2f(scissorss[j].getSprite().getPosition().x, scissorss[j].getSprite().getPosition().y);
                       

                        scissorss.erase(scissorss.begin() + j);

                        Rock newRock = Rock(originalPosition,rockTexture);

                        rocks.push_back(newRock);
                        rocks.back().setPosition(originalPosition);
                        
                        break;

                    }


                }

            }
            for (int i = 0; i < scissorss.size(); i++) { //������ ���ڱⰡ ��������
                for (int j = 0; j < papers.size(); j++) {
                    if (papers[j].hitby(scissorss[i])) {
                        int k = j;

                        Vector2f originalPosition = Vector2f(papers[j].getSprite().getPosition().x, papers[j].getSprite().getPosition().y);
                        

                        papers.erase(papers.begin() + j);

                        Scissors newScissors = Scissors(originalPosition,scissorsTexture);

                        scissorss.push_back(newScissors);
                        scissorss.back().setPosition(originalPosition);
                       
                        break;

                    }


                }

            }
       

        }

       
        
        textRock.setString("Rocks: " + to_string(slider1.getOffset()));
        textSci.setString("Scissors: " + to_string(slider2.getOffset()));
        textPap.setString("Papers: " + to_string(slider3.getOffset()));

 
        
        

        // ȭ�� û��
        window.clear();

        // ���� �����ϰ� ���� �����̴� ���ֱ�
        if (hasStarted == false) {
            slider1.draw(window);
            slider2.draw(window);
            slider3.draw(window);


            window.draw(textRock);
            window.draw(textSci);
            window.draw(textPap);
            
        }



        //����,����,�� ��� �ϳ��� �߰��ؾ� ���� ��ŸƮ �� �� ����
        if (rocks.size() + scissorss.size() + papers.size() >= 1) {
            myButton.draw(window);
            window.draw(textButton);
            myButton.handleEvent(event, window, hasStarted, reset, resume, textButton);
            //��ư �̺�Ʈ �ڵ鸵�� ����� �ű�. ��ư�� ��� ��ư�� �ִ� �ڸ��� ������ ��ư�� �۵��ϴ� ������ �߻��ؼ�
        }



        //���� ��ü�� �� ������ ������
        if (rocks.size() + scissorss.size() + papers.size() == rocks.size()&&hasStarted==true ||
            rocks.size() + scissorss.size() + papers.size() == scissorss.size()&&hasStarted == true ||
            rocks.size() + scissorss.size() + papers.size() == papers.size()&&hasStarted == true) {
            ended = true;
            if (rocks.size() + scissorss.size() + papers.size() == rocks.size() && hasStarted == true) {//�װ� ������
                result.setString("Rock wins!");
            }
            if (rocks.size() + scissorss.size() + papers.size() == scissorss.size() && hasStarted == true) {//������
                result.setString("Scissors wins!");
            }           
            if (rocks.size() + scissorss.size() + papers.size() == papers.size() && hasStarted == true) {//����
                result.setString("Paper wins!"); //���� ��� ��� �غ�
            }

            window.draw(result); //��� ���
            textButton.setString("Restart");        //��ư�� �ؽ�Ʈ�� restart�� ����
            textButton.setPosition(buttonPos.x + 25, buttonPos.y+8);

        }

        //�������� ��, �ٽ� ������ �� �ʱ�ȭ
        if (reset == true) {
            scissorss.clear();
            rocks.clear();
            papers.clear();
            
            slider1.resetSlider();
            slider2.resetSlider();
            slider3.resetSlider();

            reset = false;
            ended = false; //ended�� false�� �ʱ�ȭ
        }

        
        for (int i = 0; i < rocks.size(); i++) {
            rocks[i].draw(window);
        }
        for (int i = 0; i < scissorss.size(); i++) {
            scissorss[i].draw(window);
        }
        for (int i = 0; i < papers.size(); i++) {
            papers[i].draw(window);
        }


      
        // ����
        window.display();
    }
}