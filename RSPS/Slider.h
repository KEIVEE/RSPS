#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class Slider {
	RectangleShape sliderBar;
	bool isDragging;
	float offsetX;

public:
	Slider(float width, float height, Vector2f position);

	void handleEvent(Event event, RenderWindow& window);

	void draw(RenderWindow& window);
};