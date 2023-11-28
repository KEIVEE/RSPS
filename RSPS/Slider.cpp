#include "Slider.h"

Slider::Slider(float width, float height, Vector2f position) {
    sliderBar.setSize(Vector2f(width, height));
    sliderBar.setPosition(position);
    sliderBar.setFillColor(Color::Blue);

    isDragging = false;
    offsetX = 0.0f;
}


void Slider::handleEvent(Event event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {
            if (sliderBar.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                isDragging = true;
                offsetX = event.mouseButton.x - sliderBar.getPosition().x;
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
            float x = event.mouseMove.x - offsetX;
            if (x >= 0 && x <= window.getSize().x - sliderBar.getSize().x) {
                sliderBar.setPosition(x, sliderBar.getPosition().y);
            }
        }
    }
}

void Slider::draw(RenderWindow& window) {
    window.draw(sliderBar);
}