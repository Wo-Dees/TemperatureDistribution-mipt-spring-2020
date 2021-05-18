//
// Created by Карим Вафин on 28.04.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_GUI_H
#define TEMPERATURE_DISTRIBUTION_GUI_H

#include "animation.h"
#include "menu.h"
#include <queue>
#include <vector>

class GUI {

public:
    GUI(){};
    ~GUI() = default;

    // mainloop
    void run();

    void next_window(int choice, sf::RenderWindow& window, std::queue<std::vector<double>>& dat);
};


#endif //TEMPERATURE_DISTRIBUTION_GUI_H
