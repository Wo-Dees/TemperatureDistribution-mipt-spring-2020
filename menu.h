//
// Created by Карим Вафин on 28.04.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_MENU_H
#define TEMPERATURE_DISTRIBUTION_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include <queue>
#include <vector>


class Menu : public Window{
private:
    int choice;
    sf::Sprite backgr;

public:
    Menu(sf::RenderWindow& win);
    ~Menu() = default;

    // main method
    int run() override;
    void process_events() override;
    void button_animation();
    void draw_objects() override;
    std::queue<std::vector<double>> load_from_file(std::string file_name);
};


#endif //TEMPERATURE_DISTRIBUTION_MENU_H
