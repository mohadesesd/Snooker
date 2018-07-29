//
// Created by msd on 7/18/18.
//
#include "../headers/resource.h"
#include <sstream>
#include <iostream>
using namespace std;

//constructor of resource class
Resource::Resource(Game *game) {
    this->game = game;
}

//set function of resource class read data from a string stream
void Resource::set(std::string str) {
    std::stringstream inp(str);
    int turn, i, score,rotation;
    double ball_x, ball_y, speed, dx, dy;
    bool is_in_hole;
    int ID;
    for (int i = 0; i < 22; i++) {
        inp >> ball_x >> ball_y >> is_in_hole;
        this->game->get_ball(i)->set_x(ball_x);
        this->game->get_ball(i)->set_y(ball_y);
        this->game->get_ball(i)->set_is_in_hole(is_in_hole);
    }

    inp >> rotation;
    game->get_handle()->set_rotate(rotation);
    inp >> turn;
    this->game->set_turn(turn);
    inp >> i >> score;
    this->game->set_score(i, score);
    inp >> i >> score;
    this->game->set_score(i, score);
    cout<<" Player "<< 1<<" Get: " << " " << this->game->get_score(0) <<endl;
    cout<<" Player "<< 2<<" Get: " << " " << this->game->get_score(1) <<endl;
    return;
}

//get  function of the resource class to write a data on string stream
std::string Resource::get() {
    std::stringstream res;
    for (int i = 0; i < 22; i++) {
        res << this->game->get_ball(i)->get_x() << " "
            << this->game->get_ball(i)->get_y() << " "
            << this->game->get_ball(i)->get_is_in_hole() << " ";
    }
    res << game->get_handle()->get_rotate() << " ";
    res << this->game->get_turn() << " ";
    res << 0 << " " << this->game->get_score(0) << " ";
    res << 1 << " " << this->game->get_score(1) << " ";
    cout<<" Player "<< 1<<" Get: " << " " << this->game->get_score(0) <<endl;
    cout<<" Player "<< 2<<" Get: " << " " << this->game->get_score(1) <<endl;
    return res.str();
}