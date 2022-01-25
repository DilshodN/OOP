#include "../includes/game.h"

Game::Game(sf::RenderWindow &window) {
    window.setFramerateLimit(FPS);
    sf::Vector2<unsigned int> size = window.getSize();
    board = std::make_shared<Board>(size);
    sf::Texture texture;
    if (!texture.loadFromFile("../images/background_game.png")) {
        std::cerr << "Can't download background image of a game" << std::endl;
    }
    sf::Sprite background(texture);
    if (!load()) {
        player = std::make_shared<RealPlayer>(size.x / 2, size.y / 2);
        cells.push_back(player->cells[0]); // 1st cell
    } else {
        player = nullptr;
        for (auto &cell: cells) {
            cell->set_acceleration(0);
            if (cell->is_it_player()) {
                if (not player) {
                    player = std::make_shared<RealPlayer>(cell);
                } else {
                    player->add_cell(cell);
                }
            }
        }
        remove("bin/save");
    }

    window.clear();
    window.display();
    clock.restart();
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                save();
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::M:
                        save();
                        window.clear();
                        return;
                    case sf::Keyboard::Space:
                        for (auto &cell: player->divide(sf::Mouse::getPosition(window))) {
                            cells.push_back(cell);
                        }
                        break;
                    default:
                        break;
                }
            } else if (event.type == sf::Event::Resized) {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                WINDOW_HEIGHT = window.getSize().x;
                WINDOW_HEIGHT = window.getSize().y;
            }
        }
        window.clear();
        window.draw(background);
        sleep(sf::milliseconds(2));

        step(window);
        window.display();


        double maxRadius = 0;
        for (auto &cell: cells) {
            maxRadius = std::max(maxRadius, static_cast<double>(cell->get_radius()));
        }

        if (player->cells.empty() || maxRadius >= std::min(WINDOW_HEIGHT, WINDOW_WIDTH) / 3 || maxRadius == 0) {
            game_over(window);
            break;
        }
    }
}

sf::Vector2<float> Game::find_place() {
    return {static_cast<float>(f_rand(0.0, board->get_size().x)),
            static_cast<float>(f_rand(0.0, board->get_size().y))};
}

double Game::f_rand(double fMin, double fMax) {
    double f = (double) std::rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void Game::step(sf::RenderWindow &window) {
    while (feed_units.size() < MAX_NUMBER_OF_FEED_UNITS) {
        auto u = std::make_shared<Unit>(find_place(), 1);
        feed_units.push_back(u);
    }

    while (bots.size() + 1 < MAX_NUMBER_OF_PLAYERS) {
        auto _bot = std::make_shared<Bot>(find_place().x, find_place().y);
        bots.push_back(_bot);
        cells.push_back(_bot->get_bot_cells()[0]);
    }


    sf::Vector2<int> position = sf::Mouse::getPosition(window);
    player->set_mouse_position(position);
    sf::Time time = clock.getElapsedTime();
    clock.restart();
    update(time);
    board->draw(window, cells, feed_units);
}

void Game::update(sf::Time time) {
    std::vector<std::shared_ptr<Cell>> cellsToDelete;
    for (auto cell = cells.begin(); cell != cells.end(); ++cell) {
        for (auto unit = feed_units.begin(); unit != feed_units.end(); ++unit) {
            if ((*cell)->distance(*(*unit)) <= (*cell)->get_radius()) {
                (*cell)->grow((*unit)->get_mass());
                feed_units.erase(unit);
                --unit;
            }
        }

        for (auto cell2 = cell + 1; cell2 != cells.end(); ++cell2) {
            if ((*cell)->distance(*(*cell2)) <= (*cell)->get_radius()) {
                if ((*cell)->get_mass() > (*cell2)->get_mass()) {
                    if ((*cell2)->is_it_player()) {
                        player->remove_cell((*cell2));
                    } else {
                        for (auto &_bot: bots) {
                            if (_bot->get_bot_cells()[0] == (*cell2)) {
                                delete_bot(_bot);
                            }
                        }
                    }

                    (*cell)->grow((*cell2)->get_mass() / 2);
                    cellsToDelete.push_back(*cell2);
                    cells.erase(cell2);
                    --cell2;
                }
            } else if ((*cell2)->distance(*(*cell)) <= (*cell2)->get_radius()) {
                if ((*cell)->get_mass() < (*cell2)->get_mass()) {
                    if ((*cell)->is_it_player()) {
                        player->remove_cell((*cell));
                    } else {
                        for (auto _bot: bots) {
                            if (_bot->get_bot_cells()[0] == (*cell)) {
                                delete_bot(_bot);
                            }
                        }
                    }

                    (*cell2)->grow((*cell)->get_mass() / 2);
                    cellsToDelete.push_back(*cell);
                }
            }
        }
    }

    for (auto &cell: cellsToDelete) {
        delete_cell(cell);
    }

    for (const auto &_bot: bots) {
        _bot->set_next_position(feed_units, cells);
    }
}

void Game::save() const {
    std::ofstream myfile;
    myfile.open("bin/save");
    myfile << *this;
    myfile.close();
}

bool Game::load() {
    std::ifstream myfile;
    myfile.open("bin/save");
    if (!myfile) {
        return false;
    }
    myfile >> *this;
    myfile.close();
    return true;
}

void Game::game_over(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);
}

void Game::add_cell(std::shared_ptr<Cell> &cell) {
    cells.push_back(cell);
}

void Game::add_bot(std::shared_ptr<Bot> &_bot) {
    bots.push_back(_bot);
}

void Game::delete_cell(std::shared_ptr<Cell> &cell) {
    auto finding_cell = std::find(cells.begin(), cells.end(), cell);
    if (finding_cell != cells.end()) {
        cells.erase(finding_cell);
    }
}

void Game::delete_bot(std::shared_ptr<Bot> &_bot) {
    auto finding_bot = std::find(bots.begin(), bots.end(), bot);
    if (finding_bot != bots.end()) {
        bots.erase(finding_bot);
    }
}

std::ostream &operator<<(std::ostream &stream, const Game &game) {
    stream << game.cells.size() << std::endl;
    for (const auto &cell: game.cells) {
        stream << cell->is_it_player() << std::endl;
        stream << *cell << std::endl;
    }
    stream << game.feed_units.size() << std::endl;
    for (const auto &feed_unit: game.feed_units) {
        stream << *feed_unit << std::endl;
    }
    return stream;

}

std::istream &operator>>(std::istream &stream, Game &game) {
    unsigned int cellsSize;
    stream >> cellsSize;
    for (unsigned int i = 0; i < cellsSize; ++i) {
        bool isPlayer;
        stream >> isPlayer;
        auto cell = std::make_shared<Cell>();
        stream >> *cell;
        if (isPlayer) {
            cell->set_as_player();
            game.add_cell(cell);
        } else {
            auto bot = std::make_shared<Bot>(cell->get_position().x, cell->get_position().y);
            bot->get_bot_cells()[0]->set_mass(cell->get_mass());
            game.add_cell(bot->get_bot_cells()[0]);
            game.add_bot(bot);
        }
    }

    unsigned int feedUnitsSize;
    stream >> feedUnitsSize;
    for (unsigned int i = 0; i < feedUnitsSize; ++i) {
        auto unit = std::make_shared<Unit>();
        game.feed_units.push_back(unit);
        stream >> *game.feed_units[i];
    }

    return stream;

}


