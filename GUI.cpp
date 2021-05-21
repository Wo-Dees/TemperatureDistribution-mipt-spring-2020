//
// Created by Карим Вафин on 28.04.2021.
//

#include "GUI.h"
#include "animation.h"
#include "menu.h"
#include "difference_shame.h"
#include <vector>
using std::vector;

GUI::GUI()
{}

void GUI::run()
{
    sf::RenderWindow window (sf::VideoMode(1920, 1080), "Temperature distribution");
    window.setFramerateLimit(30);
    sf::Image icon;
    if (!icon.loadFromFile("../Additional/icon.png"))
    {
        throw std::runtime_error("GUI.cpp");
    }
    window.setIcon(500, 500, icon.getPixelsPtr());
    Animation anim(window);
    Menu menu(window, anim);
    int choice = menu.run();
    std::string filename = menu.getFilename();
    next_window(choice, window);
}

void GUI::next_window(int choice, sf::RenderWindow& window)
{
    Animation anim(window);
    switch (choice)
    {
        case 1:
        {
            //anim.init_conditions();
            //std::queue<std::vector<double>> init_conditions = anim.getData();
            // вызов функции Лени которая вернет очередь и векторов
            std::queue<std::vector<double>> data;
            solver_mesh(data, aluminum, 1, 1, 300, 500, 1, 0, 100);
            anim.run(data);
        }
        case 2:
        {
            std::queue<std::vector<double>> data;
            data = anim.load_from_file("../data.txt");
            anim.run(data);
        }

    }
}