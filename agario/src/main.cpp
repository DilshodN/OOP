#include <iostream>
#include "../includes/menu.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "AgarIO");

    Menu menu;
    menu.run(window);
    return 0;
}
