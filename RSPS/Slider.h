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
	int storedValue = 0;
public:
	Slider(Vector2f& position);

	void handleEvent(Event event, RenderWindow& window);

	void draw(RenderWindow& window);

	int getOffset();

	int getstoredValue();

	void setstoredValue(int x);
};