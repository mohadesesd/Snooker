//
// Created by msd on 7/18/18.
//
#include <SFML/Graphics.hpp>
#include "../headers/handle.h"
#include<iostream>

//the constructor get the color of the handle and x and y(position of the handle)
Handle::Handle(int size, int R, int G, int B,double x,double y) {
    this->size = size;
    this->R = R;
    this->G = G;
    this->B = B;
    this->x = x;
    this->y = y;
}

//change place of the handle with mouse movement
void Handle::move(sf::RenderWindow* window) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
    this->x = localPosition.x;
    this->y = localPosition.y;
}

//get the size of the handle
int Handle::get_size() {
    return this->size;
}

//get the blue part of rgb coloring
int Handle::get_B() {
    return this->B;
}

//get the green part of rgb coloring
int Handle::get_G() {
    return this->G;
}

//get the red part of rgb coloring
int Handle::get_R() {
    return this->R;
}

//get the x position
double Handle::get_x() {
    return this->x;
}

//get the y position
double Handle::get_y() {
    return this->y;
}

//set the rotation of the handle
void Handle::set_rotate(int rotate) {
    this->rotate = rotate;
}

//get the rotation of the handle
int Handle::get_rotate() {
    return this->rotate;
}
