//
// Created by Карим Вафин on 28.04.2021.
//

#include "GUI.h"
#include "animation.h"
#include "menu.h"

GUI::GUI()
{}

void GUI::run()
{
    sf::RenderWindow window (sf::VideoMode(1000, 1000), "Temperature distribution");
    window.setFramerateLimit(30);
    sf::Image icon;
    if (!icon.loadFromFile("../Additional/icon.png"))
    {
        throw std::exception();
    }
    window.setIcon(500, 500, icon.getPixelsPtr());
    Menu menu(window);
    int choice = menu.run();
    std::queue<std::vector<double>> dat = menu.get_data();
    next_window(choice, window, dat);
}

void GUI::next_window(int choice, sf::RenderWindow& window, std::queue<std::vector<double>>& dat)
{
    switch (choice)
    {
        case 1:
            Animation anim(window, dat);
            anim.run();
    }
}