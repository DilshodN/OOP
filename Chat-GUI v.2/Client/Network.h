#pragma once

#include <thread>

#undef Status
#undef None
#undef BadRequest

#include <SFML/Network.hpp>
#include "Client.h"

class Client;
class Network {
    std::string address;
    sf::TcpSocket local_socket;
    std::thread receiver_thread;
    Client* client;
public:
    bool isConnected = false;
    std::string username;

    explicit Network(Client&);

    void Connect(const char *, unsigned short);

    void DisconnectThread();

    void Disconnect();

    bool Send(sf::Int8, const std::string &);

    bool Receive(sf::Packet &);

    void ReceivePackets(sf::TcpSocket *);

    void StartReceiving();
};
