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
#include "animation.h"


class Menu : public Window{
private:
    int choice;
    sf::Sprite backgr;
    std::queue<std::vector<double>> data;
    std::string filename;
    Animation anim;
    int method;

public:
    Menu(sf::RenderWindow& win, Animation& anim);
    ~Menu() = default;

    // main method
    int run() override;
    void start_step();
    void load_file_step();
    void init_conditions_step();
    void parameters();
    void process_events() override;
    void button_animation();
    void draw_objects() override;
    std::queue<std::vector<double >> get_data();
    const std::string &getFilename() const;
    int getMethod();
};


#endif //TEMPERATURE_DISTRIBUTION_MENU_H
