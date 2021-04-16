#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

int main(int argc, char* argv[]) {
    std::string map_image_path = argv[1];
    std::string image_path = argv[2];
    cv::Mat map_image = cv::imread(map_image_path, 1);
    if (!map_image.data) {
        return 1;
    }
    Mat image = cv::imread(image_path);
    for (size_t i = 0; i < image.cols; ++i) {
        for (size_t j = 0; j < image.rows; ++j) {
            auto& pixel = image.at<Vec3b>(Point(i, j));
            for (int col = 0; col < 3; ++col) {
                pixel[col] = map_image.at<Vec3b>(Point(pixel[col], 2 - col))[col];
            }
        }
    }
    imwrite("mapped.png", image);

    return 0;
}
