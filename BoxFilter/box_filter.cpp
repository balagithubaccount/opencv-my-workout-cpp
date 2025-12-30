#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    // cv::Mat src = cv::imread("Hills.jpg");
    cv::Mat src(5, 4, CV_8UC3, cv::Scalar(0, 255, 0));
    src = cv::imread("tree.png");
    cv::Mat filtered;

    if (src.empty())
    {
        cout << "Could not open the image." << endl;
        return -1;
    }

    // for (int i = 3; i <= 55; i += 4)
    // {
    //     cv::boxFilter(src, filtered, src.depth(), cv::Size(i, i));
    //     cv::imshow("Original Image", src);
    //     cv::imshow("Box Filtered Image", filtered);
    //     cv::waitKey(500);
    // }
    // cv::waitKey(0);

    cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);

    cout << "src:\n"
         << src << endl;
    cv::boxFilter(src, filtered, -1, cv::Size(3, 3));

    cout << "boxfilter:\n"
         << filtered << endl;

    cv::namedWindow("Original Image", cv::WINDOW_NORMAL);
    cv::imshow("Original Image", src);
    cv::imshow("Box Filtered Image", filtered);
    cv::waitKey(0);

    return 0;
}
