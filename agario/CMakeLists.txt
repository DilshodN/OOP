cmake_minimum_required(VERSION 3.20)
project(agario)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(test)

add_executable(agario src/main.cpp src/unit.cpp includes/unit.h src/cell.cpp includes/cell.h includes/config_values.h src/player.cpp includes/player.h src/bot.cpp includes/bot.h src/board.cpp includes/board.h src/real_player.cpp includes/real_player.h src/settings.cpp includes/settings.h src/menu.cpp includes/menu.h src/game.cpp includes/game.h src/manual.cpp includes/manual.h)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(agario sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
