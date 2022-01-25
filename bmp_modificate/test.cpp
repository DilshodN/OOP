#include <gtest/gtest.h>
#include "../transform.h"

TEST(Rotate, EmptyImage)
{
    bmp::Bitmap image;

    bmp::Bitmap new_image_90 = transform_bmp(image, Params ::HALF_PI);
    bmp::Bitmap new_image_180 = transform_bmp(image, Params ::PI);
    bmp::Bitmap new_image_270 = transform_bmp(image, Params ::PI_AND_HALF_PI);

    ASSERT_EQ(image, new_image_90);
    ASSERT_EQ(image, new_image_180);
    ASSERT_EQ(image, new_image_270);
}

TEST(Rotate, ValidArgsRotate_270)
{

    bmp::Bitmap image(200, 100);

    for (std::uint8_t y = 0; y < image.Height(); ++y)
        for (std::uint8_t x = 0; x < image.Width(); ++x)
            image.Set(x, y, bmp::Pixel(x, y, 0));

    bmp::Bitmap new_image = transform_bmp(image, Params ::PI_AND_HALF_PI);

    int new_x, new_y;
    for (std::int32_t y = 0; y < image.Height(); ++y){
        for (std::int32_t x = 0; x < image.Width(); ++x){
            new_x = (new_image.Width() - y - 1);
            new_y = x;

        ASSERT_EQ(image.Get(x, y).r, new_image.Get(new_x, new_y).r);
        ASSERT_EQ(image.Get(x, y).g, new_image.Get(new_x, new_y).g);
        ASSERT_EQ(image.Get(x, y).b, new_image.Get(new_x, new_y).b);
        }
    }
}

TEST(Rotate, ValidArgsRotate_90) {
    bmp::Bitmap image(200, 100);

    for (std::uint8_t y = 0; y < image.Height(); ++y)
        for (std::uint8_t x = 0; x < image.Width(); ++x)
            image.Set(x, y, bmp::Pixel(x, y, 0));


    bmp::Bitmap new_image = transform_bmp(image, Params ::HALF_PI);


    int new_x, new_y;
    for (std::int32_t y = 0; y < image.Height(); ++y) {
        for (std::int32_t x = 0; x < image.Width(); ++x) {
            new_x = y;
            new_y = (new_image.Height() - x - 1);

            ASSERT_EQ(image.Get(x, y).r, new_image.Get(new_x, new_y).r);
            ASSERT_EQ(image.Get(x, y).g, new_image.Get(new_x, new_y).g);
            ASSERT_EQ(image.Get(x, y).b, new_image.Get(new_x, new_y).b);
        }
    }
}
//
TEST(Rotate, ValidArgsRotate_180)
{
    bmp::Bitmap image(200, 100);

    for (std::int32_t y = 0; y < image.Height(); ++y)
        for (std::int32_t x = 0; x < image.Width(); ++x)
            image.Set(x, y, bmp::Pixel(x, y, 0));

    bmp::Bitmap new_image = transform_bmp(image, Params::PI);


    int new_x, new_y;
    for (std::int32_t y = 0; y < image.Height(); ++y){
        for (std::int32_t x = 0; x < image.Width(); ++x){
            new_x = (new_image.Width() - x - 1);
            new_y = (new_image.Height() - y - 1);

            ASSERT_EQ(image.Get(x, y).r, new_image.Get(new_x, new_y).r);
            ASSERT_EQ(image.Get(x, y).g, new_image.Get(new_x, new_y).g);
            ASSERT_EQ(image.Get(x, y).b, new_image.Get(new_x, new_y).b);
            }
        }
}

TEST(Mirror, EmptyImage)
{
    bmp::Bitmap image;

    bmp::Bitmap new_image_v = transform_bmp(image, Params :: VERTICAL);
    bmp::Bitmap new_image_h = transform_bmp(image, Params :: HORIZONTAL);

    ASSERT_EQ(image, new_image_v);
    ASSERT_EQ(image, new_image_h);
}

TEST(Mirror, ValidArgsMirror_H)
{
    bmp::Bitmap image(200, 100);

for (std::int32_t y = 0; y < image.Height(); ++y)
    for (std::int32_t x = 0; x < image.Width(); ++x)
        image.Set(x, y, bmp::Pixel(x, y, 0));


bmp::Bitmap new_image = transform_bmp(image, Params :: HORIZONTAL);

int new_x, new_y;
for (std::int32_t y = 0; y < image.Height(); ++y){
    for (std::int32_t x = 0; x < image.Width(); ++x){
        new_x = x;

        new_y = (new_image.Height() - y - 1);

        ASSERT_EQ(image.Get(x, y).r, new_image.Get(new_x, new_y).r);
        ASSERT_EQ(image.Get(x, y).g, new_image.Get(new_x, new_y).g);
        ASSERT_EQ(image.Get(x, y).b, new_image.Get(new_x, new_y).b);

        }
    }

}

TEST(Mirror, ValidArgsMirror_V)
{
    bmp::Bitmap image(200, 100);

for (std::int32_t y = 0; y < image.Height(); ++y)
    for (std::int32_t x = 0; x < image.Width(); ++x)
        image.Set(x, y, bmp::Pixel(x, y, 0));


bmp::Bitmap new_image = transform_bmp(image, Params :: VERTICAL);

int new_x, new_y;
for (std::int32_t y = 0; y < image.Height(); ++y){
    for (std::int32_t x = 0; x < image.Width(); ++x){

        new_x = (new_image.Width() - x - 1);
        new_y = y;

        ASSERT_EQ(image.Get(x, y).r, new_image.Get(new_x, new_y).r);
        ASSERT_EQ(image.Get(x, y).g, new_image.Get(new_x, new_y).g);
        ASSERT_EQ(image.Get(x, y).b, new_image.Get(new_x, new_y).b);
        }
    }
}
