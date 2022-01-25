#pragma once

#include "player.h"
#include <random>

class Bot final : public Player {
private:
    std::vector<std::shared_ptr<Cell>> bot_cells;
public:
    Bot() = default;

    [[maybe_unused]] Bot(float x, float y);

    [[maybe_unused]] explicit Bot(std::shared_ptr<Cell> &cell);

    ~Bot() override = default;

    [[maybe_unused]] std::vector<std::shared_ptr<Cell>> get_bot_cells();

    [[maybe_unused]] void set_next_position(std::vector<std::shared_ptr<Unit>> &feed_units,
                                            std::vector<std::shared_ptr<Cell>> &cells);
};