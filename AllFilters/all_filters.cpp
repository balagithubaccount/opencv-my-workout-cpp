#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    cv::Mat src = cv::imread("Hills.jpg", cv::IMREAD_UNCHANGED);

    cv::Mat gaussian, median, box;

    if (src.empty())
    {
        cout << "Could not open the image." << endl;
        return -1;
    }

    for (int i = 3; i <= 35; i += 2)
    {
        cv::GaussianBlur(src, gaussian, cv::Size(i, i), 0);
        cv::medianBlur(src, median, i);
        cv::boxFilter(src, box, src.depth(), cv::Size(i, i));

        cv::imshow("Original Image", src);
        cv::imshow("Gaussian Blur", gaussian);
        cv::imshow("Median Blur", median);
        cv::imshow("Box Filter", box);
        cv::waitKey(0);
    }

    // cv::GaussianBlur(src, gaussian, cv::Size(3,3), 0);
    // cv::medianBlur(src, median, 3);
    // cv::boxFilter(src, box, src.depth(), cv::Size(3,3));

    // cv::imshow("Original Image", src);
    // cv::imshow("Gaussian Blur", gaussian);
    // cv::imshow("Median Blur", median);
    // cv::imshow("Box Filter", box);
    // cv::waitKey(0);
    return 0;
}