#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>

#include "../includes/unit.h"
#include "../src/unit.cpp"

#include "../includes/cell.h"
#include "../src/cell.cpp"

#include "../includes/player.h"
#include "../src/player.cpp"

#include "../includes/real_player.h"
#include "../src/real_player.cpp"

#include "../includes/bot.h"
#include "../src/bot.cpp"

#include "../src/game.cpp"

#include "../src/board.cpp"

using namespace sf;

TEST(agario, UnitBasic1) {
    Unit u = Unit({0.0, 0.0});
    EXPECT_EQ(u.get_mass(), 1);
}

TEST(agario, UnitBasic2) {
    int size = 1234;
    Unit u = Unit({0.0, 0.0}, size);
    EXPECT_EQ(u.get_mass(), size);
}

TEST(agario, UnitBasicGrowing1) {
    int size = 730;
    int growthSize = 459;
    Unit u = Unit({0.0, 0.0}, size);
    u.grow(growthSize);
    EXPECT_EQ(u.get_mass(), size + growthSize);
}

TEST(agario, UnitBasicGrowing2) {
    int growthSize = 9421;
    Unit u = Unit({0.0, 0.0});
    u.grow(growthSize);
    EXPECT_EQ(u.get_mass(), 1 + growthSize);
}

TEST(agario, UnitIncrease) {
    int size = 1234;
    int increase = 442;
    Unit u = Unit({0.0, 0.0}, size);
    u.decrease_mass(increase);
    EXPECT_EQ(u.get_mass(), size - increase);
}

TEST(agario, UnitSetRadius) {
    int mass = 400;
    Unit u;
    u.set_radius_from_mass(mass);
    EXPECT_EQ(u.get_radius(), 2);
}

TEST(agario, CellBasic1) {
    Cell cell({12.5, 31.22}, 0, false);
    Unit unit({7.12, 49.2});
    EXPECT_FLOAT_EQ(cell.distance(unit), 18.767653);
}

TEST(agario, CellBasic2) {
    Cell cell({122.123, 333.777}, 50.0, true);
    Unit unit({122.123, 333.777});
    EXPECT_FLOAT_EQ(cell.distance(unit), 0);
}

TEST(agario, CellBasic3) {
    Cell cell({12.5, 31.22}, 0, false);
    Cell cell2({7.12, 49.2}, 1, true);
    EXPECT_FLOAT_EQ(cell.distance(cell2), 18.767653);
}

TEST(agario, UpdateTest1) {
    float x = 122.123;
    float y = 321.111;
    double xDirection = 1;
    double yDirection = 1;
    Cell cell({x, y}, 2.0, true);
    cell.set_direction(xDirection, yDirection);

    cell.update_speed();
    double speed = cell.get_speed();

    cell.update();

    EXPECT_FLOAT_EQ(cell.get_position().x, x + xDirection * speed);
    EXPECT_FLOAT_EQ(cell.get_position().y, y + yDirection * speed);
}

TEST(agario, UpdateTest2) {
    float x = WINDOW_WIDTH;
    float y = WINDOW_HEIGHT;
    float xDirection = 1;
    float yDirection = 1;
    Cell cell({x, y}, 2.0, true);

    int mass = 500;
    cell.set_mass(mass);
    cell.set_radius(mass);

    double radius = cell.get_radius();
    cell.set_position(sf::Vector2f(x - radius, y - radius));
    cell.set_position({xDirection, yDirection});

    cell.update_speed();
    double speed = cell.get_speed();

    cell.update();

    EXPECT_FLOAT_EQ(cell.get_position().x, WINDOW_WIDTH - radius);
    EXPECT_FLOAT_EQ(cell.get_position().y, WINDOW_HEIGHT - radius);
}

TEST(agario, PlayerBasicAddCell) {
    Player p(92, 123.1, 0.2, 72);
    int number = 23;

    EXPECT_EQ(p.cells.size(), 1);

    for (unsigned int i = 0; i < number; ++i) {
        auto cell = std::make_shared<Cell>();
        p.add_cell(cell);
    }

    EXPECT_EQ(p.cells.size(), number + 1);
}

TEST(agario, PlayerBasicRemoveCell) {
    Player p(92, 123.1, 0.2, 72);
    int number = 23;

    auto c1 = std::shared_ptr<Cell>();
    auto c2 = std::shared_ptr<Cell>();

    EXPECT_EQ(p.cells.size(), 1);
    p.add_cell(c1);
    p.add_cell(c2);
    EXPECT_EQ(p.cells.size(), 3);
    p.remove_cell(c2);
    EXPECT_EQ(p.cells.size(), 2);
    p.remove_cell(c1);
    EXPECT_EQ(p.cells.size(), 1);
}


TEST(agario, RealPlayerSetMouse) {
    float posX = 92.2;
    float posY = 123.1;
    RealPlayer p(posX, posY);

    float x = 321.9;
    float y = 422;

    p.set_mouse_position(sf::Vector2i(x, y));

    double newX = p.cells[0]->get_position().x;
    double newY = p.cells[0]->get_position().y;

    ASSERT_TRUE(std::abs(newX / newY - x / y) < 0.1);

    EXPECT_LT((newX - posX) * (newX - posX) + (newY - posY) * (newY - posY),
              (x - posX) * (x - posX) + (y - posY) * (y - posY));
}

TEST(agario, RealPlayerDivide) {
    float posX = 92.2;
    float posY = 123.1;
    RealPlayer p(posX, posY);

    float x = 321.9;
    float y = 422;

    p.divide(sf::Vector2i(x, y));

    double newX = p.cells[1]->get_position().x;
    double newY = p.cells[1]->get_position().y;

    EXPECT_EQ(p.cells.size(), 2);

    ASSERT_TRUE(std::abs(newX / newY - x / y) < 0.1);

    EXPECT_LT((newX - posX) * (newX - posX) + (newY - posY) * (newY - posY),
              (x - posX) * (x - posX) + (y - posY) * (y - posY));
}

TEST(agario, BotBehaviour) {
    std::vector<std::shared_ptr<Cell>> vec;
    std::vector<std::shared_ptr<Unit>> uvec;
    vec.push_back(std::shared_ptr<Cell>(new Cell({0, 0}, 0, false, 2)));
    vec.push_back(std::shared_ptr<Cell>(new Cell({500, 500}, 0, false, 123)));
    vec.push_back(std::shared_ptr<Cell>(new Cell({1000, 1000}, 0, false, 20)));

    uvec.push_back(std::shared_ptr<Unit>(new Unit({5, 5}, 1)));

    Bot bot = Bot(vec[1]);

    bot.set_next_position(uvec, vec);

    double dist1 = (vec[0]->get_position().x - vec[1]->get_position().x) *
                   (vec[0]->get_position().x - vec[1]->get_position().x) +
                   (vec[0]->get_position().y - vec[1]->get_position().y) *
                   (vec[0]->get_position().y - vec[1]->get_position().y);


    double dist2 = (vec[1]->get_position().x - vec[2]->get_position().x) *
                   (vec[1]->get_position().x - vec[2]->get_position().x) +
                   (vec[1]->get_position().y - vec[2]->get_position().y) *
                   (vec[1]->get_position().y - vec[2]->get_position().y);

    EXPECT_LT(dist1, dist2);
}

