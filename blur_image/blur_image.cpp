#include "blur_image.h"
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

namespace {

    const int KERNEL_X = 17;
    const int KERNEL_Y = 17;
    const double SIGMA_X =0;
    const double SIGMA_Y = 0;
    bool check_y_parameters(const BlurInfo& cur_info)
    {
        return  cur_info.get_y() > 0 && cur_info.get_height_region() > 0 && cur_info.get_y() + cur_info.get_height_region() < cur_info.get_image().rows;
    }
    bool check_x_parameters(const BlurInfo& cur_info)
    {
        return cur_info.get_x() > 0 && cur_info.get_width_region() > 0 && cur_info.get_x() + cur_info.get_width_region() < cur_info.get_image().cols;
    }
}

cv::Rect BlurringImage:: create_region(int x,int y,int width,int height)
{
    return cv::Rect{ x, y, width, height};
}
cv::Mat BlurringImage:: blur_image(const BlurInfo& cur_info)
{
    if (!check_x_parameters(cur_info) || !check_y_parameters(cur_info)) return cur_info.get_image();
    Mat new_image = cur_info.get_image().clone();
    const cv::Rect cur_region = create_region(cur_info.get_x(), cur_info.get_y(), cur_info.get_width_region(), cur_info.get_height_region());
    GaussianBlur(new_image(cur_region), new_image(cur_region), Size(KERNEL_X, KERNEL_Y), SIGMA_X, SIGMA_Y);
    return  new_image;
}