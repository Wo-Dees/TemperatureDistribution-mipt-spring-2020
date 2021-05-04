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
    Animation(sf::RenderWindow& win);
    ~Animation() = default;

    // main method
    int run() override;

    void draw_objects() override;

    void set_temperature();

    void process_events();

    int get_number_of_current_element();

    void heat_near_elements(unsigned int x);
};


#endif //TEMPERATURE_DISTRIBUTION_ANIMATION_H
