#pragma once

#include <iostream>

#include "Network.h"
#include "InterfaceManager.h"

#include "Standard.h"

#define logl(x) std::cout << x << std::endl

class Network;
class InterfaceManager;

class Client {
public:
    Network *network;
    InterfaceManager *interface_manager;

    Client();

    ~Client();

    void Run();

    bool Connect(const char *);

    void Login(const std::string &, const std::string &);

    void Register(std::string, std::string);

    void Send(const std::string &);

    void ProcessPacket(sf::Packet &);

    void ChatWindow();

    void StopChat();
};