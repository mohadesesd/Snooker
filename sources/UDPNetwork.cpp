//
// Created by msd on 7/21/18.
//
#include <SFML/Network.hpp>
#include <SFML/Network/Socket.hpp>
#include <chrono>
#include <thread>
#include "../headers/UDPNetwork.h"
#include "../headers/network.h"

//to send and receive udp messages
UDPNetwork::UDPNetwork(int a) {

    if(a == 0)
    {
        Ip = sf::IpAddress::getLocalAddress().toString();
        Port = 55001;

    }
    else
    {
        Ip = sf::IpAddress::getLocalAddress().toString();
        Port = 55002;
    }
}

//to receive a udp message
void UDPNetwork::receivemessage() {
    sf::UdpSocket socket;
    socket.bind(55002);
    char buffer[1024] = "hi";
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    socket.receive(buffer, sizeof(buffer), received, sender, port);
    makeServersList(sender.toString(), port);
    cout << sender.toString() << "  " << port << "  said:  " << buffer << endl;
}

//to broad cast a message
void UDPNetwork::broadcast() {
    sf::UdpSocket socket;
    socket.bind(55001);
    std::string message =
            "Hi, I am " + sf::IpAddress::getLocalAddress().toString() + "  I want to play Game!any one there?";
    socket.send(message.c_str(), message.size() + 1, sf::IpAddress::Broadcast, 55002);
    cout << message << endl;
}

void UDPNetwork::makeServersList(string HostIp, unsigned int Hostport) {
    int flag = 0;
    for (int i = 0; i < this->list.size(); i++) {
        if (HostIp == this->list[i].first) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        pair<string, int> a;
        a.first = HostIp;
        a.second = Hostport;
        this->list.emplace_back(a);
    }
}

void UDPNetwork::ShowServesList() {
    for (int i = 0; i < this->list.size(); i++) {
        cout << "server's Ip is: " << this->list[i].first << " server's Port is: " << this->list[i].second << "\n";
    }
}

void UDPNetwork::chooseServer(string H, unsigned int P) {
    this->HostIp = H;
    this->HostPort = P;
}

string UDPNetwork::get_Host_IP() {
    return this->HostIp;
}
