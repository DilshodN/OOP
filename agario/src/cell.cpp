#include "../includes/cell.h"

double Cell::set_speed() {
    double speed_of_cell;
    if (is_it_player()) {
        speed_of_cell = (BASIC_SPEED + (0.5 * BASIC_SPEED) * (2 - LEVEL)) / sqrt(radius * 2) + acceleration;
    } else {
        speed_of_cell = (BASIC_SPEED + (0.5 * BASIC_SPEED) * (LEVEL - 2)) / sqrt(radius * 2) + acceleration;
    }
    return speed_of_cell;
}

void Cell::slow_down() {
    if (clock.getElapsedTime().asMilliseconds() > 0.1) {
        speed = BASIC_SPEED / sqrt(radius);
        clock.restart();
    }
}

void Cell::lose_mass() {
    --steps_to_decrease_mass;
    if (steps_to_decrease_mass <= 0) {
        if (mass > 1) {
            decrease_mass(1);
        }
        steps_to_decrease_mass = calculate_steps();
    }
}

void Cell::eval_position() {
    if (position.x < radius) {
        position.x = radius;
    }
    if (position.y < radius) {
        position.y = radius;
    }
    if (position.x > WINDOW_WIDTH) {
        position.x = WINDOW_WIDTH - radius;
    }
    if (position.y > WINDOW_HEIGHT) {
        position.y = WINDOW_HEIGHT - radius;
    }
}


Cell::Cell(sf::Vector2<float> position, double acceleration, bool is_player, int mass) : Unit(position, mass) {
    if (is_it_player()) {
        speed = (BASIC_SPEED + (0.5 * BASIC_SPEED) * (2 - LEVEL)) / sqrt(radius) + acceleration;
    } else {
        speed = (BASIC_SPEED + (0.5 * BASIC_SPEED) * (LEVEL - 2)) / sqrt(radius) + acceleration;
    }
    clock.restart();
    steps_to_decrease_mass = calculate_steps();
}

void Cell::update_speed() {
    speed = set_speed();
    slow_down();
}

[[maybe_unused]] void Cell::set_direction(float x, float y) {
    x_dir = x;
    y_dir = y;
}

[[maybe_unused]] void Cell::set_as_player() {
    is_player = true;
}

[[maybe_unused]] void Cell::set_acceleration(double acc) {
    acceleration = acc;
}

[[maybe_unused]] double Cell::get_speed() const {
    return speed;
}

[[maybe_unused]] void Cell::update() {
    lose_mass();
    update_speed();
    position.x += static_cast<float>(x_dir * speed);
    position.y += static_cast<float>(y_dir * speed);
    eval_position();
}

int Cell::calculate_steps() const {
    return static_cast<int>(MAX_MASS_OF_PLAYER / (mass)); // подобрал
}

double Cell::distance(const Unit &unit) const {
    double x = position.x - unit.get_position().x;
    double y = position.y - unit.get_position().y;
    return hypot(x, y);
}

void Cell::grow(int add_mass) {
    Unit::grow(add_mass);
    update_speed();
}

bool Cell::is_it_player() const {
    return is_player;
}

std::shared_ptr<Cell> Cell::division(sf::Vector2<int> mouse_position) {
    sf::Vector2<float> position = Unit::get_position();
    float hypot_value = hypot((static_cast<float>(mouse_position.x) - position.x),
                              (static_cast<float>(mouse_position.y) - position.y));
    float cos_alpha = (static_cast<float>(mouse_position.x) - position.x) / hypot_value;
    float sin_alpha = (static_cast<float>(mouse_position.y) - position.y) / hypot_value;
    float new_x_coord = position.x + cos_alpha * (1.5 * Unit::get_radius());
    float new_y_coord = position.y + sin_alpha * (1.5 * Unit::get_radius());
    sf::Vector2<float> new_pos(new_x_coord, new_y_coord);
    int new_mass = get_mass() / 2;
    Unit::set_mass(new_mass);
    speed = set_speed();
    auto new_cell = std::make_shared<Cell>(new_pos, BASIC_SPEED, true, new_mass);
    new_cell->set_color(sf::Color::Red);
    return new_cell;
}

[[maybe_unused]] sf::Vector2<float> Cell::get_direction() const {
    return {x_dir, y_dir};
}