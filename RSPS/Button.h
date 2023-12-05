#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Button {
	
private:
	RectangleShape buttonShape;
	bool isButtonPressed;				//버튼 한 번만 처리하기 위해

public:
	Button(Vector2f position, Text& text);
	void handleEvent(Event event, RenderWindow& window, bool& hasStarted, bool&reset, Text& text);
	void draw(RenderWindow& window);
};