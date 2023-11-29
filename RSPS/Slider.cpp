#include "Slider.h"

Slider::Slider( Vector2f position) {
    sliderBar.setSize(Vector2f(300.f, 30.f));
    floatingBar.setSize(Vector2f(30.f, 30.f));
    sliderBar.setPosition(position);
    floatingBar.setPosition(position);
    sliderBar.setFillColor(Color::White);
    floatingBar.setFillColor(Color::Blue);

    isDragging = false;
    offsetX = 0.0f;
}


void Slider::handleEvent(Event event, RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {
            if (floatingBar.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                isDragging = true;
                offsetX = event.mouseButton.x - floatingBar.getPosition().x;
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
        }
    }
}

void Slider::draw(RenderWindow& window) {
    window.draw(sliderBar);
    window.draw(floatingBar);
}