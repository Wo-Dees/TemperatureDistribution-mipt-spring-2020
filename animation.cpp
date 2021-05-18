//
// Created by Карим Вафин on 28.04.2021.
//

#include "animation.h"
#include <iostream>
#include <unistd.h>

Animation::Animation(sf::RenderWindow& win, std::queue<std::vector<double>> data) : Window(win)
{
    this->data = data;
    if (!font.loadFromFile("../Additional/Opel Sans Bold.ttf"))
        throw std::exception();
    height_of_rect = 20;
    width_of_rect = 40;
    int x = window.getSize().x / width_of_rect;
    int y = window.getSize().y / height_of_rect;
    web.reserve(window.getSize().x / width_of_rect * window.getSize().y / height_of_rect);
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            sf::RectangleShape rect;
            rect.setPosition(float(width_of_rect * j), float(height_of_rect * i));
            rect.setSize(sf::Vector2f(width_of_rect, height_of_rect));
            web.push_back(rect);
        }
    }
    temperature.reserve(web.size());
    for (int i = 0; i < web.size(); i++)
        temperature.push_back(0);
}

int Animation::run()
{
    unsigned long int counter = 0;
    std::cout << this->data.size();
    sf::Text& temp = create_text(20, window.getSize().y - 100, "Temp", 50, sf::Color::White);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        int x = get_number_of_current_element();
        if (x >= 0 && x < temperature.size())
            temp.setString(std::to_string(int(temperature[x])) + "C | " + std::to_string(sf::Mouse::getPosition(window).x));
        window.clear();
        if (!data.empty())
        {
            for (int i = 0; i < data.front().size(); ++i)
            {
                temperature[i] = data.front()[i];
            }
            if (!data.empty())
                data.pop();
            if (!data.empty())
                data.pop();
            if (!data.empty())
                data.pop();
            if (!data.empty())
                data.pop();
        }
        //process_events();
        set_temperature();
        draw_objects();
        window.display();
        counter++;
//        sleep(1);
    }
    return 0;
}

void Animation::draw_objects()
{
    for (auto& rect : web)
        window.draw(rect);
    for (auto& txt : texts)
        window.draw(txt);
}

void Animation::set_temperature()
{
    for (int i = 0; i < web.size(); i++)
    {
//        if (temperature[i] > 0)
//            temperature[i] -= 0.01;
        int color1 = 0;
        int color2 = 0;
        int color3 = 0;
        int color = int(temperature.at(i) / 2);
        if (color < 100)
            color1 = color;
        else
        {
            color1 = 100;
            color -= 100;
            if (color1 + color / 2 < 256)
                color1 += color / 2;
            else color1 = 255;
            if (color2 + color / 2 < 256)
                color2 += color / 2;
            else
                color2 = 255;
        }
        web[i].setFillColor(sf::Color(color1, color2, color3));
        //heat_near_elements(i);
    }
}

void Animation::process_events()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int x = get_number_of_current_element();
        if (x >= 0 && x < temperature.size())
        {
            temperature[x] += 10;
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        int x = get_number_of_current_element();
        if (x >= 0 && x < temperature.size())
        {
            if (temperature[x] > 0)
                temperature[x] -= 10;
        }
    }
}

int Animation::get_number_of_current_element()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    int y = (mouse_pos.y + 1) / height_of_rect;
    int x = mouse_pos.x / width_of_rect;
    std::vector<int> vec;
    return window.getSize().x / width_of_rect * y + x;
}

void Animation::heat_near_elements(unsigned int x)
{
    std::vector<int> vec;
    vec.push_back(x);
    vec.push_back(x + 1);
    vec.push_back(x + 2);
    vec.push_back(x + window.getSize().x / width_of_rect);
    vec.push_back(x + window.getSize().x / width_of_rect + 1);
    vec.push_back(x + window.getSize().x / width_of_rect - 1);
    vec.push_back(x + 2 * window.getSize().x / width_of_rect);
    vec.push_back(x - 1);
    vec.push_back(x - 2);
    vec.push_back(x - window.getSize().x / width_of_rect + 1);
    vec.push_back(x - window.getSize().x / width_of_rect - 1);
    vec.push_back(x - window.getSize().x / width_of_rect);
    vec.push_back(x - 2 * window.getSize().x / width_of_rect);
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] >= 0 && vec[i] < temperature.size() && temperature[vec[i]] < temperature[vec[0]])
        {
            double t_start = temperature[vec[i]];
            temperature[vec[i]] += (temperature[vec[0]] - temperature[vec[i]]) * 0.1;
            temperature[vec[0]] -= (temperature[vec[0]] - t_start) * 0.04;
        }
    }
}