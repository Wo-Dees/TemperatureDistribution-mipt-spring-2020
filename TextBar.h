//
// Created by evgen on 18.05.2021.
//

#ifndef TEXTBAR_TEXTBAR_H
#define TEXTBAR_TEXTBAR_H
#include <SFML/Graphics.hpp>

struct ShapeOfBbox
{
    int length; int width;
    int x; int y;
    int left_corner_x; int left_corner_y;
    int mouse_x_min; int mouse_x_max;
    int mouse_y_min; int mouse_y_max;

    ShapeOfBbox(int x = 0, int y = 0, int length = 0, int width = 0);
    bool is_in(int x_, int y_) const;
};

class TextBar {
private:
    sf::Font font;
    ShapeOfBbox Shape;
    sf::String s;
    sf::Text txt;
    sf::Sprite box;
    int b_size;
    bool active;
    int max_size_of_text;

public:

    TextBar(int x, int y, int length, int width, const sf::Texture& texture, const sf::Font& font, std::string initial_data, int max_size_of_text);

    void setActive();

    void setPassive();

    int getTextLength() const;

    void displayBox(sf::RenderWindow& window) const;

    void setText(std::string& str);

    void event_holder(sf::Event& event);

    std::string returnText();
};


#endif //TEXTBAR_TEXTBAR_H
