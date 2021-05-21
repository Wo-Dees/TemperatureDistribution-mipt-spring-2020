//
// Created by evgen on 18.05.2021.
//

#ifndef ONEBAR_H
#define ONEBAR_H
#include <SFML/Graphics.hpp>



class OneChoiseBar{
private:
    sf::Color back_color;
    sf::Color main_color;
    int x;
    int y;
    int radius;
    bool value;
    sf::RenderWindow win;
    sf::CircleShape ext_circle;
    sf::CircleShape int_circle;

    bool is_in(int x, int y);

public:
    OneChoiseBar(int x, int y, int dr, int radius, sf::Color back_color, sf::Color main_color);

    void display(sf::RenderWindow& window);

    void event_holder(sf::Event& event);

    bool return_value();
};


#endif //ONEBAR_H
