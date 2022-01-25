#pragma once

#include <exception>

class ClientException : public std::exception {
};

class CouldNotConnectToServerException : public ClientException {
    const char *what() const noexcept override { return "Could not connect to the server\n"; }
};

class CouldNotSendPacketException : public ClientException {
    const char *what() const noexcept override { return "Could not send packet\n"; }
};
