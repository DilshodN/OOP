#pragma once
#include <string>
#include <opencv4/opencv2/highgui.hpp>

class GUI final
{
    const std::string window_name;
    const std::string width_trackbar_name{ "Width" };
    const std::string height_trackbar_name{ "Height" };
public:
    GUI(std::string  _window_name= "Window" );
    void draw_image(const cv::Mat& img) const;
    void draw_width_trackbar(int width, int max_width, void call_back(int, void*) = 0, void* userdata = 0);
    void draw_height_trackbar(int height, int max_height, void call_back(int, void*) = 0, void* userdata = 0);
    void react_to_mouse(void call_back(int, int, int, int, void*) = 0, void* userdata=0);
};
