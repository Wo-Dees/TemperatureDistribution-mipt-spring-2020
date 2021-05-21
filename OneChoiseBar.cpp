//
// Created by evgen on 18.05.2021.
//

#include "OneChoiseBar.h"
bool OneChoiseBar::is_anyone_active = false;
OneChoiseBar::OneChoiseBar(int x, int y, int dr, int radius, sf::Color back_color, sf::Color main_color) {
    this->back_color = back_color;
    this->main_color = main_color;
    this->radius = radius;

    this->x = x;
    this->y = y;

    this->ext_circle.setRadius((float)radius - 0);
    this->ext_circle.setFillColor(back_color);
    this->ext_circle.setOutlineThickness(1);
    this->ext_circle.setOutlineColor(sf::Color::Black);
    this->ext_circle.setOrigin(this->radius, this->radius);
    this->ext_circle.setPosition(x, y);

    this->int_circle.setRadius((float)radius - dr);
    this->int_circle.setFillColor(main_color);
    this->int_circle.setOrigin(this->radius - dr, this->radius - dr);
    this->int_circle.setPosition(x, y);

    this->value = false;
}

void OneChoiseBar::display(sf::RenderWindow &window) {
    if (is_anyone_active && !this->value)
        this->ext_circle.setFillColor(sf::Color(128, 128, 128));
    else
        this->ext_circle.setFillColor(this->back_color);
    window.draw(this->ext_circle);
    if (this->value)
        window.draw(this->int_circle);
}

void OneChoiseBar::event_holder(sf::Event& event) {
    if (!is_anyone_active || (is_anyone_active && this->value)) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (this->is_in(event.mouseButton.x, event.mouseButton.y))
                    this->value = not this->value;
                if (this->value)
                    is_anyone_active = true;
                else
                    is_anyone_active = false;
            }
        }
    }
}

bool OneChoiseBar::is_in(int x, int y) {
    if (x < this->x + this->radius/1.41 && x > this->x - this->radius/1.41 &&
    y < this->y + this->radius/1.41 && y > this->y - this->radius/1.41)
        return true;
    return false;
}

bool OneChoiseBar::return_value() {
    return this->value;
}

