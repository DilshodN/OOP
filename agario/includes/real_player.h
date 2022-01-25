#pragma once

#include "player.h"
#include "config_values.h"

class RealPlayer final : public Player {
    sf::Color color = sf::Color::Red;
public:
    RealPlayer(float x, float y);

    explicit RealPlayer(std::shared_ptr<Cell> &cell);

    void set_mouse_position(sf::Vector2<int> position);

    [[maybe_unused]] std::vector<std::shared_ptr<Cell>> get_cells();

    std::vector<std::shared_ptr<Cell>> divide(sf::Vector2<int> mouse_position);
};