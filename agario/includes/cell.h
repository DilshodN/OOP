#pragma once

#include "unit.h"
#include "config_values.h"
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>

class Cell final : public Unit {
private:
    double speed{}, acceleration{};
    float x_dir{}, y_dir{};
    bool is_player{};
    sf::Clock clock;
    int steps_to_decrease_mass{};

    double set_speed();

    void slow_down();

    void lose_mass();

    void eval_position();

public:
    Cell() = default;

    Cell(sf::Vector2<float> position, double acceleration, bool is_player, int mass = 1);

    ~Cell() override = default;

    void update_speed();

    [[maybe_unused]] void set_direction(float x, float y);

    [[maybe_unused]] void set_as_player();

    [[maybe_unused]] void set_acceleration(double acc);

    [[maybe_unused]] [[nodiscard]] double get_speed() const;

    [[maybe_unused]] void update();

    [[nodiscard]] int calculate_steps() const;

    [[maybe_unused]] [[nodiscard]] double distance(const Unit &unit) const;

    void grow(int add_mass) override;

    [[nodiscard]] bool is_it_player() const;

    [[maybe_unused]] std::shared_ptr<Cell> division(sf::Vector2<int> mouse_position);

    [[maybe_unused]] [[nodiscard]] sf::Vector2<float> get_direction() const;

};