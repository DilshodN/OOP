#pragma once

#include "game.h"
#include "settings.h"
#include "config_values.h"
#include "manual.h"

#include <SFML/Graphics.hpp>

class Menu final {
private:
    int chosen_option;

    const sf::Color checked = sf::Color::Red;
    const sf::Color unchecked = sf::Color::Black;

    Settings settings;
    Manual manual;
public:
    Menu();

    void run(sf::RenderWindow &window);

    void choose_option(sf::RenderWindow &window);
};

