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