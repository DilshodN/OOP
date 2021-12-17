#include "gui.h"
#include <opencv4/opencv2/highgui.hpp>
#include <utility>

using namespace cv;
GUI::GUI(std::string  _window_name):window_name(std::move(_window_name))
{
}
void GUI::draw_image(const cv::Mat& img) const
{
    if (img.empty()) return;
    namedWindow(window_name, WINDOW_AUTOSIZE);
    imshow(window_name, img);
}

void GUI::draw_width_trackbar(int width, int max_width, void call_back(int, void*), void* userdata)
{

    createTrackbar(width_trackbar_name, window_name, &width, max_width, call_back, userdata);
}

void GUI::draw_height_trackbar(int height, int max_height, void call_back(int, void*), void* userdata)
{
    createTrackbar(height_trackbar_name, window_name, &height, max_height, call_back, userdata);
}

void GUI::react_to_mouse(void call_back(int, int, int, int, void*), void* userdata)
{
    setMouseCallback(window_name, call_back, userdata);
}