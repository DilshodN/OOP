#pragma once

#include "cell.h"
#include <vector>

class Player {
public:
    std::vector<std::shared_ptr<Cell>> cells;

    Player() = default;

    [[maybe_unused]] Player(float x, float y, double acceleration, int mass);

    explicit Player(std::shared_ptr<Cell> &cell);

    virtual ~Player() = default;

    void set_color(sf::Color color);

    [[maybe_unused]] void draw(sf::RenderWindow &window);

    void add_cell(std::shared_ptr<Cell> &cell);

    void remove_cell(std::shared_ptr<Cell> &cell);
};