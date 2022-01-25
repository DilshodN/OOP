#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_ask.H>

class Client;

class LoginInterface : public Fl_Double_Window {
    Fl_Return_Button *login_button;
    Fl_Button *register_button;

    static void LoginButtonCallback(Fl_Widget *, void *); // так требует библиотека

    static void OpenRegisterWindowButtonCallback(Fl_Widget *, void *); // так требует библиотека

    static void CloseLoginWindowCallback(Fl_Widget *, void *); // так требует библиотека

public:
    Fl_Input *username_input;
    Fl_Secret_Input *password_input;

    explicit LoginInterface(Client*);
    ~LoginInterface();
};


