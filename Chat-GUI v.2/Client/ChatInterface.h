#pragma once

#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>

class Client;
class ChatInterface : public Fl_Double_Window {
    Fl_Text_Display::Style_Table_Entry style_table[3];

    Fl_Text_Display *text_display;
    Fl_Text_Buffer *text_display_buffer;
    Fl_Text_Buffer *text_style_buffer;
    Fl_Button *send_button;

    static void SendButtonCallback(Fl_Widget *, void *);

    static void CloseWindowCallback(Fl_Widget *, void *);

public:
    Fl_Input *message_input;

    explicit ChatInterface(Client *);

    ~ChatInterface() override;

    void PrintMessage(std::string, char);
};

