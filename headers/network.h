//
// Created by msd on 7/18/18.
//

#ifndef BILLIARD_NETWORK_H
#define BILLIARD_NETWORK_H

#include "resource.h"
#include <SFML/Network.hpp>


class Network {
public:
//    Network(Resource* resource);
    Network(Resource *resource, int a, std::string ip);

    void send();

    void receive();

    void listen();

    void connect();

    void accept();

private:
    Resource *resource;
    bool is_server;
    std::string ip;
    sf::TcpListener *listener;
    sf::TcpSocket *socket;
};

#endif //BILLIARD_NETWORK_H
