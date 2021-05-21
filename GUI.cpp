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
    next_window(choice, window, filename);
}

void GUI::next_window(int choice, sf::RenderWindow& window, std::string filename)
{
    Animation anim(window);
    switch (choice)
    {
        case 1:
        {
            std::vector<double> init_conditions = {1};
            for (auto& i : init_conditions)
                std::cout << i << " ";
            // вызов функции Лени которая вернет очередь и векторов
            std::queue<std::vector<double>> data;
            solver_mesh(data, aluminum, 1, 1, 30, 0, 0, 1, 100, init_conditions);
            anim.run(data);
        }
        case 2:
        {
            std::queue<std::vector<double>> data;
            data = anim.load_from_file("../" + filename);
            anim.run(data);
        }

    }
}