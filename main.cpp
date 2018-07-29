//#include <string>
//#include <iostream>
//#include <SFML/Network.hpp>
//
//using namespace std;
//int main(){
//    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
//    sf::UdpSocket socket;
//    char connectionType, mode;
//    char buffer[2000];
//    size_t received; //based in the amount of data we recieved
//    std::map<unsigned short, sf::IpAddress> computerID;
//    std::string text = "connected to: ";
//
//    cout<<"enter s for server enter c for client" << endl;
//    cin>> connectionType;
//    unsigned short port;
//    std::cout<< "set port number " ;
//    cin >>port;
//
//    socket.bind(port); //it's listening on that port
//    if(connectionType == 's'){
//        char answer = 'b';
//        while(answer != 'a' ){
//            sf::IpAddress rIp;
//            unsigned short port;
//            socket.receive(buffer, sizeof(buffer), received, rIp, port);
//            if(received>0)
//                computerID[port] = rIp;
//            cin >>answer;
//        }
//    }
//    else {
//        std::string sIP;
//        std::cout << "enter server ip: ";
//        std::cin>> sIP;
//        sf::IpAddress sendIP(sIP);
//        socket.send(text.c_str(), text.length()+1, sendIP, 2000);
//    }
//    bool done = true;
//    while(done){
//        if(connectionType == 's'){
//            std::getline(cin, text);
//            std::map<unsigned short, sf::IpAddress>::iterator tempIterator;
//            for(tempIterator = computerID.begin(); tempIterator != computerID.end(); tempIterator ++)
//                socket.send(text.c_str(), text.length()+1, tempIterator->second,tempIterator->first );
//        }
//        else{
//            sf::IpAddress tempIp;
//            unsigned short tempPort;
//            socket.receive(buffer, sizeof(buffer), received, tempIp, tempPort);
//            if(received>0)
//                std::cout << "received: " << buffer <<std::endl;
//        }
//
//    }
//    system("pause");
///
// /}
#include <thread>
#include<iostream>

class Task
{
public:
    void execute(std::string command)
    {
        for(int i = 0; i < 5; i++)
        {
            std::cout<<command<<" :: "<<i<<std::endl;
        }
    }

};

int main()
{
    Task * taskPtr = new Task();

    // Create a thread using member function
    std::thread th(&Task::execute, taskPtr, "Sample Task");

    th.join();

    delete taskPtr;
    return 0;
}