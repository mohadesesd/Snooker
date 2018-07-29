//
// Created by msd on 7/18/18.
//

#include "../headers/network.h"
#include <SFML/Network.hpp>
#include <iostream>

//constructor of network class get the resource and ip
Network::Network(Resource *resource,int a, std::string ip) {
    if (a == 0) {
        this->resource = resource;
        this->is_server = true;
        this->ip = ip;
        this->listener = new sf::TcpListener;
        listener->listen(12345);
    } else {
        this->resource = resource;
        this->is_server = false;
        this->ip = ip;
    }
}

//listen function to listen for a TCP connection
void Network::listen() {
    if (this->is_server) {
        this->socket = new sf::TcpSocket;
    }
}

//connect fuction to connect a TCP connection
void Network::connect() {
    if (not this->is_server) {
        this->socket = new sf::TcpSocket;
        this->socket->connect(this->ip, 12345);
    }
}

//send function to send a message via TCP connection
void Network::send() {
    std::string message = this->resource->get();
    char *c_message = new char[(int) message.size() + 1];

    for (int i = 0; i < message.size(); i++)
        c_message[i] = message[i];

    this->socket->send(c_message, (int) message.size());
    delete c_message;
}

//recieve function to recieve a message via TCP connection
void Network::receive() {
    char data[1000];
    size_t received;

    this->socket->receive(data, 1000, received);

    if (received != 0) {
        std::string message = std::string(data);

        this->resource->set(message);
    }
}

//accept to accept TCP connection
void Network::accept() {
    this->listener->accept(*this->socket);

}
