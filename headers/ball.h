//
// Created by msd on 7/18/18.
//


#ifndef BILLIARD_BALL_H
#define BILLIARD_BALL_H

#include<string>
#include <tgmath.h>

using namespace std;
#define PI 3.14159265

class Ball {
public:
    Ball(double x, double y, double initialspeed, int R, int G, int B, int point, string color, int ID);

    void move();

    bool is_in_Hole();

    void set_R(int R);

    void set_G(int G);

    void set_B(int B);

    void set_x(double x);

    void set_y(double y);

    void set_ID(int ID);

    void set_initial_speed(double speed);

    void set_speed(double speed);

    void set_x_center(double x_center);

    void set_y_center(double y_center);

    void set_dx(double dx);

    void set_dy(double dy);

    void set_is_in_hole(bool isinhole);

    void set_initial_x(double initial_x);

    void set_initial_y(double initial_y);

    void set_hit_angle(double hit_angle);

    string get_color();

    int get_ID();

    int get_point();

    int get_R();

    int get_G();

    int get_B();

    double get_x();

    double get_y();

    double get_speed();

    double get_x_center();

    double get_y_center();

    double get_dx();

    double get_dy();

    double get_initial_speed();

    bool get_is_in_hole();

    double get_initial_x();

    double get_initial_y();

    double get_hit_angle();

private:
    string color;
    double x, y, speed, initialspeed, x_center, y_center, initial_x, initial_y;
    int R, G, B, point, ID;
    double dx = cos(PI * (180 + 45) / 180);
    double dy = sin(PI * (180 + 45) / 180);
    bool is_in_hole = false;
    double hit_angle = 0;

};
#endif //BILLIARD_BALL_H