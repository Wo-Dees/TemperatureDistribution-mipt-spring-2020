//
// Created by Карим Вафин on 28.04.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_MENU_H
#define TEMPERATURE_DISTRIBUTION_MENU_H

#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Font font;

    sf::Text create_text(float x, float y, std::string inf, int size, sf::Color color) const;

public:
    Menu();
    ~Menu() = default;

    // main method
    void run(sf::RenderWindow& window);
};


#endif //TEMPERATURE_DISTRIBUTION_MENU_H
