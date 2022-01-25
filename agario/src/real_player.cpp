#include "../includes/real_player.h"

RealPlayer::RealPlayer(float x, float y) : Player(x, y, 0, BASIC_PLAYER_MASS) {
    set_color(color);
}

RealPlayer::RealPlayer(std::shared_ptr<Cell> &cell) : Player(cell) {
    set_color(color);
}

void RealPlayer::set_mouse_position(sf::Vector2<int> position) {
    for (auto &cell: cells) {
        sf::Vector2<float> cell_position = cell->get_position();
        float length = hypot(static_cast<float>(position.x) - cell_position.x,
                             static_cast<float>(position.y) - cell_position.y);
        float x = (static_cast<float>(position.x) - cell_position.x) / length;
        float y = (static_cast<float>(position.y) - cell_position.y) / length;
        cell->set_direction(x, y);
        cell->update();
    }
}

std::vector<std::shared_ptr<Cell>> RealPlayer::divide(sf::Vector2<int> mousePosition) {
    std::vector<std::shared_ptr<Cell>> new_cells;

    for (auto &cell: cells) {
        if (cell->get_mass() > MIN_MASS_OF_PLAYER) {
            new_cells.push_back(cell->division(mousePosition));
        }
    }

    for (auto &cell: new_cells) {
        cell->set_as_player();
        cells.push_back(cell);
    }

    return new_cells;
}

[[maybe_unused]] std::vector<std::shared_ptr<Cell>> RealPlayer::get_cells() {
    return cells;
}
