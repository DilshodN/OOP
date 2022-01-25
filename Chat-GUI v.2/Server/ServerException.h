#pragma once

#include <exception>

class ServerException : public std::exception {
};

class CouldNotListen : public ServerException {
    const char *what() const noexcept override { return "Could not listen"; }
};

class ListenerError : public ServerException {
    const char *what() const noexcept override { return "Server listener error, restart the server"; }
};

class CouldNotSendPacketOnBroadcast : public ServerException {
    const char *what() const noexcept override { return "Could not send packet on broadcast"; }
};
