//
// Created by msd on 7/26/18.
//

#include "headers/network.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<pthread.h>
#include <thread>
#include <chrono>
#include "headers/table.h"
#include "headers/UDPNetwork.h"

void task1(UDPNetwork * net, int *k);
void task2(Game* game,string name);
void task3(Game* game,Table* table);

int main() {
    int k = 0;
    int *s = &k;
    int a;
    std::cin >> a;
    Game *game;
    game = new Game(a);
    game->set_turn(0);
    Resource *resource;
    resource = new Resource(game);
    Network *network;
    UDPNetwork *net;
    net = new UDPNetwork(a);
    if (a == 0) {
        game->set_my_turn(0);
        network = new Network(resource, a, sf::IpAddress::getLocalAddress().toString());
        network->listen();
        std::thread t1(task1, net, s);
        network->accept();
        *s = 1;
        cout << *s << endl;
        if (t1.joinable()) {
            t1.join();
        }
    } else {
        game->set_my_turn(1);
        int b;
        std::chrono::system_clock systemClock;
        std::chrono::system_clock::time_point lastRun = systemClock.now();
        while (true) {
            if (systemClock.now() - lastRun >= std::chrono::seconds(2)) {
                lastRun += std::chrono::seconds(2);
                net->receivemessage();
                cout << "enter 1 to continue receiving message and 0 to stop receiving message:" << endl;
                cin >> b;
                if (b == 0) {
                    net->ShowServesList();
                    break;
                }
            }
        }
        cout << "Enter Ip and port of the server you want to connect to:" << endl;
        string H;
        unsigned int P;
        cin >> H >> P;
        net->chooseServer(H, P);
        network = new Network(resource, a, net->get_Host_IP());
        network->connect();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    string name = "";
    if (a == 0) {
        name = "Billiard-Server-Player1";
    } else {
        name = "Billiard-Client-Player2";
    }
    Table *table;
    table = new Table(game);
    std::thread t2(task2, game, name);
    if (game->get_turn() == game->get_myturn()) {
        network->send();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    } else {
        network->receive();
    }
    while (true) {
        if (game->get_turn() == game->get_myturn()) {
            task3(game, table);
            network->send();
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }
        if (game->get_turn() != game->get_myturn()) {
            network->receive();
        }
        if (game->is_the_end()) {
            cout << "The End" << endl;
            cout << " The winner is: " << game->get_winner() + 1;
            break;
        }
    }
    t2.join();
}

//task for broadcast thread
void task1(UDPNetwork * net, int *k) {
    std::chrono::system_clock systemClock;
    std::chrono::system_clock::time_point lastRun = systemClock.now();
    while (true) {
        if (systemClock.now() - lastRun >= std::chrono::seconds(2)) {
            lastRun += std::chrono::seconds(2);
            net->broadcast();
            if (*k == 1) {
                break;
            }

        }
    }
}

//task for GUI thread
void task2(Game* game,string name) {
    sf::RenderWindow window(sf::VideoMode(1500, 1500), name);
    while (window.isOpen()) {
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        Table(&window, game);
        window.display();
    }
}

//to check rules of the game
void task3(Game* game,Table* table) {
    if (not(game->is_still_moving())) {
        if (table->get_flag() == 0 && game->get_flag()) {
            game->set_players(1 - game->get_turn(), 1, game->get_players(1 - game->get_turn()).second + 4);
            game->set_turn(1 - game->get_turn());
            game->set_flag(false);
            table->set_flag(0);
            game->set_target_ball(-1);
            game->check_packets();
        } else if (table->get_flag() == 1 && game->get_flag()) {
            if (game->check_target_ball()) {
                if (game->get_ball(game->get_target_ball())->get_is_in_hole()) {
                    game->set_players(game->get_turn(), 1, game->get_players(game->get_turn()).second +
                                                           game->get_ball(game->get_target_ball())->get_point());
                    game->set_turn(game->get_turn());
                    if (game->get_ball(game->get_target_ball())->get_color() == "red") {
                        game->set_red_turn();
                    }
                    for (int i = 0; i < game->get_new_in_packet().size(); i++) {
                        if (i != game->get_target_ball()) {
                            game->set_players(1 - game->get_turn(), 1, game->get_players(1 - game->get_turn()).second +
                                                                       game->get_ball(i)->get_point());
                        }
                    }
                    game->check_packets();
                    game->set_flag(false);
                    table->set_flag(0);
                    game->set_target_ball(-1);
                } else {
                    game->set_players(1 - game->get_turn(), 1, game->get_players(1 - game->get_turn()).second +
                                                               max(4, game->get_ball(
                                                                       game->get_target_ball())->get_point()));
                    for (int i = 0; i < game->get_new_in_packet().size(); i++) {
                        if (i != game->get_target_ball()) {
                            game->set_players(1 - game->get_turn(), 1,
                                              game->get_players(1 - game->get_turn()).second +
                                              game->get_ball(i)->get_point());
                        }
                    }
                    game->check_packets();
                    game->set_turn(1 - game->get_turn());
                    game->set_flag(false);
                    table->set_flag(0);
                    game->set_target_ball(-1);
                }
            } else {
                for (int i = 0; i < game->get_new_in_packet().size(); i++) {
                    if (i != game->get_target_ball()) {
                        game->set_players(1 - game->get_turn(), 1, game->get_players(1 - game->get_turn()).second +
                                                                   game->get_ball(i)->get_point());
                    }
                }
                game->check_packets();
                game->set_players(1 - game->get_turn(), 1, game->get_players(1 - game->get_turn()).second + 4);
                game->set_turn(1 - game->get_turn());
                game->set_flag(false);
                table->set_flag(0);
                game->set_target_ball(-1);
            }
        } else if (table->get_flag() == 2 && game->get_flag()) {

            if (game->check_target_ball()) {
                for (int i = 0; i < game->get_new_in_packet().size(); i++) {
                    game->set_players(1 - game->get_turn(), 1, game->get_players(1 - game->get_turn()).second +
                                                               game->get_ball(i)->get_point());
                }
                game->check_packets();
                game->set_turn(1 - game->get_turn());
                game->set_flag(false);
                table->set_flag(0);
                game->set_target_ball(-1);
                game->clear_new_in_packet();
            } else {
                game->set_players(1 - game->get_turn(), 1, game->get_players(1 - game->get_turn()).second + 4);
                game->set_turn(1 - game->get_turn());
                game->set_flag(false);
                table->set_flag(0);
                game->set_target_ball(-1);
            }
        }
    }
}