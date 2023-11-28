#include <string>
#include <exception>
#include <vector>
#include "RSP.h"
#include "Rock.h"

int main(void)
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

    sf::VideoMode fullScreenMode = modes[0];

    sf::RenderWindow window(fullScreenMode, "RSPS", sf::Style::Fullscreen);

    Rock rock;
    

    float speed = 0.1f;

    // ������ ���� ����
    while (window.isOpen())
    {
        sf::Event event;

        // ���� ���� üũ
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rock.getSprite().getPosition().x > 0) {
            rock.move(-speed, 0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rock.getSprite().getPosition().x < window.getSize().x - rock.getSprite().getGlobalBounds().width) {
            rock.move(speed, 0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rock.getSprite().getPosition().y > 0) {
            rock.move(0.f, -speed);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rock.getSprite().getPosition().y < window.getSize().y - rock.getSprite().getGlobalBounds().height) {
            rock.move(0.f, speed);
        }

        // ȭ�� û��
        window.clear();

        // ȭ�鿡 �۾� ����
        window.draw(rock.getSprite());
        

        // ����
        window.display();
    }
}
