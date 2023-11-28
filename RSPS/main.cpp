#include <string>
#include <exception>
#include <vector>
#include "RSP.h"
#include "Rock.h"
#include "Slider.h"

int main(void)
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

    sf::VideoMode fullScreenMode = modes[0];

    sf::RenderWindow window(fullScreenMode, "RSPS", sf::Style::Fullscreen);

    Rock rock;
    

    Vector2f leftSpeed = Vector2f(-0.1f, 0.f);
    Vector2f rightSpeed = Vector2f(0.1f, 0.f);
    Vector2f upSpeed = Vector2f(0.f, -0.1f);
    Vector2f downSpeed = Vector2f(0.f, 0.1f);
    
    
    
    Vector2f sliderPos = Vector2f(50.f, 20.f);
    Slider slider1(30.f, 3.f, sliderPos);


    // 윈도우 루프 시작
    while (window.isOpen())
    {
        Event event;

        // 종료 여부 체크
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

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

        slider1.handleEvent(event, window);
        // 화면 청소
        window.clear();

        // 화면에 글씨 쓰기
        rock.draw(window);
        slider1.draw(window);

        // 띄우기
        window.display();
    }
}
