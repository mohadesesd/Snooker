//
// Created by msd on 7/18/18.
//

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include"../headers/hole.h"

//constructor of the hole Class get the position of the hole
Hole::Hole(double x, double y) {
    set_x(x);
    set_y(y);
}

//get the x position
double Hole::get_x(){
    return this->x;
}

//set the x position
void Hole::set_x(double x) {
    if (x == 200 - (8 * 2) - 2.5 || x == 200 + 370 * 3 / 2 - (8 * 2) - 2.5 || x == 200 + 370 * 3 - (8 * 2) - 2.5) {
        this->x = x;
    }
}

//get the y position
double Hole::get_y() {
    return this->y;
}

//set the y position
void Hole::set_y(double y) {
    if (y == 200 - (8 * 2) - 2.5 || y == 200 + 180 * 3 - (8 * 2) - 2.5 || y == 200 + 180 * 3 - (8 * 2) + 2.5) {
        this->y = y;
    }
}

//make hole function this function is like a draw function
void  Hole::make_hole(sf::RenderWindow *window) {
    sf::CircleShape hole((8) * 2);
    hole.setPosition(static_cast<float>(this->get_x()), static_cast<float>(this->get_y()));
    hole.setFillColor(sf::Color(53, 15, 1));
    return window->draw(hole);
}