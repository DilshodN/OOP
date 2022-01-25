#pragma once

#include "AddressInterface.h"
#include "LoginInterface.h"
#include "RegisterInterface.h"
#include "ChatInterface.h"

enum win{
    Address,
    Login,
    Register,
    Chat
};

class Client;
class InterfaceManager {
public:
    Client* client;
    AddressInterface *address_interface;
    LoginInterface *login_interface;
    RegisterInterface *register_interface;
    ChatInterface *chat_interface;

    explicit InterfaceManager(Client& data);

    ~InterfaceManager();

    void HideAll();

    void ShowWindow(win);
};