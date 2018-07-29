//
// Created by msd on 7/18/18.
//


#ifndef BILLIARD_GAME_H
#define BILLIARD_GAME_H

#include<vector>
#include<new>
#include <string>
#include"ball.h"
#include "handle.h"
using namespace std;

class Game {
public:
    explicit Game(int turn);

    void move_cue_ball();

    void change_place_ball(int i);

    void set_turn(int turn);

    int get_turn();

    void set_force();

    bool is_cue_ball_hit_balls(int i);

    bool is_ball_hit(int i, int j);

    Ball *get_ball(int i);

    Handle *get_handle();

    void change_rotate_of_handle();

    void check_place_ball(int i);

    void hit_speed_calculator(int i, int j);

    void hit_angle_calculater(int i, int j);

    void choose_target_ball();

    void set_target_ball(int index);

    int get_target_ball();

    void change_scores();

    bool not_hit_any_ball();

    int get_hit_which_ball();

    bool check_target_ball();

    bool get_red_turn();

    void set_red_turn();

    bool is_there_any_red_ball();

    void check_packets();

    int get_myturn();

    void set_my_turn(int myturn);

    int get_score(int i);

    void set_score(int i, int score);

    bool is_the_end();

    pair<int, int> get_players(int i);

    void set_players(int i, int j, int l);

    bool get_flag();

    void set_flag(bool a);

    bool is_still_moving();

    vector<int> get_in_packet();

    void set_in_packet();

    bool is_in_packet_list(int i);

    void set_new_in_packet(int i);

    vector<int> get_new_in_packet();

    void clear_new_in_packet();

    int get_winner();

    int get_color_ball_turn();


private:
    Ball **balls = new Ball *[22];
    Handle *handle;
    pair<int, int> players[2];
    int turn, myturn;
    int target_ball_index = -1;
    bool red_turn = true;
    int winner;
    bool flag = false;
    vector<int> in_packet;
    vector<int> new_in_packet;
};

#endif //BILLIARD_GAME_H