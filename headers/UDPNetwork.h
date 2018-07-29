//
// Created by msd on 7/21/18.
//

#ifndef BILLIARD_UDPNETWORK_H
#define BILLIARD_UDPNETWORK_H

#include<iostream>
#include<vector>
#include "resource.h"
#include "network.h"

using namespace std;

class UDPNetwork {
public:
    explicit UDPNetwork(int a);

    void receivemessage();

    static void broadcast();

    void makeServersList(string HostIp, unsigned int Hostport);

    void ShowServesList();

    void chooseServer(string H, unsigned int P);

    string get_Host_IP();

private:
    string HostIp;
    string Ip;
    unsigned int Port;
    unsigned int HostPort;
    vector<pair<string, unsigned int>> list;

};
#endif //BILLIARD_UDPNETWORK_H
