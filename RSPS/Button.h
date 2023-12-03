#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Button {
	
private:
	RectangleShape buttonShape;
	Text buttonText;
	bool isButtonPressed;				//버튼 한 번만 처리하기 위해

public:
	Button(Vector2f position, Font& font);
	void handleEvent(Event event, RenderWindow& window, bool& hasStarted);
	void draw(RenderWindow& window);
};