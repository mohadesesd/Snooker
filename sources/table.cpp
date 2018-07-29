//
// Created by msd on 7/18/18.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <thread>
#include "../headers/game.h"
#include "../headers/hole.h"
#include "../headers/table.h"
#include "../headers/handle.h"


Table::Table(Game *game) {
}

//to draw table and balls
Table::Table(sf::RenderWindow* window, Game *game) {
    sf::RectangleShape rectangle(sf::Vector2f(1110, 540));
    rectangle.setFillColor(sf::Color(3, 48, 0));
    rectangle.setOutlineThickness(10);
    rectangle.setOutlineColor(sf::Color(53, 15, 1));
    rectangle.setPosition(200, 200);
    sf::RectangleShape hand(sf::Vector2f((game->get_handle()->get_size()) * 3, 4 * 2));
    hand.setFillColor(sf::Color(static_cast<sf::Uint8>(game->get_handle()->get_R()),
                                static_cast<sf::Uint8>(game->get_handle()->get_G()),
                                static_cast<sf::Uint8>(game->get_handle()->get_B())));
    hand.setPosition(static_cast<float>(game->get_handle()->get_x()), static_cast<float>(game->get_handle()->get_y()));
    hand.rotate(game->get_handle()->get_rotate());
    Hole *hole, *hole1, *hole2, *hole3, *hole4, *hole5;
    hole = new Hole(181.5, 181.5);
    hole1 = new Hole(736.5, 181.5);
    hole2 = new Hole(1291.5, 181.5);
    hole3 = new Hole(1291.5, 721.5);
    hole4 = new Hole(181.5, 721.5);
    hole5 = new Hole(736.5, 726.5);
    Ball **ball;
    ball = new Ball *[22];
    sf::VertexArray line(sf::LinesStrip, 2);
    line[0].position = sf::Vector2f(422, 200);
    line[1].position = sf::Vector2f(422, 740);
    sf::CircleShape semicircle(23 * 3);
    semicircle.setPosition(411.5 + 5.25 * 2 - 23 * 3, 480.5 + 5.25 * 2 - 23 * 3);
    semicircle.setFillColor(sf::Color(3, 48, 0));
    semicircle.setOutlineThickness(1);
    semicircle.setOutlineColor(sf::Color(255, 255, 255));
    sf::RectangleShape semirectangle(sf::Vector2f(23 * 3 * 2, 23 * 3 * 3 + 5.25 * 2));
    semirectangle.setFillColor(sf::Color(3, 48, 0));
    semirectangle.setPosition(411.5 + 5.25 * 2, 411.5 + 5.25 * 2);
    window->draw(rectangle);
    window->draw(semicircle);
    window->draw(semirectangle);
    window->draw(line);
    hole->make_hole(window);
    hole1->make_hole(window);
    hole2->make_hole(window);
    hole3->make_hole(window);
    hole4->make_hole(window);
    hole5->make_hole(window);
    for (int i = 0; i < 22; i++) {
        ball[i] = game->get_ball(i);
        if (not(game->get_ball(i)->get_is_in_hole())) {
            sf::CircleShape balli(5.25 * 2);
            balli.setPosition(static_cast<float>(ball[i]->get_x()), static_cast<float>(ball[i]->get_y()));
            balli.setFillColor(
                    sf::Color(static_cast<sf::Uint8>(ball[i]->get_R()), static_cast<sf::Uint8>(ball[i]->get_G()),
                              static_cast<sf::Uint8>(ball[i]->get_B())));
            window->draw(balli);
        }
    }
    if (game->get_myturn() == game->get_turn()) {
        sf::CircleShape target_on(20, 4);
        target_on.setPosition(1000, 100);
        if (game->get_target_ball() == -1) {
            target_on.setFillColor(sf::Color(247, 244, 245));
            game->choose_target_ball();
        }
        if (game->get_target_ball() != -1) {
            target_on.setFillColor(sf::Color(244, 4, 84));
        }
        sf::CircleShape turnball(20, 8);
        turnball.setPosition(1100, 100);
        turnball.setFillColor(sf::Color(23, 216, 149));
        window->draw(turnball);
        window->draw(target_on);
        game->get_handle()->move(window);
        game->change_rotate_of_handle();
        game->set_force();
        game->move_cue_ball();
        for (int i = 0; i < 21; i++) {
            if (game->is_cue_ball_hit_balls(i) && i == game->get_target_ball()) {
                game->change_place_ball(i);
                game->change_place_ball(21);
                this->flag = 1;
            } else if (game->is_cue_ball_hit_balls(i)) {
                game->change_place_ball(i);
                game->change_place_ball(21);
                this->flag = 2;
            }
            if (game->get_ball(i)->get_is_in_hole()) {
                if (not(game->is_in_packet_list(i))) {
                    game->set_new_in_packet(i);
                }
            }
            game->change_place_ball(i);
            game->change_place_ball(21);
        }
        for (int i = 0; i < 21; i++) {
            for (int j = 0; j < 22; j++) {
                if (i != j && game->is_ball_hit(i, j)) {
                    game->change_place_ball(i);
                    game->change_place_ball(j);
                }
            }
        }
    } else {
        game->set_target_ball(-1);
        sf::CircleShape turnball(20, 8);
        turnball.setPosition(1100, 100);
        turnball.setFillColor(sf::Color(181, 69, 204));
        window->draw(turnball);
    }

    window->draw(hand);
}

int Table::get_flag() {
    return this->flag;
}

void Table::set_flag(int i) {
    this->flag=i;
}
