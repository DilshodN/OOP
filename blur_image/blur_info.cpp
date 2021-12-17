#include "blur_info.h"


BlurInfo::BlurInfo(const cv::Mat& img,const int _width, const int _height, const int _cur_x,const  int _cur_y )
{
    image = img;
    width_region = _width;
    height_region = _height;
    x_region = _cur_x;
    y_region =_cur_y;
}

const cv::Mat BlurInfo::get_image() const
{
    return image;
}

cv::Mat BlurInfo::get_image()
{
    return image;
}

int BlurInfo::get_x() const
{
    return x_region;
}

int BlurInfo::get_y() const
{
    return y_region;
}

int BlurInfo::get_width_region() const
{
    return width_region;
}

int BlurInfo::get_height_region() const
{
    return height_region;
}

void BlurInfo::change_x(const int _x)
{
    x_region = _x;
}

void BlurInfo::change_y(const int _y)
{
    y_region = _y;
}

void BlurInfo::change_width_region(const int _width)
{
    width_region = _width;
}

void BlurInfo::change_height_region(const int _height)
{
    height_region = _height;
}