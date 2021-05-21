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
    int method = menu.getMethod();
    std::string filename = menu.getFilename();
    next_window(choice, window, filename, method);
}

void GUI::next_window(int choice, sf::RenderWindow& window, std::string filename, int method)
{
    Animation anim(window);
    switch (choice)
    {
        case 1:
        {
            std::vector<double> init_conditions = anim.init_conditions();
            for (auto& i : init_conditions)
                std::cout << i << " ";
            // вызов функции Лени которая вернет очередь и векторов
            std::queue<std::vector<double>> data;
            // рабочая изотерма
            solver_mesh(data, aluminum, 100, 100, 1, 100, 1, 0, 0, init_conditions);
            anim.run(data);
            break;
        }
        case 2:
        {
            std::queue<std::vector<double>> data;
            data = anim.load_from_file("../" + filename);
            anim.run(data);
            break;
        }
        case 3:
        {
            std::vector<double> init_conditions = {0};
            // вызов функции Лёни которая вернет очередь и векторов
            std::queue<std::vector<double>> data;
            // рабочая изотерма (тут адиабата бессмысленна)
            solver_mesh(data, aluminum, 100, 100, 1, 500, 1, 0, 100, init_conditions);
            anim.run(data);
            break;
        }
        case 4:
        {
            std::vector<double> init_conditions = {1};
            // вызов функции Лени которая вернет очередь и векторов
            std::queue<std::vector<double>> data;
            if (method == 1)
                solver_mesh(data, aluminum, 100, 100, 1, 0, 0, 1, 1000, init_conditions);
            else
                solver_mesh(data, aluminum, 100, 100, 1, 500, 1, 0, 1000, init_conditions);
            anim.run(data);
            break;
        }

    }
}
