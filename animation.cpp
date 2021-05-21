//
// Created by Карим Вафин on 28.04.2021.
//
#include "animation.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>

Animation::Animation(sf::RenderWindow& win) : Window(win)
{
    if (!font.loadFromFile("../Additional/Opel Sans Bold.ttf"))
        throw std::runtime_error("animation.cpp");
    height_of_rect = 27;
    width_of_rect = 48;
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
    temperature.resize(web.size());
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            temperature[x * j + i] = (10 * i);
    set_temperature();
}

int Animation::run(std::queue<std::vector<double>>& data)
{
    texts.clear();
    this->data = data;
    std::cout << data.size() << std::endl;
    unsigned long int counter = 0;
    sf::Text& temp = create_text(20, window.getSize().y - 100, "Temp", 50, sf::Color::White);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return 0;
        }
        int x = get_number_of_current_element();
        if (x >= 0 && x < temperature.size())
            temp.setString(std::to_string(int(temperature[x])) + " C");
        window.clear();
        if (!data.empty())
        {
            for (int i = 0; i < data.front().size(); ++i)
            {
                temperature[i] = data.front()[i];
            }
            if (!data.empty())
                data.pop();
        }
        draw_objects();
        set_temperature();
        window.display();
        counter++;
    }
    return 0;
}

std::vector<double> Animation::init_conditions()
{
    loading();
    sf::Text& temp = create_text(20, window.getSize().y - 100, "", 50, sf::Color::White);
    Button start("", 960, 1000, font, "Start", sf::Color(253, 106, 2), sf::Color::Yellow, window, false);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            start.event_holder(event);
        }
        int x = get_number_of_current_element();
        if (x >= 0 && x < temperature.size())
            temp.setString(std::to_string(int(temperature[x])) + " C");
        window.clear();
        if (start.is_active())
        {
            window.clear();
            break;
        }
        process_events();
        set_temperature();
        draw_objects();
        start.display_button(window);
        window.display();
    }
    return temperature;
}

void Animation::draw_web()
{
    for (auto& rect : web)
        window.draw(rect);
}

void Animation::draw_objects()
{
    draw_web();
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
    }
}

void Animation::process_events()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int x = get_number_of_current_element();
        if (x >= 0 && x < temperature.size())
        {
            temperature[x] += 50;
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

const std::queue<std::vector<double>>& Animation::getData() const {
    return data;
}

void Animation::loading()
{
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < temperature.size(); i++)
            if (temperature[i] - 10 >= 0)
                temperature[i] -= 10;
        if (*std::max_element(temperature.begin(), temperature.end()) < 2)
            break;
        window.clear();
        process_events();
        set_temperature();
        draw_objects();
        window.display();
    }
}

std::queue<std::vector<double>> Animation::load_from_file(std::string file_name)
{
    std::queue<std::vector<double >> answer;
    std::string buff;
    std::ifstream in(file_name);
    std::vector<double> part;
    if (in.is_open()) {
        for (int i = 0; i < 50000; i++)
        {
            getline(in, buff);
            std::vector<double> vec = str_to_vec(buff);
            for(auto& j: vec)
                part.push_back(j);
            if (part.size() == 1600)
            {
                answer.push(part);
                part.clear();
            }
        }
    }
    in.close();
    return answer;
}

std::vector<double> Animation::str_to_vec(std::string s)
{
    std::string::size_type sz;
    std::vector<std::string> vec;
    std::vector<double> ans;
    std::string word;
    std::stringstream str(s);
    while (str >> word)
    {
        double a = stod(word, &sz);
        ans.push_back(a);
    }
    return ans;
}