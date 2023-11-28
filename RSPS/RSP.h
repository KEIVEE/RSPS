#pragma once

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class RSP {
protected:
	float vel_x;
	float vel_y;
private:

public:
	void setVelocity(float, float);
};