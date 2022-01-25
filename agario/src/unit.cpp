#include "../includes/unit.h"

Unit::Unit() {
    sprite = std::make_shared<sf::CircleShape>();
    sprite->setRadius(2);
}

Unit::Unit(sf::Vector2<float> position, int mass) : position(position), mass(mass) {
    sprite = std::make_shared<sf::CircleShape>();
    color = sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255);
    set_radius_from_mass(mass);
}

void Unit::grow(int add_mass) {
    mass += add_mass;
}

void Unit::decrease_mass(int sub_mass) {
    mass -= sub_mass;
}

void Unit::set_mass(int new_mass) {
    mass = new_mass;
}

int Unit::get_mass() const {
    return mass;
}

sf::Vector2<float> Unit::get_position() const {
    return position;
}

float Unit::get_radius() const {
    return radius;
}

void Unit::draw(sf::RenderWindow &window) {
    set_radius_from_mass(mass);
    try {
        sprite->setOrigin(radius, radius);
        sprite->setPosition(position);
        sprite->setRadius(radius);
        sprite->setFillColor(color);
        window.draw(*sprite);
    }
    catch (std::exception &e) {
        std::cerr << "can't draw a shape" << e.what() << std::endl;
    }
}

void Unit::set_color(sf::Color new_color) {
    color = new_color;
}

void Unit::set_position(sf::Vector2<float> new_position) {
    position = new_position;
}

void Unit::set_radius(float new_radius) {
    radius = new_radius;
}

void Unit::set_radius_from_mass(int new_mass) {
    radius = sqrt(abs(mass)) + 2;
}

std::ostream &operator<<(std::ostream &stream, const Unit &unit) {
    stream << unit.mass << std::endl;
    stream << unit.color.r << std::endl;
    stream << unit.color.g << std::endl;
    stream << unit.color.b << std::endl;
    stream << unit.color.a << std::endl;
    stream << unit.position.x << std::endl;
    stream << unit.position.y << std::endl;
    stream << unit.radius << std::endl;
    return stream;
}

std::istream &operator>>(std::istream &stream, Unit &unit) {
    stream >> unit.mass;
    stream >> unit.color.r;
    stream >> unit.color.g;
    stream >> unit.color.b;
    stream >> unit.color.a;
    stream >> unit.position.x;
    stream >> unit.position.y;
    stream >> unit.radius;
    return stream;
}













