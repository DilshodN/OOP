#pragma once
#include <opencv4/opencv2/highgui.hpp>

class BlurInfo final
{
    cv::Mat image;
    int x_region;
    int y_region;
    int width_region;
    int height_region;
public:
    BlurInfo(const cv::Mat& img, int _width, int _height, int _x = 0, int _y = 0);
    const cv::Mat get_image() const;
    cv::Mat get_image();
    int get_x()const;
    int get_y()const;
    int get_width_region()const;
    int get_height_region()const;
    void change_x(int _x);
    void change_y(int _y);
    void change_width_region(int _width);
    void change_height_region(int _height);
};