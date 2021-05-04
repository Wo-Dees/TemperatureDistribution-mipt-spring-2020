//
// Created by Карим Вафин on 29.04.2021.
//

#include "Window.h"

Window::Window(sf::RenderWindow& win) : window(win)
{
    if (!font.loadFromFile("../Additional/Vampire95 Regular.ttf"))
        throw std::exception();
}

sf::Text& Window::create_text(float x, float y, std::string inf, int size, sf::Color color)
{
    sf::Text text;
    text.setFont(font);
    text.setString(inf);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y - float(size) / 2);
    texts.push_back(text);
    return *texts.rbegin();
}

sf::RectangleShape& Window::create_button(float pos_x, float pos_y, float size_x, float size_y, sf::Color color)
{
    sf::RectangleShape rect(sf::Vector2f(size_x, size_y));
    rect.setPosition(pos_x, pos_y);
    rect.setFillColor(color);
    buttons.push_back(rect);
    return *buttons.rbegin();
}

void Window::draw_objects()
{
    for (auto& btn : buttons)
        window.draw(btn);
    for (auto& txt : texts)
        window.draw(txt);
}