#include "../includes/bot.h"

Bot::Bot(float x, float y) {
    sf::Vector2<float> position(x, y);
    // Масса ботов зависит от уровня
    bot_cells.push_back(std::make_shared<Cell>(position, 0, false, (60 * LEVEL * 2)));
}

[[maybe_unused]] Bot::Bot(std::shared_ptr<Cell> &cell) {
    bot_cells.push_back(cell);
}

[[maybe_unused]] std::vector<std::shared_ptr<Cell>> Bot::get_bot_cells() {
    return bot_cells;
}

[[maybe_unused]] void Bot::set_next_position(std::vector<std::shared_ptr<Unit>> &feed_units,
                                             std::vector<std::shared_ptr<Cell>> &cells) {
    // самая тупая реализация AI для ботов
    // суть: бот ищет, что покушать и убегает от "больших" бактерий
    double x = 0, y = 0;
    double x_second_cell_bigger, y_second_cell_bigger;
    double x_second_cell_smaller = 20000, y_second_cell_smaller = 20000;
    for (auto &cell: bot_cells) {
        double length = 1000; // минимальный радиус поиска жертвы
        double nearest_bigger = 1000, nearest_smaller = 1000;
        double temp_nearest_bigger_size, temp_nearest_smaller_size;
        double temp_biggest_smaller = 0;
        for (auto &feed_unit: feed_units) {
            auto temp_x = feed_unit->get_position().x - cell->get_position().x;
            auto temp_y = feed_unit->get_position().y - cell->get_position().y;

            double new_length = hypot(temp_x, temp_y);
            if (new_length < length) {
                length = new_length;
                x = temp_x;
                y = temp_y;
            }
        }
        for (auto &second_cell: cells) {
            auto temp_x = second_cell->get_position().x - cell->get_position().x;
            auto temp_y = second_cell->get_position().y - cell->get_position().y;

            double new_length = hypot(temp_x, temp_y);
            if (second_cell->get_mass() > cell->get_mass() &&
                nearest_bigger > new_length && new_length - second_cell->get_radius() < cell->get_radius() * 2) {
                temp_nearest_bigger_size = second_cell->get_mass();
                nearest_bigger = new_length - second_cell->get_radius();
                x_second_cell_smaller = temp_x;
                y_second_cell_smaller = temp_y;
            }
            if (second_cell->get_mass() < cell->get_mass() &&
                temp_biggest_smaller < second_cell->get_mass() &&
                new_length - second_cell->get_radius() < cell->get_radius()) {
                nearest_smaller = new_length - second_cell->get_radius();
                temp_biggest_smaller = second_cell->get_mass();
                x_second_cell_smaller = temp_x;
                y_second_cell_smaller = temp_y;
            }
        }
        double priority = 1 / nearest_smaller - 1 / nearest_bigger;
        if (priority > 0 && (1 / length) < (1 / nearest_smaller) * temp_biggest_smaller) {
            x = x_second_cell_smaller;
            y = y_second_cell_smaller;
        } else {
            if (priority < 0 && (1 / length) < (1 / nearest_smaller) * temp_biggest_smaller) {
                x -= x_second_cell_smaller;
                y -= y_second_cell_smaller;
            }
        }
        x = (x + cell->get_direction().x) / 2;
        y = (y + cell->get_direction().y) / 2;

        cell->set_direction(x / hypot(x, y), y / hypot(x, y));
        cell->update();
    }
}




