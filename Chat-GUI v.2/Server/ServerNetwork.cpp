#include "ServerNetwork.h"
#include "Server.h"
#include "ServerException.h"


ServerNetwork::ServerNetwork() = default;

void ServerNetwork::Initialize(Server& data) {
    server = &data;
    state = true;
}

void ServerNetwork::Listen(unsigned short port) {
    logl("Chat Server Started");
    logl("Print [ !q ] to terminate server");
    if (listener.listen(port) != sf::Socket::Done) throw CouldNotListen();
}

void ServerNetwork::ConnectClients(std::vector<sf::TcpSocket *> *client_array) {
    while (state) {
        auto* new_client = new sf::TcpSocket();
        if (listener.accept(*new_client) == sf::Socket::Done) {
            new_client->setBlocking(false);
            client_array->push_back(new_client);
            logl("Added client " << new_client->getRemoteAddress() << ":" << new_client->getRemotePort() << " on slot "
                                 << client_array->size());
        } else {
            delete (new_client);
            throw ListenerError();
        }
    }
}

void ServerNetwork::DisconnectClient(sf::TcpSocket* socket_ptr, size_t position) {
    logl("Client " << socket_ptr->getRemoteAddress() << ":" << socket_ptr->getRemotePort()
                   << " disconnected, removing");
    server->SendNotification("User " + socket_ptr->getRemoteAddress().toString() + " disconnected.", true,
                             socket_ptr->getRemoteAddress(), socket_ptr->getRemotePort());
    socket_ptr->disconnect();
    delete client_array[position];
    client_array.erase(client_array.begin() + position);
}

bool ServerNetwork::SendPacket(sf::TcpSocket* socket, sf::Int8 type) {
    sf::Packet packet;
    packet << type;

    return socket->send(packet) == sf::Socket::Done;
}


void ServerNetwork::BroadcastPacket(sf::Packet &packet, sf::IpAddress exclude_address, unsigned short port) {
    if (packet.getDataSize() > 0) {
        for (auto client : client_array) {
            if (client->getRemoteAddress() != exclude_address || client->getRemotePort() != port) {
                if (client->send(packet) != sf::Socket::Done) {
                    throw CouldNotSendPacketOnBroadcast();
                }
            }
        }
    }
}


void ServerNetwork::BroadcastPacket(sf::Packet &packet) {
    if (packet.getDataSize() > 0) {
        for (auto client : client_array) {
            if (client->send(packet) != sf::Socket::Done) {
                throw CouldNotSendPacketOnBroadcast();
            }
        }
    }
}

void ServerNetwork::ReceivePacket(sf::TcpSocket *client, size_t iterator) {
    sf::Packet packet;

    sf::Socket::Status status = client->receive(packet);
    if (status == sf::Socket::Disconnected) {
        DisconnectClient(client, iterator);
    } else if (status == sf::Socket::Done) {
        server->ProcessPacket(client, packet);
    }
}


void ServerNetwork::ManagePackets() {
    while (state) {
        for (size_t iterator = 0; iterator < client_array.size(); iterator++)
            ReceivePacket(client_array[iterator], iterator);
        std::this_thread::sleep_for((std::chrono::milliseconds) 10);
    }
}

void ServerNetwork ::ShutDown() {
    std :: string temp;
    while(state) {
        if(std :: cin >> temp){
            if(temp == "!q"){
                logl("ShutDown...");
                for (size_t iterator = 0; iterator < client_array.size(); iterator++) {
                    DisconnectClient(client_array[iterator], iterator);
                    std::this_thread::sleep_for((std::chrono::milliseconds) 10);
                }
                state = false;
            }
        }
    }
    logl("Complete!");
}

bool ServerNetwork::State() {
    return state;
}

void ServerNetwork::Run() {
    std::thread connection_thread(&ServerNetwork::ConnectClients, this, &client_array);
    connection_thread.detach();
    std::thread terminate_thread(&ServerNetwork :: ShutDown, this);
    ManagePackets();
    terminate_thread.join();
}
