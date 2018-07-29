//
// Created by msd on 7/18/18.
//

#include <iostream>
#include "../headers/ball.h"

//this is constructor of ball class it get positions and initial speed and color of ball in RGB(Red,Green,Blue) method and point of the ball
//and ID to check if it is moving or static
Ball::Ball(double x, double y, double initialspeed, int R, int G, int B, int point, string color, int ID) {
    set_x(x);
    set_y(y);
    set_initial_x(x);
    set_initial_y(y);
    set_R(R);
    set_G(G);
    set_B(B);
    set_ID(ID);
    set_initial_speed(initialspeed);
    set_speed(initialspeed);
    this->point = point;
    this->color = color;
}

//This function set the speed of the ball
void Ball::set_speed(double speed) {
    this->speed = speed;
}

//This function get the speed of the ball
double Ball::get_speed() {
    return this->speed;
}

//This function set the ID of the ball it use to check that if the ball is moving or static
void Ball::set_ID(int ID) {
    this->ID = ID;
}

//This function get the ID of the ball
int Ball::get_ID() {
    return this->ID;
}

//This function get the color of the ball
string Ball::get_color() {
    return this->color;
}

//This function get the point of the ball
int Ball::get_point() {
    return this->point;
}

//This function set the x_position of ball
void Ball::set_x(double x) {
    this->x_center = x + 5.25 * 2;
    this->x = x;
}

//This function get the x_position of the ball
double Ball::get_x() {
    return this->x;
}

//This function set the y_position of the ball
void Ball::set_y(double y) {
    this->y_center = y + 5.25 * 2;
    this->y = y;
}

//This function get the y_position of the ball
double Ball::get_y() {
    return this->y;
}

//This function set the Blue number of RGB
void Ball::set_B(int B) {
    this->B = B;
}

//This function get the Blue number of RGB
int Ball::get_B() {
    return this->B;
}

//This function set the Green number of RGB
void Ball::set_G(int G) {
    this->G = G;
}

//This function get the Green number of RGB
int Ball::get_G() {
    return this->G;
}

//this function set the Red number of RGB
void Ball::set_R(int R) {
    this->R = R;
}

//This function get the Red number of RGB
int Ball::get_R() {
    return this->R;
}

//This function get the X position of center of the ball
double Ball::get_x_center() {
    return this->x_center;
}

//This function Get the Y position of center of the ball
double Ball::get_y_center() {
    return this->y_center;
}

//this function set the X position of center of the ball
void Ball::set_x_center(double x_center) {
    this->x_center = x_center;
}

//this function set Y position of center of the ball
void Ball::set_y_center(double y_center) {
    this->y_center = y_center;
}

//this function set the dx of the ball
void Ball::set_dx(double dx) {
    this->dx = dx;
}

//this function set  the dy of the ball
void Ball::set_dy(double dy) {
    this->dy = dy;
}

//this function get the dx of the ball
double Ball::get_dx() {
    return this->dx;
}

//this function get the dy of the ball
double Ball::get_dy() {
    return this->dy;
}

//this function change place of the ball and move it
void Ball::move() {
    set_x_center(get_x_center() + (get_speed()) * get_dx());
    set_y_center(get_y_center() + (get_speed()) * get_dy());
    set_x(get_x() + (get_speed()) * get_dx());
    set_y(get_y() + (get_speed()) * get_dy());
}

//this fuction check if the ball is in the hole or not
bool Ball::is_in_Hole() {
    if (sqrt((get_x_center() - 181.5 - 8 * 2) * (get_x_center() - 181.5 - 8 * 2) +
             (get_y_center() - 181.5 - 8 * 2) * (get_y_center() - 181.5 - 8 * 2)) < 8 * 2) {
        this->is_in_hole = true;
        return true;
    }
    if (sqrt((get_x_center() - 736.5 - 8 * 2) * (get_x_center() - 736.5 - 8 * 2) +
             (get_y_center() - 181.5 - 8 * 2) * (get_y_center() - 181.5 - 8 * 2)) < 8 * 2) {
        this->is_in_hole = true;
        return true;
    }
    if (sqrt((get_x_center() - 1291.5 - 8 * 2) * (get_x_center() - 1291.5 - 8 * 2) +
             (get_y_center() - 181.5 - 8 * 2) * (get_y_center() - 181.5 - 8 * 2)) < 8 * 2) {
        this->is_in_hole = true;
        return true;
    }
    if (sqrt((get_x_center() - 1291.5 - 8 * 2) * (get_x_center() - 1291.5 - 8 * 2) +
             (get_y_center() - 721.5 - 8 * 2) * (get_y_center() - 721.5 - 8 * 2)) < 8 * 2) {
        this->is_in_hole = true;
        return true;
    }
    if (sqrt((get_x_center() - 181.5 - 8 * 2) * (get_x_center() - 181.5 - 8 * 2) +
             (get_y_center() - 721.5 - 8 * 2) * (get_y_center() - 721.5 - 8 * 2)) < 8 * 2) {
        this->is_in_hole = true;
        return true;
    }
    if (sqrt((get_x_center() - 736.5 - 8 * 2) * (get_x_center() - 736.5 - 8 * 2) +
             (get_y_center() - 726.5 - 8 * 2) * (get_y_center() - 726.5 - 8 * 2)) < 8 * 2) {
        this->is_in_hole = true;
        return true;
    }
    this->is_in_hole = false;
    return false;
}

//this function set the initial speed for the ball
void Ball::set_initial_speed(double speed) {
    this->initialspeed = speed;

}

//this function get the initial speed for the ball
double Ball::get_initial_speed() {
    return this->initialspeed;
}

//this function get the is_in_hole parameter of ball to check if the ball is in pockets or not
bool Ball::get_is_in_hole() {
    return this->is_in_hole;
}

//this function set the is_in_hole parameter of ball if the ball is in the hole it is true and false for else
void Ball::set_is_in_hole(bool isinhole) {
    this->is_in_hole = isinhole;
}

//this function set the initial x parameter of the ball
void Ball::set_initial_x(double initial_x) {
    this->initial_x = initial_x;

}

//this function set the initial y parameter of the ball
void Ball::set_initial_y(double initial_y) {
    this->initial_y = initial_y;
}

//this function get the initial x parameter of the ball
double Ball::get_initial_x() {
    return initial_x;
}

//this function get the initial y parameter of the ball
double Ball::get_initial_y() {
    return initial_y;
}

//this function set the hit angle of two balls
void Ball::set_hit_angle(double hit_angle) {
    this->hit_angle = hit_angle;
}

//this function get the hit angle of two balls
double Ball::get_hit_angle() {
    return this->hit_angle;
}