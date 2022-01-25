#include "../includes/board.h"

Board::Board(sf::Vector2<unsigned int> size) : size(size) {}

sf::Vector2<unsigned int> Board::get_size() const {
    return size;
}

[[maybe_unused]] void Board::set_size(sf::Vector2<unsigned int> new_size) {
    size = new_size;
}

void Board::draw(sf::RenderWindow &window, std::vector<std::shared_ptr<Cell>> &cells,
                 std::vector<std::shared_ptr<Unit>> &feed_units) {
    if (window.getSize() != size) {
        size = window.getSize();
    }
    for (auto &cell: cells) {
        cell->draw(window);
    }
    for (auto &unit: feed_units) {
        unit->draw(window);
    }
}


