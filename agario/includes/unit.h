#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class Unit {
private:
    std::shared_ptr<sf::CircleShape> sprite;
    sf::Color color;
protected:
    sf::Vector2<float> position{};
    float radius{};
    int mass{};
public:
    Unit();

    [[maybe_unused]] explicit Unit(sf::Vector2<float> position, int mass = 1);

    [[maybe_unused]] virtual void grow(int add_mass);

    [[maybe_unused]] void decrease_mass(int sub_mass);

    [[maybe_unused]] void set_mass(int new_mass);

    [[nodiscard]] int get_mass() const;

    [[nodiscard]] sf::Vector2<float> get_position() const;

    [[nodiscard]] float get_radius() const;

    [[maybe_unused]] void draw(sf::RenderWindow &window);

    [[maybe_unused]] void set_color(sf::Color new_color);

    [[maybe_unused]] void set_position(sf::Vector2<float> new_position);

    [[maybe_unused]] void set_radius(float new_radius);

    [[maybe_unused]] void set_radius_from_mass(int new_mass);

    friend std::ostream &operator<<(std::ostream &stream, const Unit &unit);

    friend std::istream &operator>>(std::istream &stream, Unit &unit);

    virtual ~Unit() = default;
};