//
// Created by Карим Вафин on 28.04.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_ANIMATION_H
#define TEMPERATURE_DISTRIBUTION_ANIMATION_H

#include <SFML/Graphics.hpp>
#include "Window.h"

class Animation : public Window {
private:
    std::vector<sf::RectangleShape> web;
    std::vector<double> temperature;
    std::vector<std::vector<double>> temp_mas;
    int size_of_rect;

public:
    Animation();
    ~Animation() = default;

    // main method
    int run(sf::RenderWindow& window);

    void draw_objects(sf::RenderWindow& window);

    void set_temperature();

    void process_events(sf::RenderWindow& window);
};


#endif //TEMPERATURE_DISTRIBUTION_ANIMATION_H
