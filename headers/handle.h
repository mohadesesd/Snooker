//
// Created by msd on 7/18/18.
//

#ifndef BILLIARD_HANDLE_H
#define BILLIARD_HANDLE_H

#include <SFML/Graphics.hpp>

class Handle {
public:
    Handle(int size, int R, int G, int B, double x, double y);

    void move(sf::RenderWindow *window);

    int get_size();

    int get_R();

    int get_G();

    int get_B();

    double get_x();

    double get_y();

    int get_rotate();

    void set_rotate(int rotate);

private:
    int size, R, G, B, rotate = 45;
    double x, y;
    double ini_speed = 5;
};
#endif //BILLIARD_HANDLE_H
