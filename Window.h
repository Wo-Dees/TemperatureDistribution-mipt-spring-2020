//
// Created by Карим Вафин on 29.04.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_WINDOW_H
#define TEMPERATURE_DISTRIBUTION_WINDOW_H

#include <SFML/Graphics.hpp>

class Window {
protected:
    sf::Font font;
    std::vector<sf::Text> texts;
    std::vector<sf::RectangleShape> buttons;

public:
    Window();
    virtual ~Window() = default;

    virtual int run(sf::RenderWindow& window) = 0;

    sf::Text& create_text(float x, float y, std::string inf, int size, sf::Color color);

    sf::RectangleShape& create_button(float pos_x, float pos_y, float size_x, float size_y, sf::Color color);

    virtual void process_events(sf::RenderWindow& window){};

    virtual void draw_objects(sf::RenderWindow& window);
};


#endif //TEMPERATURE_DISTRIBUTION_WINDOW_H
