//
// Created by msd on 7/18/18.
//


#include <utility>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <tgmath.h>

#include "../headers/ball.h"
#include "../headers/game.h"

#define PI 3.14159265

//the constructor of Game class,set the balls positions
Game::Game( int turn) {
    this->players[0].first = 0;
    this->players[1].first = 1;
    this->players[0].second = 0;
    this->players[1].second = 0;
    this->myturn = turn;
    //we have a black ball ,a blue ball,a brown ball,a green ball ,a yellow ball,15 red balls, pink ball,cue ball
    handle = new Handle(150, 244, 188, 66, 100, 100);
    balls[0] = new Ball(1202, 480.5, 3, 0, 0, 0, 7, "black", 0);
    balls[1] = new Ball(744.5, 480.5, 3, 0, 0, 255, 5, "blue", 0);
    balls[2] = new Ball(411.5, 480.5, 3, 175, 117, 29, 4, "brown", 0);
    balls[3] = new Ball(411.5, 411.5, 3, 0, 255, 0, 3, "green", 0);
    balls[4] = new Ball(411.5, 549.5, 3, 255, 255, 0, 2, "yellow", 0);
    balls[5] = new Ball(1104.5, 480.5, 3, 255, 0, 0, 1, "red", 0);
    balls[6] = new Ball(1104.5, 501.5, 3, 255, 0, 0, 1, "red", 0);
    balls[7] = new Ball(1104.5, 459.5, 3, 255, 0, 0, 1, "red", 0);
    balls[8] = new Ball(1104.5, 438.5, 3, 255, 0, 0, 1, "red", 0);
    balls[9] = new Ball(1104.5, 522.5, 3, 255, 0, 0, 1, "red", 0);
    balls[10] = new Ball(1083.5, 449, 3, 255, 0, 0, 1, "red", 0);
    balls[11] = new Ball(1083.5, 470.125, 3, 255, 0, 0, 1, "red", 0);
    balls[12] = new Ball(1083.5, 512, 3, 255, 0, 0, 1, "red", 0);
    balls[13] = new Ball(1083.5, 490.875, 3, 255, 0, 0, 1, "red", 0);
    balls[14] = new Ball(1062.5, 456.875, 3, 255, 0, 0, 1, "red", 0);
    balls[15] = new Ball(1062.5, 504.125, 3, 255, 0, 0, 1, "red", 0);
    balls[16] = new Ball(1062.5, 480.5, 3, 255, 0, 0, 1, "red", 0);
    balls[17] = new Ball(1041.5, 470, 3, 255, 0, 0, 1, "red", 0);
    balls[18] = new Ball(1041.5, 491, 3, 255, 0, 0, 1, "red", 0);
    balls[19] = new Ball(1020.5, 480.5, 3, 255, 0, 0, 1, "red", 0);
    balls[20] = new Ball(999.5, 480.5, 3, 255, 0, 208, 6, "pink", 0);
    balls[21] = new Ball(372.5, 525.5, 5, 255, 255, 255, 0, "white", 0);
}
//to move cue ball
void Game::move_cue_ball() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//shoot the cue ball
        double d = get_handle()->get_x() - get_ball(21)->get_x_center();
        double l = get_handle()->get_y() - get_ball(21)->get_y_center();
        check_place_ball(21);
        if (d * d + l * l <= 5.25 * 5.25 * 4) {
            if (get_ball(21)->is_in_Hole()) {
                get_ball(21)->set_ID(0);
            } else {
                check_place_ball(21);
                get_ball(21)->set_dx(cos(PI * (180 + get_handle()->get_rotate()) / 180));
                get_ball(21)->set_dy(sin(PI * (180 + get_handle()->get_rotate()) / 180));
                get_ball(21)->move();
                get_ball(21)->set_ID(1);
                check_place_ball(21);
                set_flag(true);

            }
        }
    }
}

//this fuction use to get the suitable ball
Ball *Game::get_ball(int i) {
    return (this->balls)[i];
}

//this function get the handle
Handle *Game::get_handle() {
    return (this->handle);
}

//this function change place of balls and check some topics for example check the speed and check that if the ball hit the wall or not
void Game::change_place_ball(int i) {
    if (((get_ball(i)->get_ID()) == 1) && abs(get_ball(i)->get_speed()) > 1e-5) {
        if (get_ball(i)->is_in_Hole()) {
            get_ball(i)->set_ID(0);
        } else {
            check_place_ball(i);
            get_ball(i)->move();
            check_place_ball(i);
            get_ball(i)->set_speed(get_ball(i)->get_speed() - (get_ball(i)->get_speed()) * 2e-2);//reduce the speed each time
            if(i==21)
            {
                set_flag(true);
            }
        }
    } else if (((get_ball(i)->get_ID()) == 1) && abs(get_ball(i)->get_speed()) <= 1e-5) {
        get_ball(i)->set_ID(0);
        get_ball(i)->set_speed(5);
    }
}

//this function check if two ball hit or not
bool Game::is_ball_hit(int i, int j) {
    if (abs(get_ball(i)->get_x_center() - get_ball(j)->get_x_center()) <= 5.25 * 4) {
        if (abs(get_ball(i)->get_y_center() - get_ball(j)->get_y_center()) <= 5.25 * 4) {
            if ((get_ball(i)->get_ID() == 1)) {
                hit_speed_calculator(i, j);
                get_ball(j)->set_ID(1);

                return true;
            }
        }
    }
    return false;
}

//this function check if cue ball hits any ball or not
bool Game::is_cue_ball_hit_balls(int i) {
   return is_ball_hit(21, i);
}

//this function change rotation of the handle
void Game::change_rotate_of_handle() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {//this key set the angle of rotation 0
        get_handle()->set_rotate(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        get_handle()->set_rotate(30);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        get_handle()->set_rotate(45);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        get_handle()->set_rotate(60);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        get_handle()->set_rotate(90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
        get_handle()->set_rotate(120);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
        get_handle()->set_rotate(135);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
        get_handle()->set_rotate(150);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
        get_handle()->set_rotate(180);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
        get_handle()->set_rotate(-30);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
        get_handle()->set_rotate(-45);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
        get_handle()->set_rotate(-60);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
        get_handle()->set_rotate(-90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
        get_handle()->set_rotate(-120);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
        get_handle()->set_rotate(-135);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) {
        get_handle()->set_rotate(-150);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
        get_handle()->set_rotate(-180);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {//if rise angle of rotate  5 degree
        get_handle()->set_rotate(get_handle()->get_rotate() + 5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {//if reduce angle of rotate 5 degree
        get_handle()->set_rotate(get_handle()->get_rotate() - 5);
    }
}

//this function check about if the ball hit the wal or not!if yes it change the direction
void Game::check_place_ball(int i) {
    if (get_ball(i)->get_x() > 1290) {//if the ball hit the right wall
        get_ball(i)->set_x(1290);
        get_ball(i)->set_dx(get_ball(i)->get_dx() * (-1));
    }
    if (get_ball(i)->get_y() > 720) {//if the ball hit the down wall
        get_ball(i)->set_y(720);
        get_ball(i)->set_dy(get_ball(i)->get_dy() * (-1));
    }
    if (get_ball(i)->get_x_center() < 210) {//if the ball hit the left wall
        get_ball(i)->set_x(210);
        get_ball(i)->set_dx(get_ball(i)->get_dx() * (-1));
    }
    if (get_ball(i)->get_y_center() < 210) {//if the ball hit the up wall
        get_ball(i)->set_y(210);
        get_ball(i)->set_dy(get_ball(i)->get_dy() * (-1));
    }
}

//this function calculates speed of two balls
void Game::hit_speed_calculator(int i, int j) {
    hit_angle_calculater(i, j);
    double a = sin(2 * (get_ball(i)->get_hit_angle()));
    double b = cos((get_ball(i)->get_hit_angle()));
    get_ball(i)->set_speed(
            sqrt(get_ball(i)->get_initial_speed() * get_ball(i)->get_initial_speed() / ((a / b) * (a / b) + 1)));
    get_ball(j)->set_speed(abs(get_ball(i)->get_speed() * a / b));
    get_ball(j)->set_dx(cos(get_ball(j)->get_hit_angle()));
    get_ball(j)->set_dy(sin(get_ball(j)->get_hit_angle()));
    get_ball(i)->set_dx(cos(get_ball(i)->get_hit_angle()));
    get_ball(i)->set_dy(sin(get_ball(i)->get_hit_angle()));
}

//this function get the turn
int Game::get_turn() {
    return this->turn;
}

//this function set the turn
void Game::set_turn(int turn) {
    this->turn = turn;
}

//this function set the force of the shoot also change the initial speed of the cue ball
void Game::set_force() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {//if you click on Q key on the key board it set the initial speed of cue ball 5
        get_ball(21)->set_speed(5);
        get_ball(21)->set_initial_speed(5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        get_ball(21)->set_speed(7);
        get_ball(21)->set_initial_speed(7);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        get_ball(21)->set_speed(9);
        get_ball(21)->set_initial_speed(9);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        get_ball(21)->set_speed(11);
        get_ball(21)->set_initial_speed(11);
    }
}

//this function choose the target ball
void Game::choose_target_ball() {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (int i = 0; i < 21; i++) {
                double d = get_handle()->get_x() - get_ball(i)->get_x_center();
                double l = get_handle()->get_y() - get_ball(i)->get_y_center();
                if (d * d + l * l <= 5.25 * 5.25 * 4) {
                    this->target_ball_index = i;
                    break;
                }
            }
        }
}

//this function get the target ball
int Game::get_target_ball() {
    return this-> target_ball_index;
}

//this function changes the scores
void Game::change_scores() {
    if (not_hit_any_ball()) {
        players[1 - get_turn()].second += 4;
        set_turn(1 - get_turn());
    }
    if (not(is_cue_ball_hit_balls((get_target_ball())))) {
        players[1 - get_turn()].second += max(get_ball(get_hit_which_ball())->get_point(), 4);
        set_turn(1 - get_turn());
    }
    if (get_ball(21)->is_in_Hole()) {
        players[1 - get_turn()].second += max(get_ball(get_target_ball())->get_point(), 4);
        set_turn(1 - get_turn());
    }
    if (is_there_any_red_ball() && get_red_turn()) {
        if (not(get_ball(get_target_ball())->get_color() == "red")) {
            players[1 - get_turn()].second += 4;//meghdar khata ra bepors
            set_turn(1 - get_turn());
        }
    }
}

//this function check if the cue ball hit to any ball or not
bool Game::not_hit_any_ball() {
    for (int i = 0; i < 21; i++) {
        if (is_cue_ball_hit_balls(i)) {
            return false;
        }
    }
    return true;
}

//this function get the ball which cue ball hits with
int Game::get_hit_which_ball() {
    for (int i = 0; i < 21; i++) {
        if (is_cue_ball_hit_balls(i)) {
            return i;
        }
    }
}

//this function check that if it is a correct target ball or not
bool Game::check_target_ball() {
    if (get_target_ball() == -1) {
        return false;
    }
    if (is_there_any_red_ball() && get_red_turn()) {
        if (not(get_ball(get_target_ball())->get_color() == "red")) {
            return false;
        }
    }
    return (!((not(is_there_any_red_ball())) && (get_target_ball() != get_color_ball_turn())));
}

//this function get the red turn
bool Game::get_red_turn() {
    return this->red_turn;
}

//this function set the red turn
void Game::set_red_turn() {
    this->red_turn=not this->red_turn;
}

//this function check if there is any red ball or not
bool Game::is_there_any_red_ball() {
    for (int i = 5; i < 20; i++) {
        if (not(get_ball(i)->is_in_Hole())) {
            return true;
        }
    }
    return false;
}

//this function check the packets
void Game::check_packets() {
    for (int i = 0; i < 22; i++) {
        if (is_there_any_red_ball() &&  (i < 5 || 19 < i) && get_ball(i)->get_is_in_hole()) {
            get_ball(i)->set_is_in_hole(false);
            get_ball(i)->set_x(get_ball(i)->get_initial_x());
            get_ball(i)->set_y(get_ball(i)->get_initial_y());
        }
    }
}

//this function calculate hit angle of two balls
void Game::hit_angle_calculater(int i, int j) {
    get_ball(i)->set_hit_angle(
            atan((get_ball(i)->get_y() - get_ball(j)->get_y()) / (get_ball(i)->get_x() - get_ball(j)->get_x())));
    get_ball(j)->set_hit_angle(
            (2 * atan((get_ball(i)->get_y() - get_ball(j)->get_y()) / (get_ball(i)->get_x() - get_ball(j)->get_x()))));
}

//this function get my turn
int Game::get_myturn() {
    return this->myturn;
}

//this function set my turn
void Game::set_my_turn(int myturn) {
    this->myturn=myturn;
}

//this function set the scores
void Game::set_score(int i,int score) {
    this->players[i].second=score;
}

//this function get the scores
int Game::get_score(int i) {
    return this->players[i].second;
}

//this function check if its the end of the game or not
bool Game::is_the_end() {
    for (int i = 0; i < 21; i++) {
        if (not(get_ball(i)->get_is_in_hole())) {
            return false;
        }
    }
    this->winner = 0;
    if (get_score(0) <= get_score(1)) {
       this->winner = 1;
    }
    return true;
}

//this function get players score
pair<int, int> Game::get_players(int i) {
    return this->players[i];
}

//this function set players score
void Game::set_players(int i, int j,int l) {
    if (j == 0) {
        this->players[i].first = l;
    } else {
        this->players[i].second = l;
    }
}

//this function get the flag
bool Game::get_flag() {
    return this->flag;
}

//this function set the flag
void Game::set_flag(bool a) {
    this->flag = a;
}

//this function set the target ball index
void Game::set_target_ball(int index) {
    this->target_ball_index = index;
}

//This function check that is there any ball still moving or not
bool Game::is_still_moving() {
    for (int i = 0; i < 22; i++) {
        if (get_ball(i)->get_ID() == 1) {
            return true;
        }
    }
    return false;
}

//this function check balls those are in packets
vector<int> Game::get_in_packet() {
    return this->in_packet;
}

//this function set a vector that is contain in_hole balls
void Game::set_in_packet() {
    for (int i = 0; i < 21; i++) {
        if (get_ball(i)->get_is_in_hole()) {
            this->in_packet.push_back(i);
        }
    }
}

//this function check if the ball is new in_hole or not
void Game::set_new_in_packet(int i) {
    this->new_in_packet.push_back(i);
}

//this function get the in_hole balls
bool Game::is_in_packet_list(int i) {
    for (int j = 0; j < this->in_packet.size(); j++) {
        if (in_packet[j] == i) {
            return true;
        }
    }
    return false;
}

//this function get the in hole balls
vector<int> Game::get_new_in_packet() {
    return new_in_packet;
}

//this function clear in packet vector
void Game::clear_new_in_packet() {
    this->new_in_packet.clear();

}

//this function get the winner of the game
int Game::get_winner() {
    return this->winner;
}

//this function color ball turn
int Game::get_color_ball_turn() {
    for (int i = 0; i < 5; i++) {
        if (not(get_ball(i)->get_is_in_hole())) {
            return i;
        }
    }
    if (not(get_ball(20)->get_is_in_hole())) {
        return 20;
    }
}
