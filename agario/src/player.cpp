#include "../includes/player.h"


[[maybe_unused]] Player::Player(float x, float y, double acceleration, int mass) {
    sf::Vector2<float> position(x, y);
    cells.push_back(std::make_shared<Cell>(position, acceleration, true, mass));
}

Player::Player(std::shared_ptr<Cell> &cell) {
    cells.push_back(cell);
}

void Player::set_color(sf::Color color) {
    for (auto &cell: cells) {
        cell->Unit::set_color(color);
    }
}

[[maybe_unused]] void Player::draw(sf::RenderWindow &window) {
    for (auto &cell: cells) {
        cell->Unit::draw(window);
    }
}

void Player::add_cell(std::shared_ptr<Cell> &cell) {
    cells.push_back(cell);
}

void Player::remove_cell(std::shared_ptr<Cell> &cell) {
    auto finding_cell = std::find(cells.begin(), cells.end(), cell);
    if (finding_cell != cells.end()) {
        cells.erase(finding_cell);
    }
}





