#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Button {
	
private:
	RectangleShape buttonShape;
	bool isButtonPressed;				//��ư �� ���� ó���ϱ� ����

public:
	Button(Vector2f position, Text& text);
	void handleEvent(Event event, RenderWindow& window, bool& hasStarted, bool&reset, Text& text);
	void draw(RenderWindow& window);
};