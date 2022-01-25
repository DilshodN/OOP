#pragma once

#include "BitmapPlusPlus.hpp"

enum class Params{
    HALF_PI,
    PI,
    PI_AND_HALF_PI,
    VERTICAL,
    HORIZONTAL
};

bmp::Bitmap transform_bmp(const bmp::Bitmap& origin, Params param);