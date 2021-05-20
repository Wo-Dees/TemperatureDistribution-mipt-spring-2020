//
// Created by evgen on 18.05.2021.
//

#ifndef TEXTBAR_BUTTON_H
#define TEXTBAR_BUTTON_H
#include <SFML/Graphics.hpp>

struct ShapeOfBbox
{
    int length; int width;
    int x; int y;
    int left_corner_x; int left_corner_y;
    int mouse_x_min; int mouse_x_max;
    int mouse_y_min; int mouse_y_max;
    int center_x; int center_y;

    ShapeOfBbox(int x = 0, int y = 0, int length = 0, int width = 0);
    bool is_in(int x_, int y_) const;
    void set_current_parametres();
};

class Button {
private:
    sf::RenderWindow& window;
    ShapeOfBbox Shape;
    sf::Text txt;
    sf::Sprite box;
    bool& synchronized_value;
    sf::Color first_color;
    sf::Color second_color;
    std::string name;

    void change_synchronized_value();

    void cursor_in();

    void cursor_out();

public:

    Button(std::string name, int x, int y, int length, int width, const sf::Texture& texture, const sf::Font& font,
           std::string text, sf::Color first_color, sf::Color second_color, const sf::RenderWindow& window, const bool& synchronized_value);

    Button (std::string name, int x, int y, const sf::Font& font, std::string text,
            sf::Color first_color, sf::Color second_color, const sf::RenderWindow& window, const bool& synchronized_value);

    void display_button(sf::RenderWindow& Window) const;

    void event_holder(sf::Event& event);
};


#endif //TEXTBAR_BUTTON_H
