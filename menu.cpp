//
// Created by Карим Вафин on 28.04.2021.
//

#include "menu.h"
#include <string>
#include <iostream>

Menu::Menu(sf::RenderWindow& win, Animation& anim) : Window(win), anim(anim)
{
    choice = 0;
    filename = "";
}

int Menu::run()
{
    choice = 0;
    start_step();
    if (choice == 1)
        init_conditions_step();
    if (choice == 2)
        load_file_step();
    return choice;
}

void Menu::start_step()
{
    sf::Text title = create_text(350, 70, "Temperature distribution", 100, sf::Color::White);
    Button button1("Set initial conditions", 960, 350, font, "Set initial conditions", sf::Color(253, 106, 2), sf::Color::Yellow, window, false);
    Button button2("Set initial conditions", 960, 500, font, "Load from file", sf::Color(253, 106, 2), sf::Color::Yellow, window, false);
    Button button3("Set initial conditions", 960, 650, font, "Exit", sf::Color(253, 106, 2), sf::Color::Yellow, window, false);
    Buttons.push_back(button1);
    Buttons.push_back(button2);
    Buttons.push_back(button3);
    button_animation();
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            for (auto& b: Buttons)
                b.event_holder(event);
        }
        process_events();
        window.clear(sf::Color::White);
        draw_objects();
        window.display();
        if (choice != 0)
            break;
    }
}

// load from file
void Menu::load_file_step()
{
    choice = 2;
    Buttons.clear();
    Button button1("", 960, 300, font, "Filename", sf::Color(253, 106, 2), sf::Color::Yellow, window, false);
    Button button2("", 960, 450, font, "Exit", sf::Color(253, 106, 2), sf::Color::Yellow, window, false);
    //TextBar filename_bar(1050, 300, );
    Buttons.push_back(button1);
    Buttons.push_back(button2);
    button_animation();
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (choice == -1)
            window.close();
        process_events();
        window.clear(sf::Color::White);
        draw_objects();
        window.display();
        if (choice == 1)
        {
            choice = 2;
            break;
        }
    }
}

void Menu::init_conditions_step()
{
    choice = 1;
}

void Menu::process_events()
{
    if (Buttons[0].is_active())
        choice = 1;
    if (Buttons[1].is_active())
        choice = 2;
    if (Buttons[2].is_active())
        choice = 3;
}

void Menu::button_animation()
{
    for (int i = 0; i < Buttons.size(); i++)
    {
        sf::Vector2i pos = Buttons[i].get_position();
        Buttons[i].set_position(-900, pos.y);
        while (Buttons[i].get_position().x < pos.x)
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            Buttons[i].move(150, 0);
            window.clear(sf::Color::White);
            anim.draw_web();
            for (int k = 0; k <= i; k++)
                Buttons[k].display_button(window);
            window.draw(texts[0]);
            window.display();
        }
        sf::Vector2i new_pos = Buttons[i].get_position();
        for (int j = 0; j < int(abs(pos.x - new_pos.x)) / 20; j++)
        {
            Buttons[i].move(-20, 0);
            window.clear(sf::Color::White);
            anim.draw_web();
            for (int k = 0; k <= i; k++)
                Buttons[k].display_button(window);
            window.draw(texts[0]);
            window.display();
        }
    }
}

void Menu::draw_objects()
{
    for (auto& btn : buttons)
        window.draw(btn);
    anim.draw_web();
    for (auto& txt : texts)
        window.draw(txt);
    for (auto& b : Buttons)
        b.display_button(window);

}

std::queue<std::vector<double>> Menu::get_data()
{
    return data;
}

const std::string &Menu::getFilename() const {
    return filename;
}

