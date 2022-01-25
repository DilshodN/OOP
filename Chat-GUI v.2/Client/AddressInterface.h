#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>

class Client;

class AddressInterface : public Fl_Double_Window {
    Fl_Return_Button* connect_button;
    static void ConnectButtonCallback(Fl_Widget *, void*); // так в библиотеке
public:
    Fl_Input* address_input;
    explicit AddressInterface(Client*);
    ~AddressInterface() override;
};


