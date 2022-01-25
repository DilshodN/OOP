#pragma once

#include "config_values.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Settings final {
private:
    const int num_of_options = 3;

    const int settings_window_width = 700;
    const int setting_window_height = 700;

    int chosen_option;

    const sf::Color checked = sf::Color::Red;
    const sf::Color unchecked = sf::Color::Black;

public:
    Settings();

    void run();

    void choose_option() const;

    static void load_font(sf::Font &font);

    static void load_background(sf::Sprite &background, const std::string &path);

    static sf::Text make_text(const std::string &string, const sf::Font &font, const unsigned int &font_size);
};