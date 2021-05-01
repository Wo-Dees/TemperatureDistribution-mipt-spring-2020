//
// Created by Карим Вафин on 28.04.2021.
//

#include "GUI.h"
#include "animation.h"
#include "menu.h"

void GUI::run()
{
    sf::RenderWindow window (sf::VideoMode(1920, 1080), "Temperature distribution");
    window.setFramerateLimit(30);
    sf::Image icon;
    if (!icon.loadFromFile("../Additional/icon.png"))
    {
        throw std::exception();
    }
    window.setIcon(500, 500, icon.getPixelsPtr());
    Menu menu;
    Animation anim;
    int choice = menu.run(window);
    next_window(choice, window);
}

void GUI::next_window(int choice, sf::RenderWindow& window)
{
    switch (choice)
    {
        case 1:
            Animation anim;
            anim.run(window);
    }
}