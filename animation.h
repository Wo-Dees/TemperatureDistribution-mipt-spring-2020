//
// Created by Карим Вафин on 28.04.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_ANIMATION_H
#define TEMPERATURE_DISTRIBUTION_ANIMATION_H

#include <SFML/Graphics.hpp>
#include "Window.h"
#include <queue>
#include <vector>
#include "Button.h"

class Animation : public Window {
private:
    std::vector<sf::RectangleShape> web;
    std::vector<double> temperature;
    std::vector<std::vector<double>> temp_mas;
    int height_of_rect;
    int width_of_rect;
    std::queue<std::vector<double>> data;

public:
    Animation(sf::RenderWindow& win);
    ~Animation() = default;

    // main method
    int run(std::queue<std::vector<double>>& data);

    int run() override {return 0;}

    std::vector<double> init_conditions();

    void draw_objects() override;

    void draw_web();

    void set_temperature();

    void process_events() override;

    int get_number_of_current_element();

    void heat_near_elements(unsigned int x);

    const std::queue<std::vector<double>>& getData() const;

    std::queue<std::vector<double>> load_from_file(std::string file_name);

    std::vector<double> str_to_vec(std::string s);

    void loading();
};


#endif //TEMPERATURE_DISTRIBUTION_ANIMATION_H
