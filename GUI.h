//
// Created by Карим Вафин on 28.04.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_GUI_H
#define TEMPERATURE_DISTRIBUTION_GUI_H

#include "animation.h"
#include "menu.h"

class GUI {
public:
    GUI() = default;
    ~GUI() = default;

    // mainloop
    void run();

    void next_window(int choice, sf::RenderWindow& window);
};


#endif //TEMPERATURE_DISTRIBUTION_GUI_H
