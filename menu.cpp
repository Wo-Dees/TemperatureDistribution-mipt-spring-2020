//
// Created by Карим Вафин on 28.04.2021.
//

#include "menu.h"

Menu::Menu()
{
    font.loadFromFile("/Users/karimvafin/Documents/Repositories/MIPT/Temperature_distribution/font.ttf");
}

void Menu::run(sf::RenderWindow& window)
{
    sf::Text text = create_text(750, 50, "Hello blya", 100, sf::Color::Red);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }
}

sf::Text Menu::create_text(float x, float y, std::string inf, int size, sf::Color color) const
{
    sf::Text text;
    text.setFont(font);
    text.setString(inf);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    return text;
}