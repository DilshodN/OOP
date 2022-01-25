#include "../includes/manual.h"

void Manual::run() const {
    sf::RenderWindow window(sf::VideoMode(manual_window_width, manual_window_height), "Help");

    sf::Sprite background;
    Settings::load_background(background, "../images/background_menu.png");

    sf::Font font;
    Settings::load_font(font);

    sf::Text ManualText = Settings::make_text("Press M to go to the Menu\n"
                                              "Press Space to Split bacteria\n", font, 40);
    ManualText.setFillColor(sf::Color::Black);
    ManualText.setPosition({static_cast<float>(manual_window_width / 12),
                            static_cast<float>(manual_window_height * 5 / 12)});
    sf::Event event{};
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            window.clear(sf::Color(10, 10, 10));
            window.draw(background);
            window.draw(ManualText);
            window.display();
        }
    }
}
