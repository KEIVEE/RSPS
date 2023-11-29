#include "Slider.h"
#include <iostream>

Slider::Slider(Vector2f& position) {
    sliderBar.setSize(Vector2f(300.f, 15.f));
    floatingBar.setSize(Vector2f(30.f, 30.f));
    sliderBar.setPosition(position);
    floatingBar.setPosition(Vector2f(position.x, position.y - 7.5f));
    sliderBar.setFillColor(Color::White);
    floatingBar.setFillColor(Color::Blue);

    isDragging = false;
    offsetX = 0;
}


void Slider::handleEvent(Event event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {
            if (floatingBar.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                isDragging = true;
                
                
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == Mouse::Left) {
            isDragging = false;
        }
    }
    else if (event.type == Event::MouseMoved) {
        if (isDragging) {
            float x = event.mouseMove.x;
            if (x >= sliderBar.getPosition().x && x <= sliderBar.getPosition().x + sliderBar.getSize().x - floatingBar.getSize().x) {
                floatingBar.setPosition(x, floatingBar.getPosition().y);
            }
            offsetX = (((int)floatingBar.getPosition().x - (int)sliderBar.getPosition().x) / 3);
            cout << offsetX << endl;
        }
    }
}

void Slider::draw(RenderWindow& window) {
    window.draw(sliderBar);
    window.draw(floatingBar);
}

int Slider::getOffset() {
    return offsetX;
}
