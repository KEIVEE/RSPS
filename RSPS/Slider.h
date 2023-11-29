#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class Slider {
	RectangleShape sliderBar;
	RectangleShape floatingBar;
	bool isDragging;
	float offsetX;

public:
	Slider(Vector2f position);

	void handleEvent(Event event, RenderWindow& window);

	void draw(RenderWindow& window);
};