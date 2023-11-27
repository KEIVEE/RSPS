#include <SFML/Graphics.hpp>
#include <string>
#include <exception>
#include <vector>

int main(void)
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

    sf::VideoMode fullScreenMode = modes[0];

    sf::RenderWindow window(fullScreenMode, "RSPS", sf::Style::Fullscreen);

    sf::Texture tGood;

    if (!tGood.loadFromFile("paper.png")) {
        throw std::exception("image error");
    }

    sf::Sprite sGood(tGood);
    sGood.setPosition(200.f, 200.f); // 초기 위치 설정

    float speed = 0.1f;

    // 윈도우 루프 시작
    while (window.isOpen())
    {
        sf::Event event;

        // 종료 여부 체크
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sGood.getPosition().x > 0) {
            sGood.move(-speed, 0);
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

        // 화면 청소
        window.clear();

        // 화면에 글씨 쓰기
        window.draw(sGood);
        

        // 띄우기
        window.display();
    }
}
