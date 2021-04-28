//
// Created by Карим Вафин on 28.04.2021.
//

#include "animation.h"

void Animation::run(sf::RenderWindow &window)
{
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
}

