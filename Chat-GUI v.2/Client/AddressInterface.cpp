#include "AddressInterface.h"
#include "Client.h"


namespace address_ui{
    Client* client;
}

AddressInterface::AddressInterface(Client* data) : Fl_Double_Window(261, 90, "Connect Window") {
    address_ui::client = data;

    address_input = new Fl_Input(90, 15, 125, 25, "Address");
    address_input->value("localHost");

    connect_button = new Fl_Return_Button(95, 50, 90, 25, "Connect");
    connect_button->callback(ConnectButtonCallback);
    this->end();
}

AddressInterface::~AddressInterface() {
    delete(address_input);
    delete(connect_button);
}

void AddressInterface::ConnectButtonCallback(Fl_Widget *, void*) {

    if (address_ui::client->Connect(address_ui::client->interface_manager->address_interface->address_input->value())) {
        address_ui::client->interface_manager->ShowWindow(Login);
    }
}