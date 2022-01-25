#include "Client.h"
#include <FL/fl_ask.H>

Client::Client() = default;

void Client::Run() {
    network = new Network(*this);
//    std :: cout << "created Network" << std :: endl;

    interface_manager = new InterfaceManager(*this);
//    std :: cout << "created InterfaceManager" << std :: endl;

    interface_manager->ShowWindow(Address);
    Fl::lock();
}

Client::~Client() {
    delete(network);
//    std :: cout << "Delete Network" << std :: endl;

    delete(interface_manager);
//    std :: cout << "Delete Manager" << std :: endl;

//    std :: cout << "Delete Client" << std :: endl;
}

bool Client::Connect(const char *address) {
    network->isConnected = false;
    network->Connect(address, 2525);
    if (!network->isConnected) {
        fl_alert("Could not connect to the server.");
        return false;
    } else return true;
}


void Client::Login(const std::string &username, const std::string &password) {
    logl("Login Callback with parameters " << username << " " << password);
    network->username = username;

    if (network->isConnected) {
        network->Send(LOGIN | REQUEST, password);

        while (network->isConnected) {
            sf::Packet packet;
            sf::Int8 server_response;
            network->Receive(packet);
            packet >> server_response;

            if (server_response == (LOGIN | OK)) {
                ChatWindow();
                break;
            } else if (server_response == (LOGIN | FAIL)) {
                fl_alert("Invalid credentials. (Are you registered?)");
                break;
            }
        }
    } else fl_alert("Lost connection with the server.");
}


void Client::Register(std::string username, std::string password) {
    logl("Register Callback with parameters " << username << " " << password);
    network->username = username;

    if (network->isConnected) {
        network->Send(REGISTER | REQUEST, password);

        while (network->isConnected) {
            sf::Packet packet;
            sf::Int8 server_response;
            network->Receive(packet);
            packet >> server_response;

            if (server_response == (REGISTER | OK)) {
                ChatWindow();
                break;
            } else if (server_response == (REGISTER | FAIL)) {
                fl_alert("Server database error, the user may already be registered.");
                break;
            }
        }
    } else fl_alert("Lost connection with the server.");
}


void Client::Send(const std::string &message) {
    logl("Send Callback with parameters " << message);
    if (!network->Send(MESSAGE | REQUEST, message))
        fl_alert("Could not send the message.\nLost connection with the server.\nYou can close the program");
}


void Client::ProcessPacket(sf::Packet &packet) {
    sf::Int8 type;
    std::string sender_username, message;
    packet >> type >> sender_username >> message;

    logl("Received from " << sender_username << ": '" << message << "'");
    if (type == (MESSAGE | OK)) {
        interface_manager->chat_interface->PrintMessage(sender_username + ": " + message, 'A');
    } else if (type == (NOTIFICATION | OK)) {
        interface_manager->chat_interface->PrintMessage(message, 'C');
    }
}


void Client::ChatWindow() {
    interface_manager->ShowWindow(Chat);
    network->StartReceiving();
}


void Client::StopChat() {
    interface_manager->ShowWindow(Address);
    network->DisconnectThread();
}
