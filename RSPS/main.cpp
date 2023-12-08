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
    //1500 * 900 크기 창, 크기 수정 불가, 전체화면 불가
    
    Vector2f sliderRockPos = Vector2f(50.f, 20.f); //바위슬라이더 위치
    Vector2f sliderSciPos = Vector2f(50.f, 60.f); //가위 슬라이더 위치
    Vector2f sliderPaperPos = Vector2f(50.f, 100.f); //보 슬라이더 위치
    Slider slider1(sliderRockPos); //바위 슬라이더
    Slider slider2(sliderSciPos); //가위 슬라이더
    Slider slider3(sliderPaperPos); //보 슬라이더

    Font font;
    if (!font.loadFromFile("Maplestory Light.ttf")) { //글씨체
        throw exception("font error");
    }

    Text textRock; //rock 개수 text
    textRock.setFont(font);
    textRock.setFillColor(Color::White);
    textRock.setCharacterSize(24);
    textRock.setPosition(380.f, 20.f);



    Text textSci; //scissors 개수 text
    textSci.setFont(font);
    textSci.setFillColor(Color::White);
    textSci.setCharacterSize(24);
    textSci.setPosition(380.f, 60.f);



    Text textPap; //paper 개수 text
    textPap.setFont(font);
    textPap.setFillColor(Color::White);
    textPap.setCharacterSize(24);
    textPap.setPosition(380.f, 100.f);


    Text result; //누가 이겼는지 알려주는 텍스트
    result.setFont(font);
    result.setFillColor(Color::White);
    result.setCharacterSize(80);
    result.setPosition(700.f, 420.f);

     
    // 버튼 객체 생성
  
    Vector2f buttonPos = Vector2f(1200.f, 50.f); //위치
    Text textButton; //글자
    textButton.setFont(font);
    textButton.setString("Start");
    Button myButton(buttonPos,textButton);


    Rock rock; //copy constructor를 쓰기 위한 원본. copy constructor을 써야 텍스처가 깨지지 않았음
    Scissors scissors;
    Paper paper;


    Texture rockTexture;
    if (!rockTexture.loadFromFile("rock.png")) {
        // 텍스처 로드 실패 처리
        return EXIT_FAILURE;
    }
    Texture scissorsTexture;
    if (!scissorsTexture.loadFromFile("scissors.png")) {
        // 텍스처 로드 실패 처리
        return EXIT_FAILURE;
    }
    Texture paperTexture;
    if (!paperTexture.loadFromFile("paper.png")) {
        // 텍스처 로드 실패 처리
        return EXIT_FAILURE;
    }

    vector<Rock> rocks(270); //rock이 최대한 가질 수 있는 크기는 270
    /*
    처음에는 재배치 문제가 있었음
    재배치 문제가 뭐냐
    Rock 슬라이더를 올려 주면 10개, 20개 쯤에서 완전히 새로운 랜덤 위치로 모든 rock이 이동하는 현상
    이 현상을 이걸로 해결했는데, 실험해 보니 지금은 270이라는 제약을 두지 않아도 재배치가 발생하지 않으나
    그냥 둠
    */
    vector<Scissors> scissorss(270);
    vector<Paper> papers(270);

    bool hasStarted = false; //게임을 시작했냐? 스타트 버튼을 누르면 hasstarted가 true가 될 것이다. 슬라이더는 이게 false일 때만 나타나고, true면 숨길 것
    bool reset = false; //리셋을 할 것인가?
    bool resume = false; //게임이 진행 중인가?: hasStarted와는 다른 개념이다. Pause버튼을 누를 때를 위한 변수라고 보면 된다.
    /*
    pause일 때 hasStarted를 false로 맞춰버리면 슬라이더가 나타나버리고 그에 따라 부족한 객체는 채워지고 넘는 객체는 줄어버리는 현상 발생
    그래서 pause를 없앨까 했지만 pause를 살려두고 진짜로 멈췄다가 시작하는 것을 구현
    hasStarted를 true로 둬서 슬라이더가 나타나지 않게 하면서도 객체가 움직이지 않아야 하므로 이 변수를 추가
    */
    bool ended = false; //게임이 끝났냐?
    /*
    게임이 끝났을 때 모든 객체가 화면에서 사라지는 현상이 발생
    왜 그러는지는 아직도 모르겠지만, 게임이 끝났다는 변수를 추가하고
    게임이 끝났다면 객체를 움직이지 않게 함으로써 문제 해결
    */
    
    
    
    // 윈도우 루프 시작
    while (window.isOpen())
    {
        sf::Event event;

        // 종료 여부 체크
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        

        if (hasStarted == false) {
            /*
            핸들 이벤트 함수의 위치를 변경:
            핸들이벤트가 항상 돌아간다면 슬라이더가 그 자리에 없음에도 클릭 드래그 시 변화가 생기는 현상이 발생
            그래서 이벤트 핸들링을 조건 안에 실행하도록 함
            이걸 누가 알까 싶지만 그래도 고치고 싶잖아
            */
            slider1.handleEvent(event, window);
            slider2.handleEvent(event, window);
            slider3.handleEvent(event, window);
                if (rocks.size() < slider1.getOffset()) {
                    while (rocks.size() < slider1.getOffset()) {
                        Rock newRock = Rock(rock, rockTexture);
                        
                        rocks.push_back(newRock); // 새로운 Rock 객체 추가
                    }
                }
                else if (rocks.size() > slider1.getOffset()) {
                    rocks.resize(slider1.getOffset()); // Rock 개수 줄이기
                }
                if (scissorss.size() < slider2.getOffset()) {
                    while (scissorss.size() < slider2.getOffset()) {
                        Scissors newScissors = Scissors(scissors,scissorsTexture);
                        scissorss.push_back(newScissors); // 새로운 scissors 객체 추가  
                    }
                }
                else if (scissorss.size() > slider2.getOffset()) {
                    scissorss.resize(slider2.getOffset()); // scissors 개수 줄이기
                }
                if (papers.size() < slider3.getOffset()) {
                    while (papers.size() < slider3.getOffset()) {
                        Paper newPaper = Paper(paper,paperTexture);
                        papers.push_back(newPaper); // 새로운 paper 객체 추가
                    }
                }
                else if (papers.size() > slider3.getOffset()) {
                    papers.resize(slider3.getOffset()); // paper 개수 줄이기
            }
                
        }

        
        if (hasStarted == true && resume == true && ended == false) {
            /*
            움직이는 조건이 추가됨:
            hasStarted가 true면서: 게임을 시작했으면서
            resume가 true면서: pause상태가 아니면서
            ended가 false일 떄: 게임이 끝나면 멈추게. ended조건이 없으면 위 주석에서 말했듯
            게임이 끝났을 때 갑자기 잘 있던 객체들이 사라짐. 왜 그러는지는 모름
            */
            for (int i = 0; i < rocks.size(); i++) { //rock의 경우
                float rockChaseMagnitude = sqrt(rocks[i].nearest(scissorss).x * rocks[i].nearest(scissorss).x + rocks[i].nearest(scissorss).y * rocks[i].nearest(scissorss).y);
                //가장 가까운 가위와의 거리: 쫓아가야 함
                float rockAvoidMagnitude = sqrt(rocks[i].nearest(papers).x * rocks[i].nearest(papers).x + rocks[i].nearest(papers).y * rocks[i].nearest(papers).y);
                //가장 가까운 보자기와의 거리: 피해야 함

                Vector2f rockChaseVelocity = Vector2f(rocks[i].nearest(scissorss).x / rockChaseMagnitude, rocks[i].nearest(scissorss).y / rockChaseMagnitude);
                //가장 가까운 가위와의 위치 차이를 바탕으로 단위 속도 벡터를 생성
                Vector2f rockAvoidVelocity = Vector2f(-rocks[i].nearest(papers).x / rockAvoidMagnitude, -rocks[i].nearest(papers).y / rockAvoidMagnitude);
                //가장 가까운 보자기와의 위치 차이를 바탕으로 단위 속도 벡터를 생성

                Vector2f rockVelocity = (rockChaseMagnitude >= rockAvoidMagnitude ? rockAvoidVelocity : rockChaseVelocity);
                //둘 중에 어떤 벡터를 쓸 것인가: 가장 가까운 보자기와 가장 가까운 가위의 거리를 생각
                //그 중 보자기가 가깝다 하면 피해야 하고, 그 중 가위가 가깝다 하면 쫓아야 하고
                //결론은, 가위랑 가까우면 가위를 쫓는 벡터를 선택, 보자기랑 가까우면 보자기를 피하는 벡터를 선택
                if (rockChaseMagnitude == 0) rockVelocity = rockAvoidVelocity;
                if (rockAvoidMagnitude == 0) rockVelocity = rockChaseVelocity;
                //근데 가위가 전체가 죽었다: rockChaseMagnitude가 0이 돼버려서 작은 수를 선택하는 rockVelocity가 0이 돼벼려 얘들이 정신을 못 차린다
                //그래서 어느 한 수가 0이 돼버리면 나머지 값을 갖도록 함.

                rocks[i].move(rockVelocity, window);
            }

            for (int i = 0; i < scissorss.size(); i++) {
                float scissorsChaseMagnitude = sqrt(scissorss[i].nearest(papers).x * scissorss[i].nearest(papers).x + scissorss[i].nearest(papers).y * scissorss[i].nearest(papers).y);
                //가장 가까운 보자기와의 거리: 쫓아야 함
                float scissorsAvoidMagnitude = sqrt(scissorss[i].nearest(rocks).x * scissorss[i].nearest(rocks).x + scissorss[i].nearest(rocks).y * scissorss[i].nearest(rocks).y);
                //가장 가까운 바위와의 거리

                Vector2f scissorsChaseVelocity = Vector2f(scissorss[i].nearest(papers).x / scissorsChaseMagnitude, scissorss[i].nearest(papers).y / scissorsChaseMagnitude);
                //보자기를 쫓는 속도 벡터
                Vector2f scissorsAvoidVelocity = Vector2f(-scissorss[i].nearest(rocks).x / scissorsAvoidMagnitude, -scissorss[i].nearest(rocks).y / scissorsAvoidMagnitude);
                //바위를 피하는 속도 벡터


                Vector2f scissorsVelocity = (scissorsChaseMagnitude >= scissorsAvoidMagnitude ? scissorsAvoidVelocity : scissorsChaseVelocity);
                //벡터 중 작은 크기의 거리를 가진 벡터를 선택
                if (scissorsChaseMagnitude == 0) scissorsVelocity = scissorsAvoidVelocity;
                if (scissorsAvoidMagnitude == 0) scissorsVelocity = scissorsChaseVelocity;
                //0이면 다른 값 선택
                scissorss[i].move(scissorsVelocity, window);
            }

            for (int i = 0; i < papers.size(); i++) {
                float paperChaseMagnitude = sqrt(papers[i].nearest(rocks).x * papers[i].nearest(rocks).x + papers[i].nearest(rocks).y * papers[i].nearest(rocks).y);
                //가장 가까운 바위와의 거리
                float paperAvoidMagnitude = sqrt(papers[i].nearest(scissorss).x * papers[i].nearest(scissorss).x + papers[i].nearest(scissorss).y * papers[i].nearest(scissorss).y);
                //가장 가까운 가위와의 거리

                Vector2f paperChaseVelocity = Vector2f(papers[i].nearest(rocks).x / paperChaseMagnitude, papers[i].nearest(rocks).y / paperChaseMagnitude);
                //가장 가까운 바위를 쫓는 벡터
                Vector2f paperAvoidVelocity = Vector2f(-papers[i].nearest(scissorss).x / paperAvoidMagnitude, -papers[i].nearest(scissorss).y / paperAvoidMagnitude);
                //가장 가까운 가위를 피하는 벡터

                Vector2f paperVelocity = (paperChaseMagnitude >= paperAvoidMagnitude ? paperAvoidVelocity : paperChaseVelocity);
                //두 벡터 중 더 가까운 놈의 벡터를 선택
                if (paperChaseMagnitude == 0) paperVelocity = paperAvoidVelocity;
                if (paperAvoidMagnitude == 0) paperVelocity = paperChaseVelocity;
                //0이면 다른 값 선택

                papers[i].move(paperVelocity, window);
            }
            
          

            for (int i = 0; i < papers.size(); i++) { //바위가 보자기를 만났을 때
                for (int j = 0; j < rocks.size(); j++) {
                    if (rocks[j].hitby(papers[i])) {
                        int k = j;
                        
                        Vector2f originalPosition = Vector2f(rocks[j].getSprite().getPosition().x, rocks[j].getSprite().getPosition().y);
                        //원래 위치 저장
                        
                        rocks.erase(rocks.begin() + j);
                        //그 바위를 지우고
                        Paper newPaper = Paper(originalPosition, paperTexture);
                        //새 보를 그 자리에 만들기: 하지만 만들자마자 다른 곳으로 이동하는 현상이 발생
                        papers.push_back(newPaper); 
                        //새 보를 추가
                        papers.back().setPosition(originalPosition);
                        //위에서 말했듯 자리를 정해줬는데 바로 다른 랜덤한 곳으로 가길래 방금 추가한 보의 위치를 다시 지정
                        break;

                    }
                    

                }
               
            }
            for (int i = 0; i < rocks.size(); i++) { //바위가 가위를 만났을 때
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
            for (int i = 0; i < scissorss.size(); i++) { //가위와 보자기가 만났을때
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

 
        
        

        // 화면 청소
        window.clear();

        // 게임 시작하고 나면 슬라이더 없애기
        if (hasStarted == false) {
            slider1.draw(window);
            slider2.draw(window);
            slider3.draw(window);


            window.draw(textRock);
            window.draw(textSci);
            window.draw(textPap);
            
        }



        //가위,바위,보 어느 하나라도 추가해야 게임 스타트 할 수 있음
        if (rocks.size() + scissorss.size() + papers.size() >= 1) {
            myButton.draw(window);
            window.draw(textButton);
            myButton.handleEvent(event, window, hasStarted, reset, resume, textButton);
            //버튼 이벤트 핸들링도 여기로 옮김. 버튼이 없어도 버튼이 있던 자리를 누르면 버튼이 작동하는 현상이 발생해서
        }



        //만약 개체가 한 종류만 남으면
        if (rocks.size() + scissorss.size() + papers.size() == rocks.size()&&hasStarted==true ||
            rocks.size() + scissorss.size() + papers.size() == scissorss.size()&&hasStarted == true ||
            rocks.size() + scissorss.size() + papers.size() == papers.size()&&hasStarted == true) {
            ended = true;
            if (rocks.size() + scissorss.size() + papers.size() == rocks.size() && hasStarted == true) {//그게 바위다
                result.setString("Rock wins!");
            }
            if (rocks.size() + scissorss.size() + papers.size() == scissorss.size() && hasStarted == true) {//가위다
                result.setString("Scissors wins!");
            }           
            if (rocks.size() + scissorss.size() + papers.size() == papers.size() && hasStarted == true) {//보다
                result.setString("Paper wins!"); //게임 결과 출력 준비
            }

            window.draw(result); //결과 출력
            textButton.setString("Restart");        //버튼의 텍스트를 restart로 변경
            textButton.setPosition(buttonPos.x + 25, buttonPos.y+8);

        }

        //게임종료 후, 다시 시작할 때 초기화
        if (reset == true) {
            scissorss.clear();
            rocks.clear();
            papers.clear();
            
            slider1.resetSlider();
            slider2.resetSlider();
            slider3.resetSlider();

            reset = false;
            ended = false; //ended도 false로 초기화
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


      
        // 띄우기
        window.display();
    }
}