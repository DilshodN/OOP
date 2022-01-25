#pragma once

#include "cell.h"
#include "unit.h"
#include "bot.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Board final {
private:
    sf::Vector2<unsigned int> size;
public:
    Board() = default;

    explicit Board(sf::Vector2<unsigned int> size);

    ~Board() = default;

    [[nodiscard]] sf::Vector2<unsigned int> get_size() const;

    [[maybe_unused]] void set_size(sf::Vector2<unsigned int> new_size);

    void draw(sf::RenderWindow &window, std::vector<std::shared_ptr<Cell>> &cells,
              std::vector<std::shared_ptr<Unit>> &feed_units);
};