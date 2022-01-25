#include "InterfaceManager.h"
#include "iostream"

namespace {
    void GetCenterPos(Fl_Widget *widget, int &x, int &y) {
        Fl::get_mouse(x, y);
        x -= widget->w() / 2;
        y -= widget->h() / 2;
    }
}

InterfaceManager::InterfaceManager(Client& data) {
    client = &data;
    address_interface = new AddressInterface(client);
//    std :: cout << "created address interface" << std :: endl;
    login_interface = new LoginInterface(client);
//    std :: cout << "created login interface" << std :: endl;

    register_interface = new RegisterInterface(client);
//    std :: cout << "created register interface" << std :: endl;

    chat_interface = new ChatInterface(client);
//    std :: cout << "created chat interface" << std :: endl;

}

InterfaceManager::~InterfaceManager() {
    delete(address_interface);
//    std :: cout << "deleted address interface" << std :: endl;

    delete(login_interface);
//    std :: cout << "deleted login interface" << std :: endl;

    delete(register_interface);
//    std :: cout << "deleted register interface" << std :: endl;

    delete(chat_interface);
//    std :: cout << "deleted chat interface" << std :: endl;

//    std :: cout << "deleted Interface Manager" << std :: endl;

}

void InterfaceManager::HideAll() {
    address_interface->hide();
    login_interface->hide();
    register_interface->hide();
    chat_interface->hide();
}

void InterfaceManager::ShowWindow(win w) {
    HideAll();
    int x, y;
    GetCenterPos(address_interface, x, y);
    switch (w){
        case Address:
            address_interface->position(x, y);
            address_interface->show();
            break;
        case Login:
            login_interface->position(x, y);
            login_interface->show();
            break;
        case Register:
            register_interface->position(x, y);
            register_interface->show();
            break;
        case Chat:
            chat_interface->position(x, y);
            chat_interface->show();
            break;
    }
}