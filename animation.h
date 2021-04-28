//
// Created by Карим Вафин on 28.04.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_ANIMATION_H
#define TEMPERATURE_DISTRIBUTION_ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation() = default;
    ~Animation() = default;

    // main method
    void run(sf::RenderWindow& window);
};


#endif //TEMPERATURE_DISTRIBUTION_ANIMATION_H
