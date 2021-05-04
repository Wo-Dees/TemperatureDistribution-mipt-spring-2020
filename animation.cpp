//
// Created by Карим Вафин on 28.04.2021.
//

#include "animation.h"
#include <iostream>

Animation::Animation(sf::RenderWindow& win) : Window(win)
{
    if (!font.loadFromFile("../Additional/Opel Sans Bold.ttf"))
        throw std::exception();
    size_of_rect = 20;
    int x = 1920 / size_of_rect;
    int y = 1080 / size_of_rect;
    web.reserve(1920 / size_of_rect * 1080 / size_of_rect);
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            sf::RectangleShape rect;
            rect.setPosition(float(size_of_rect * j), float(size_of_rect * i));
            rect.setSize(sf::Vector2f(size_of_rect, size_of_rect));
            web.push_back(rect);
        }
    }
    temperature.reserve(web.size());
    for (int i = 0; i < web.size(); i++)
        temperature.push_back(0);
    temperature[2560] = 100;
}

int Animation::run()
{
    sf::Text& temp = create_text(20, 980, "Temp", 50, sf::Color::White);
    int i = 0;
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
            temp.setString(std::to_string(int(temperature[x])) + "C");
        window.clear();
        //process_events(window);
        set_temperature();
        draw_objects();
        window.display();
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
        int color1 = 0;
        int color2 = 0;
        int color3 = 0;
        int color = int(temperature.at(i) * 5);
        if (color < 128)
            color1 = color;
        else
        {
            color1 = 128;
            color -= 128;
            if (color1 + color / 2 < 256)
                color1 += color / 2;
            else color1 = 255;
            if (color2 + color / 2 < 256)
                color2 += color / 2;
            else
                color2 = 255;
        }
        web[i].setFillColor(sf::Color(color1, color2, color3));
        heat_near_elements(i);
    }
}

void Animation::process_events()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    int y = mouse_pos.y / size_of_rect;
    int x = mouse_pos.x / size_of_rect;
    for (int j = 0; j < 50; j++)
        for (int i = 0; i < 50; i++)
        {
            if (abs(j) + abs(i) < 100)
            {
                unsigned int a = window.getSize().x / size_of_rect * (y - i) + x + j;
                unsigned int b = window.getSize().x / size_of_rect * (y + i) + x - j;
                unsigned int c = window.getSize().x / size_of_rect * (y - i) + x - j;
                unsigned int d = window.getSize().x / size_of_rect * (y + i) + x + j;
                int e = temperature.size();
                if (a >= 0 && a < e && temperature[a] < 100)
                    temperature[a] += 0.05 / (i + 1) / (j + 1) * 10;
                if (b >= 0 && b < e && temperature[b] < 100)
                    temperature[b] += 0.05 / (i + 1) / (j + 1) * 10;
                if (c >= 0 && c < e && temperature[c] < 100)
                    temperature[c] += 0.05 / (i + 1) / (j + 1) * 10;
                if (d >= 0 && d < e && temperature[d] < 100)
                    temperature[d] += 0.05 / (i + 1) / (j + 1) * 10;
            }
        }
}

int Animation::get_number_of_current_element()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    int y = mouse_pos.y / size_of_rect;
    int x = mouse_pos.x / size_of_rect;
    std::vector<int> vec;
    return window.getSize().x / size_of_rect * y + x;
}

void Animation::heat_near_elements(unsigned int x)
{
    std::vector<int> vec;
    vec.push_back(x);
    vec.push_back(x + 1);
    vec.push_back(x + window.getSize().x / size_of_rect);
    vec.push_back(x - 1);
    vec.push_back(x - window.getSize().x / size_of_rect);
    for (int i = 0; i < 5; i++)
    {
        if (vec[i] >= 0 && vec[i] < temperature.size() && temperature[vec[i]] < temperature[vec[0]])
            temperature[vec[i]] += (temperature[vec[0]] - temperature[vec[i]]) * 0.1;
    }
}