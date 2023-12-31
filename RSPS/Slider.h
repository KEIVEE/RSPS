#include <SFML/Graphics.hpp>
#include "RSP.h"
#include "Rock.h"

using namespace std;
using namespace sf;


class Slider {
	RectangleShape sliderBar;
	RectangleShape floatingBar;
	bool isDragging;
	int offsetX;

public:
	Slider(Vector2f& position);

	void handleEvent(Event event, RenderWindow& window);

	void draw(RenderWindow& window);

	int getOffset();

	void resetSlider();
};