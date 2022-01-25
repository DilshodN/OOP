#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>

class Client;
class RegisterInterface : public Fl_Double_Window {
    Fl_Return_Button *register_button;

    static void RegisterButtonCallback(Fl_Widget *, void *);

    static void CloseRegisterWindowCallback(Fl_Widget *, void *);
public:
    Fl_Input *username_input;
    Fl_Input *password_input;
    Fl_Input *repeat_password_input;

    explicit RegisterInterface(Client *);
    ~RegisterInterface() override;
};

