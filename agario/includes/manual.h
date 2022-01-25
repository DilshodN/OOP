#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "settings.h"

class Manual final {
private:
    const int manual_window_width = 700;
    const int manual_window_height = 700;
public:
    void run() const;
};