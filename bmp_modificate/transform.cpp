#include "transform.h"
#include "exceptions_bmp.h"
using namespace bmp;

namespace {

    const Pixel &rot90(std::int32_t x, std::int32_t y, const Bitmap &origin) {
         return origin[origin.Width() - y - 1 + x * origin.Width()];
    };

    const Pixel &rot180(std::int32_t x, std::int32_t y, const Bitmap &origin) {
        return origin[(origin.Width() - x - 1) + (origin.Height() - y - 1) * origin.Width()];
    }

    const Pixel &rot270(std::int32_t x, std::int32_t y, const Bitmap &origin) {
        return origin[y + (origin.Height() - x - 1) * origin.Width()];
    }

    const Pixel &horizontal(std::int32_t x, std::int32_t y, const Bitmap &origin) {
        return origin[x + (origin.Height() - y - 1) * origin.Width()];

    }

    const Pixel &vertical(std::int32_t x, std::int32_t y, const Bitmap &origin) {
        return origin[(origin.Width() - x - 1) + y * origin.Width()];
    }

    void modify_image(const Bitmap &origin, Bitmap &mod,
                      const Pixel &(*pix)(std::int32_t x, std::int32_t y, const Bitmap &originImage)) {

        for (std::int32_t y = 0; y < mod.Height(); y++)
            for (std::int32_t x = 0; x < mod.Width(); x++)
                mod[x + y * mod.Width()] = pix(x, y, origin);
    }
}

Bitmap transform_bmp(const bmp::Bitmap& origin, Params param){
    if (!origin.Height() || !origin.Width()) return Bitmap();
    bmp::Bitmap final;
    switch (param){
        case Params ::HALF_PI:
            final = Bitmap(origin.Height(), origin.Width());
            modify_image(origin, final, rot90);
            break;
        case Params ::PI:
            final = Bitmap(origin.Width(), origin.Height());
            modify_image(origin, final, rot180);
            break;
        case Params ::PI_AND_HALF_PI:
            final = Bitmap(origin.Height(), origin.Width());
            modify_image(origin, final, rot270);
            break;
        case Params ::VERTICAL:
            final = Bitmap(origin.Width(), origin.Height());
            modify_image(origin, final, vertical);
            break;
        case Params ::HORIZONTAL:
            final = Bitmap(origin.Width(), origin.Height());
            modify_image(origin, final, horizontal);
            break;
    }
    return final;
}