#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    cv::Mat src_image = cv::imread("nature.jpeg");
    cv::Mat blur_image;
    if (src_image.empty())
    {
        cout << "Could not read the image." << endl;
        return -1;
    }

    for (int i = 3; i <= 35; i += 2)
    {
        cv::GaussianBlur(src_image, blur_image, cv::Size(i, i), 0);

        cv::imshow("Source Image", src_image);
        cv::imshow("Gaussian Filtered Image", blur_image);
        cv::waitKey(0);
    }
    // cv::GaussianBlur(src_image, blur_image, cv::Size(3, 3), 0, 0);

    // cv::imshow("Source Image", src_image);d
    // cv::imshow("Gaussian Filtered Image", blur_image);
    // cv::waitKey(0);

    return 0;
}