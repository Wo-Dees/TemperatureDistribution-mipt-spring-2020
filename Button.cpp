//
// Created by evgen on 18.05.2021.
//

#include "Button.h"
#include <iostream>


ShapeOfBbox::ShapeOfBbox(int x, int y, int length, int width) {
    this->x = x;
    this->y = y;
    this->length = length;
    this->width = width;
    this->center_x = int(x + (this->length) / 2);
    this->center_y = int(y + (this->width) / 2);

    this->set_current_parametres();
}

void ShapeOfBbox::set_current_parametres() {
    this->center_x = int((this->length) / 2);
    this->center_y = int((this->width) / 2);

    this->left_corner_x = x - this->center_x;
    this->left_corner_y = y - this->center_y;
    this->mouse_x_min = this->left_corner_x;
    this->mouse_x_max = this->left_corner_x + this->length;
    this->mouse_y_min = this->left_corner_y;
    this->mouse_y_max = this->left_corner_y + this->width;
}

bool ShapeOfBbox::is_in(int x_, int y_) const {
    if (x_ <= this->mouse_x_max && x_ >= this->mouse_x_min && y_ <= this->mouse_y_max && y_ >= this->mouse_y_min)
        return true;
    return false;
}

Button::Button(std::string name, int x, int y, int length, int width, const sf::Texture &texture, const sf::Font &font,
               std::string text, sf::Color first_color, sf::Color second_color, const sf::RenderWindow &window,
               const bool &synchronized_value) :
        Shape(x, y, length, width), synchronized_value(const_cast<bool &>(synchronized_value)),
        window(const_cast<sf::RenderWindow &>(window)) {
    this->name = std::move(name);

    this->box.setTexture(texture);
    this->box.setOrigin((float) (this->Shape.x - this->Shape.left_corner_x),
                        (float) (this->Shape.y - this->Shape.left_corner_y));

    this->box.setPosition((float) this->Shape.x, (float) this->Shape.y);

    this->first_color = first_color;
    this->second_color = second_color;
    this->txt.setString(text);
    this->txt.setFont(font);
    this->txt.setCharacterSize(35);
    auto l = this->txt.getGlobalBounds().height;
    auto f = this->txt.getGlobalBounds().width;
    this->txt.setOrigin(f / 1.85, l /1.15);

    this->txt.setPosition((float) Shape.x, (float) Shape.y);
    this->txt.setFillColor(first_color);
    this->txt.setStyle(sf::Text::Bold);
}

Button::Button(std::string name, int x, int y, const sf::Font &font, std::string text,
               sf::Color first_color, sf::Color second_color, const sf::RenderWindow &window, const bool &synchronized_value) :
        synchronized_value(const_cast<bool &>(synchronized_value)), window(const_cast<sf::RenderWindow &>(window)),
        Shape(x, y)
{
    this->name = std::move(name);

    this->first_color = first_color;
    this->second_color = second_color;

    this->first_color = first_color;
    this->second_color = second_color;
    this->txt.setString(text);
    this->txt.setFont(font);
    this->txt.setCharacterSize(35);

    auto l = this->txt.getGlobalBounds().height;
    auto f = this->txt.getGlobalBounds().width;

    Shape.length = f;
    Shape.width = l;
    Shape.set_current_parametres();

    this->txt.setOrigin(f / 1.85, l /1.15);

    this->txt.setPosition((float) Shape.x, (float) Shape.y);
    this->txt.setFillColor(first_color);
    this->txt.setStyle(sf::Text::Bold);
}

void Button::event_holder(sf::Event &event) {

    auto position = sf::Mouse::getPosition(this->window);
    if (this->Shape.is_in(position.x, position.y)) { this->cursor_in(); }
    else { this->cursor_out(); }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
            if (this->Shape.is_in(event.mouseButton.x, event.mouseButton.y)) {
                this->cursor_in();
                this->change_synchronized_value();
            }
            else {
                this->cursor_out();
            }
        }
    }
}

void Button::cursor_in() {
    this->txt.setFillColor(this->second_color);
    this->box.setColor(sf::Color(240, 240, 240));
}

void Button::cursor_out() {
    this->box.setColor(sf::Color::White);
    this->txt.setFillColor(this->first_color);
}

void Button::display_button(sf::RenderWindow &Window) const {
    Window.draw(this->box);
    Window.draw(this->txt);
}

void Button::change_synchronized_value() {
    this->synchronized_value = not this->synchronized_value;
}
