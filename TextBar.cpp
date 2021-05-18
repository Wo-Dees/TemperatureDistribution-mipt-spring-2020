//
// Created by evgen on 18.05.2021.
//

#include "TextBar.h"

ShapeOfBbox::ShapeOfBbox(int x , int y, int length, int width) {
    this->x = x;
    this->y = y;
    this->length = length;
    this->width = width;
    int center_x = int((this->length) / 2);
    int center_y = int((this->width) / 2);
    this->left_corner_x = x - center_x;
    this->left_corner_y = y - center_y;
    this->mouse_x_min = this->left_corner_x;
    this->mouse_x_max = this->left_corner_x + this->length;
    this->mouse_y_min = this->left_corner_y;
    this->mouse_y_max = this->left_corner_y + this->width;
}

bool ShapeOfBbox::is_in(int x_, int y_) const
{
    if (x_ <= this->mouse_x_max && x_ >= this->mouse_x_min && y_ <= this->mouse_y_max && y_ >= this->mouse_y_min)
        return true;
    return false;
}

TextBar::TextBar(int x, int y, int length, int width, const sf::Texture& texture, const sf::Font& font, std::string initial_data, int max_size_of_text): Shape(x, y, length, width)
{
    this->max_size_of_text = max_size_of_text;
    box.setTexture(texture);
    box.setOrigin((float)(Shape.x - Shape.left_corner_x), (float)(Shape.y - Shape.left_corner_y));
    box.setPosition((float)Shape.x, (float)Shape.y);

    active = false;

    this->font = font;
    s = initial_data;
    b_size = s.getSize();
    txt.setString(s);
    txt.setFont(font);
    txt.setPosition((float)Shape.left_corner_x, (float)Shape.left_corner_y);
    txt.setCharacterSize(35);
    txt.setFillColor(sf::Color::Black);
    txt.setStyle(sf::Text::Bold);
}

void TextBar::event_holder(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (this->Shape.is_in(event.mouseButton.x, event.mouseButton.y))
                this->setActive();
            else{
                this->setPassive();
            }
        }
    }

    if (this->active) {
        if (event.type == sf::Event::TextEntered) {
            switch (event.text.unicode) {
                case (0xD): {
                    setPassive();
                    return;
                }
                case (8):            //Backspace
                    if (!getTextLength()) return;
                    else {
                        s.erase((getTextLength() - 1), 1);
                        b_size--;
                        txt.setString(s);
                        return;
                    }
                default : {
                    if (this->b_size < this->max_size_of_text) {
                        s += (char) (event.text.unicode);
                        txt.setString(s);
                        b_size++;
                    }
                    return;
                }
            }
        }
    }
}

void TextBar::setActive(){
    active = true;
    box.setColor(sf::Color(128,128,128));
}

void TextBar::setPassive()
{
    active = false;
    box.setColor(sf::Color::White);
}

int TextBar::getTextLength() const
{
    return b_size;
}

void TextBar::displayBox(sf::RenderWindow& window) const
{
    window.draw(box);
    window.draw(txt);
}

void TextBar::setText(std::string& str)
{
    str = txt.getString();
}

std::string TextBar::returnText() {
    return this->s;
}
