#include <SFML/Graphics.hpp>
#include <string>
#include <exception>

int main(void)
{
    // main window ����
    sf::RenderWindow window(sf::VideoMode(400, 300), "SFML window");

    // �� ��Ʈ ����
    sf::Font font;
    if (!font.loadFromFile(R"(C:\Windows\Fonts\a���������M.ttf)"))
        throw std::exception("font error");

    // ȭ�鿡 �� ����
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Green); //�۾� ����

    // ������ ���� ����
    while (window.isOpen())
    {
        sf::Event event;

        // ���� ���� üũ
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // ȭ�� û��
        window.clear();

        // ȭ�鿡 �۾� ����
        window.draw(text);

        // ����
        window.display();
    }
}
