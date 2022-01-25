#pragma once

#include "real_player.h"
#include "bot.h"
#include "player.h"
#include "board.h"
#include "unit.h"
#include "config_values.h"
#include <fstream>

class Game final{
private:
    std::shared_ptr<RealPlayer> player;
    std::shared_ptr<Bot> bot;
    std::vector<std::shared_ptr<Bot>> bots;
    std::vector<std::shared_ptr<Unit>> feed_units;
    std::vector<std::shared_ptr<Cell>> cells;
    std::shared_ptr<Board> board;
    sf::Clock clock;
public:
    Game() = default;

    explicit Game(sf::RenderWindow &window);

    ~Game() = default;

    sf::Vector2<float> find_place();

    static double f_rand(double fMin, double fMax);

    void step(sf::RenderWindow &window);

    void update(sf::Time time);

    void save() const;

    bool load();

    void game_over(sf::RenderWindow &window);

    void add_cell(std::shared_ptr<Cell>& cell);

    void add_bot(std::shared_ptr<Bot>& bot);

    void delete_cell(std::shared_ptr<Cell>& cell);

    void delete_bot(std::shared_ptr<Bot>& bot);

    friend std::ostream &operator<<(std::ostream &stream, const Game &game);

    friend std::istream &operator>>(std::istream &stream, Game &game);
};