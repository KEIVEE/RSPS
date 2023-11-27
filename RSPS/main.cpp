#include <SFML/Graphics.hpp>
#include <string>
#include <exception>

int main(void)
{
    // main window 생성
    sf::RenderWindow window(sf::VideoMode(400, 300), "SFML window");

    // 쓸 폰트 생성
    sf::Font font;
    if (!font.loadFromFile(R"(C:\Windows\Fonts\a옛날목욕탕M.ttf)"))
        throw std::exception("font error");

    // 화면에 쓸 내용
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Green); //글씨 색깔

    // 윈도우 루프 시작
    while (window.isOpen())
    {
        sf::Event event;

        // 종료 여부 체크
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // 화면 청소
        window.clear();

        // 화면에 글씨 쓰기
        window.draw(text);

        // 띄우기
        window.display();
    }
}
