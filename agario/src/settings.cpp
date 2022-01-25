#include "../includes/settings.h"


Settings::Settings() {
    chosen_option = LEVEL - 1;
}

void Settings::load_background(sf::Sprite &background, const std::string &path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Error loading of a image in settings" << std::endl;
    }
    background.setTexture(texture);
}

void Settings::load_font(sf::Font &font) {
    if (!font.loadFromFile("../fonts/Storystone.ttf")) {
        std::cerr << "Error loading of a font" << std::endl;
    }
}

sf::Text Settings::make_text(const std::string &string, const sf::Font &font, const unsigned int &font_size) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(font_size);
    text.setString(string);
    return text;
}

void Settings::run() {
    sf::RenderWindow window(sf::VideoMode(settings_window_width, setting_window_height), "Settings");

    sf::Sprite background;
    load_background(background, "../images/background_menu.png");

    sf::Font font;
    load_font(font);

    sf::Text settings_text_easy = make_text("Easy", font, 40);
    settings_text_easy.setPosition({static_cast<float>(settings_window_width * 5 / 12),
                                    static_cast<float>(setting_window_height * 3 / 12)});

    sf::Text settings_text_medium = make_text("Medium", font, 40);
    settings_text_medium.setPosition({static_cast<float>(settings_window_width * 5 / 12),
                                      static_cast<float>(setting_window_height * 5 / 12)});

    sf::Text settings_text_hard = make_text("Hard", font, 40);
    settings_text_hard.setPosition({static_cast<float>(settings_window_width * 5 / 12),
                                    static_cast<float>(setting_window_height * 7 / 12)});

    sf::Event event{};
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Down:
                        chosen_option = (chosen_option + 1) % num_of_options;
                        break;
                    case sf::Keyboard::Up:
                        chosen_option = (((chosen_option - 1) % num_of_options) + num_of_options) % num_of_options;
                        break;
                    case sf::Keyboard::Return:
                        choose_option();
                        return;
                    default:
                        break;

                }
            }
            // Управление мышкой
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i position = sf::Mouse::getPosition(window);

                if (position.x > settings_window_width * 2 / 5 && position.x < settings_window_width * 7 / 10) {
                    if (position.y > setting_window_height * 4 / 15 && position.y < setting_window_height / 3) {
                        chosen_option = 0;
                        choose_option();
                        return;
                    } else if (position.y > setting_window_height * 32 / 75 && position.y < setting_window_height / 2) {
                        chosen_option = 1;
                        choose_option();
                        return;
                    } else if (position.y > setting_window_height * 3 / 5 &&
                               position.y < setting_window_height * 2 / 3) {
                        chosen_option = 2;
                        choose_option();
                        return;
                    }

                }
            }
        }
        switch (chosen_option) {
            case 0:
                settings_text_easy.setFillColor(checked);
                settings_text_medium.setFillColor(unchecked);
                settings_text_hard.setFillColor(unchecked);
                break;
            case 1:
                settings_text_easy.setFillColor(unchecked);
                settings_text_medium.setFillColor(checked);
                settings_text_hard.setFillColor(unchecked);
                break;
            case 2:
                settings_text_easy.setFillColor(unchecked);
                settings_text_medium.setFillColor(unchecked);
                settings_text_hard.setFillColor(checked);
                break;
            default:
                break;
        }

        window.clear(sf::Color(10, 10, 10));
        window.draw(background);
        window.draw(settings_text_easy);
        window.draw(settings_text_medium);
        window.draw(settings_text_hard);
        window.display();
    }
}

void Settings::choose_option() const {
    LEVEL = chosen_option + 1;
}






