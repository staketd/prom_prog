#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "codegen.hpp"

using namespace cv;

int main(int argc, char* argv[]) {
    std::string image_path = argv[1];
    Mat image = cv::imread(image_path);
    for (size_t i = 0; i < image.cols; ++i) {
        for (size_t j = 0; j < image.rows; ++j) {
            auto& pixel = image.at<Vec3b>(Point(i, j));
            for (int col = 0; col < 3; ++col) {
                pixel[col] = map_image_values[2 - col][pixel[col]];
            }
        }
    }
    imwrite("mapped.png", image);
}