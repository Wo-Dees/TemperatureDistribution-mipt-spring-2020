//
// Created by Карим Вафин on 28.04.2021.
//

#include "GUI.h"
#include "animation.h"
#include "menu.h"

void GUI::run()
{
    sf::RenderWindow window (sf::VideoMode(1920, 1080), "Temperature distribution");
    Menu menu;
    Animation anim;
    menu.run(window);
    anim.run(window);
}