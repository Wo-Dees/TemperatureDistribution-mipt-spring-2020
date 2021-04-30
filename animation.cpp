//
// Created by Карим Вафин on 28.04.2021.
//

#include "animation.h"
#include <iostream>

Animation::Animation()
{
    font.loadFromFile("/Users/karimvafin/Documents/Repositories/MIPT/Temperature_distribution/Opel Sans Bold.ttf");
    int x = 1920 / 2;
    int y = 1080 / 2;
    int color1 = 0;
    int color2 = 0;
    int color3 = 0;
    web.reserve(1920 / 2 * 1080 / 2);
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            sf::RectangleShape rect;
            rect.setPosition(float(2 * j), float(2 * i));
            rect.setSize(sf::Vector2f(2, 2));
            rect.setFillColor(sf::Color(color1, color2, color3));
            web.push_back(rect);
        }
        if (i % 5 == 0)
        {
            color1++;
        }
        else
            if (i % 5 == 1)
            {
                color2++;
                color1--;
            }
            else
                if (i % 5 == 2)
                {
                    color3++;
                    color2--;
                }
    }
}

int Animation::run(sf::RenderWindow &window)
{
    sf::Text& temperature = create_text(20, 980, "Temp", 50, sf::Color::White);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        temperature.setString(std::to_string(sf::Mouse::getPosition(window).x));
        window.clear();
        draw_objects(window);
        window.display();
    }
    return 0;
}

void Animation::draw_objects(sf::RenderWindow &window)
{
    for (auto& rect : web)
        window.draw(rect);
    for (auto& txt : texts)
        window.draw(txt);
}

