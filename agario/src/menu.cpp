#include "../includes/menu.h"

Menu::Menu() {
    chosen_option = 0;
}

void Menu::run(sf::RenderWindow &window) {
    sf::Sprite background;
    sf::Texture texture;
    texture.loadFromFile("../images/background_menu.png");
    background.setTexture(texture);

    sf::Font font;
    Settings::load_font(font);

    sf::Text menuTextLogo = Settings::make_text("AgarIO", font, 80);
    menuTextLogo.setFillColor(sf::Color::Black);
    menuTextLogo.setPosition({static_cast<float>(WINDOW_WIDTH * 4 / 11),
                              static_cast<float>(WINDOW_WIDTH * 2 / 12)});


    sf::Text menuTextPlay = Settings::make_text("Play", font, 40);
    menuTextPlay.setPosition(
            {static_cast<float>(WINDOW_WIDTH * 5 / 11), static_cast<float>(WINDOW_WIDTH * 4 / 12)});

    sf::Text menuTextLoad = Settings::make_text("Load Game", font, 40);;
    menuTextLoad.setPosition(
            {static_cast<float>(WINDOW_WIDTH * 5 / 11), static_cast<float>(WINDOW_WIDTH * 5 / 12)});

    sf::Text menuTextSettings = Settings::make_text("Settings", font, 40);;
    menuTextSettings.setPosition(
            {static_cast<float>(WINDOW_WIDTH * 5 / 11), static_cast<float>(WINDOW_WIDTH * 6 / 12)});

    sf::Text menuTextManual = Settings::make_text("Help", font, 40);
    menuTextManual.setPosition(
            {static_cast<float>(WINDOW_WIDTH * 5 / 11), static_cast<float>(WINDOW_WIDTH * 7 / 12)});


    sf::Event event{};
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Down:
                        chosen_option = (chosen_option + 1) % 4;
                        break;
                    case sf::Keyboard::Up:
                        chosen_option = (((chosen_option - 1) % 4) + 4) % 4;
                        break;
                    case sf::Keyboard::Return:
                        choose_option(window);
                    default:
                        break;
                }
            } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i position = sf::Mouse::getPosition(window);

                if (position.x > WINDOW_WIDTH * 9 / 20 && position.x < WINDOW_WIDTH * 2 / 3) {
                    if (position.y > WINDOW_HEIGHT / 3 && position.y < WINDOW_HEIGHT * 23 / 60) {
                        chosen_option = 0;
                        choose_option(window);
                    } else if (position.y > WINDOW_HEIGHT * 5 / 12 && position.y < WINDOW_HEIGHT * 7 / 15) {
                        chosen_option = 1;
                        choose_option(window);
                    } else if (position.y > WINDOW_HEIGHT / 2 && position.y < WINDOW_HEIGHT * 11 / 20) {
                        chosen_option = 2;
                        choose_option(window);
                    } else if (position.y > WINDOW_HEIGHT / 2 && position.y < WINDOW_HEIGHT * 15 / 20) {
                        chosen_option = 3;
                        choose_option(window);
                    }
                }
            }
        }
        // -__-
        switch (chosen_option) {
            case 0:
                menuTextPlay.setFillColor(checked);
                menuTextLoad.setFillColor(unchecked);
                menuTextSettings.setFillColor(unchecked);
                menuTextManual.setFillColor(unchecked);
                break;
            case 1:
                menuTextPlay.setFillColor(unchecked);
                menuTextLoad.setFillColor(checked);
                menuTextSettings.setFillColor(unchecked);
                menuTextManual.setFillColor(unchecked);
                break;
            case 2:
                menuTextPlay.setFillColor(unchecked);
                menuTextLoad.setFillColor(unchecked);
                menuTextSettings.setFillColor(checked);
                menuTextManual.setFillColor(unchecked);
                break;
            case 3:
                menuTextPlay.setFillColor(unchecked);
                menuTextLoad.setFillColor(unchecked);
                menuTextSettings.setFillColor(unchecked);
                menuTextManual.setFillColor(checked);
            default:
                break;
        }
        window.clear(sf::Color::Black);
        window.draw(background);
        window.draw(menuTextLogo);
        window.draw(menuTextPlay);
        window.draw(menuTextLoad);
        window.draw(menuTextSettings);
        window.draw(menuTextManual);
        window.display();
    }

}

void Menu::choose_option(sf::RenderWindow &window) {
    switch (chosen_option) {
        case 0: {
            remove("bin/save");
            Game game(window);
            break;
        }
        case 1: {
            Game game(window);
            break;
        }
        case 2: {
            settings.run();
            break;
        }
        case 3: {
            manual.run();
            break;
        }
        default:
            break;
    }
}
