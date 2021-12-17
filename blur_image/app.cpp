#include "app.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include "blur_image.h"
#include "blur_info.h"
using namespace cv;
namespace
{
    const int  COEFF_MAX = 5;
}
GUI ApplicationBlurringImage::gui = GUI();
void  ApplicationBlurringImage::call_back_mouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_MOUSEMOVE)
    {
        const auto cur_info = static_cast<BlurInfo*>(userdata);
        cur_info->change_x(x);
        cur_info->change_y(y);
        const Mat new_image = BlurringImage::blur_image(*cur_info);
        gui.draw_image(new_image);
    }
}
void ApplicationBlurringImage::call_back_trackbar_width(int width, void* userdata)
{
    const auto cur_info = static_cast<BlurInfo*>(userdata);
    cur_info->change_width_region( width);
    const Mat new_image = BlurringImage::blur_image(*cur_info);
    gui.draw_image(new_image);
}
void ApplicationBlurringImage::call_back_trackbar_height(int height, void* userdata)
{
    const auto cur_info = static_cast<BlurInfo*>(userdata);
    cur_info->change_height_region( height);
    const Mat new_image = BlurringImage::blur_image(*cur_info);
    gui.draw_image(new_image);
}


void ApplicationBlurringImage::start(const cv::Mat& img, size_t delay, size_t default_height, size_t default_width)
{

    int height = default_height;
    int width = default_width;
    gui.draw_image(img);
    BlurInfo cur_info (img, width, height);
    gui.draw_width_trackbar(width, img.cols/COEFF_MAX, call_back_trackbar_width, &cur_info);
    gui.draw_height_trackbar(height, img.rows /COEFF_MAX,call_back_trackbar_height, &cur_info);
    gui.react_to_mouse(call_back_mouse, &cur_info);
    waitKey(delay);
}