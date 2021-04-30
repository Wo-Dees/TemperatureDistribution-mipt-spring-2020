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

public:
    Animation();
    ~Animation() = default;

    // main method
    int run(sf::RenderWindow& window);

    void draw_objects(sf::RenderWindow& window);
};


#endif //TEMPERATURE_DISTRIBUTION_ANIMATION_H
