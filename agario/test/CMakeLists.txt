cmake_minimum_required(VERSION 3.20)
project(agario)

set(CMAKE_CXX_STANDARD 17)

add_executable(test test.cpp ../includes/unit.h ../includes/cell.h ../includes/config_values.h ../includes/player.h ../includes/bot.h ../includes/board.h ../includes/real_player.h ../includes/settings.h ../includes/menu.h ../includes/game.h ../includes/manual.h)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(test gtest gtest_main sfml-graphics)
