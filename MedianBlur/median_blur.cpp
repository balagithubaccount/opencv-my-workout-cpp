#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    // cv::Mat src = cv::imread("nature.jpeg");
    // cv::Mat src = cv::imread("Sunset.jpg");
    cv::Mat src = cv::imread("Hills.jpg");
    cv::Mat blur;

    if (src.empty())
    {
        cout << "Could not open the image." << endl;
        return -1;
    }

    for (int i = 3; i <= 35; i += 2)
    {
        cv::medianBlur(src, blur, i);
        cv::imshow("Original Image", src);
        cv::imshow("Median Blur Image", blur);
        cv::waitKey(0);
    }

    // cv::medianBlur(src, blur, 3);
    // cv::imshow("Original Image", src);
    // cv::imshow("Median Blur Image", blur);
    // cv::waitKey(0);

    return 0;
}