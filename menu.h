//
// Created by Карим Вафин on 28.04.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_MENU_H
#define TEMPERATURE_DISTRIBUTION_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"

class Menu : public Window{
private:
    int choice;
    sf::Sprite backgr;

public:
    Menu();
    ~Menu() = default;

    // main method
    int run(sf::RenderWindow& window) override;
    void process_events(sf::RenderWindow& window) override;
    void button_animation(sf::RenderWindow& window);
    void draw_objects(sf::RenderWindow& window) override;
};


#endif //TEMPERATURE_DISTRIBUTION_MENU_H
