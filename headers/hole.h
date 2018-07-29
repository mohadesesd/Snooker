//
// Created by msd on 7/18/18.
//

#ifndef BILLIARD_HOLE_H
#define BILLIARD_HOLE_H

#include <SFML/Graphics/RenderWindow.hpp>

class Hole {
public:
    Hole(double x, double y);

    void set_x(double x);

    double get_x();

    void set_y(double y);

    double get_y();

    void make_hole(sf::RenderWindow *window);

private:
    double x, y;

};

#endif //BILLIARD_HOLE_H