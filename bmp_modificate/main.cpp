#include "transform.h"
#include "exceptions_bmp.h"

int main(int argc, char* argv[]) {

    std::string filename = argc >= 2 ? argv[1] : "";
    const char* option   = argc >= 3 ? argv[2] : nullptr;
    const char* args     = argc >= 4 ? argv[3] : nullptr;

    bmp::Bitmap origin;
    bmp::Bitmap new_image;
    try{
        origin.Load(filename);
    }
    catch (bmp::BitmapException& e){
        std::cout << "error: " << e.what()  << std::endl;
        return -1;
    }

    if(!origin.Height() || !origin.Width()){
        std::cout << "error: Invalid size of bmp file" << std::endl;
        return -1;
    }

    const std::string without_format = filename.substr(0, filename.length() - 4);

    if(!option && !args){
        transform_bmp(origin, Params::HALF_PI).Save(without_format + "_90.bmp");
        transform_bmp(origin, Params::PI).Save(without_format + "_180.bmp");
        transform_bmp(origin, Params::PI_AND_HALF_PI).Save(without_format + "_270.bmp");
        transform_bmp(origin, Params::VERTICAL).Save(without_format + "_v.bmp");
        transform_bmp(origin, Params::HORIZONTAL).Save(without_format + "_h.bmp");
        return 0;
    }

    if(!option || !args){
        std::cout << "error: Invalid arguments" << std::endl;
        return -1;
    }

    if(!strcmp(option, "rotate")){
        int angle = std::stoi(args);
        switch (angle){
            case 90:
                new_image = transform_bmp(origin, Params ::HALF_PI);
                break;
            case 180:
                new_image = transform_bmp(origin, Params ::PI);
                break;
            case 270:
                new_image = transform_bmp(origin, Params ::PI_AND_HALF_PI);
                break;
            default:
                std::cout << "error: Invalid arguments" << std::endl;
                return -1;
        }
        new_image.Save(without_format + "_" + args + ".bmp");
        return 0;
    }

    if(!strcmp(option, "flip")){
        if(!strcmp(args, "h"))
            new_image = transform_bmp(origin, Params ::HORIZONTAL);
        else if(!strcmp(args, "v"))
            new_image = transform_bmp(origin, Params ::VERTICAL);
        else {
            std::cout << "error: Invalid arguments" << std::endl;
            return -1;
        }
        new_image.Save(without_format + "_" + args + ".bmp");
    }
    return 0;
}