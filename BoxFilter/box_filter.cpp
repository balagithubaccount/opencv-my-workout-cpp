#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    cv::Mat src = cv::imread("Hills.jpg");
    cv::Mat filtered;

    if (src.empty())
    {
        cout << "Could not open the image." << endl;
        return -1;
    }

    for (int i = 3; i <= 55; i += 4)
    {
        cv::boxFilter(src, filtered, src.depth(), cv::Size(i, i));
        cv::imshow("Original Image", src);
        cv::imshow("Box Filtered Image", filtered);
        cv::waitKey(500);
    }
    cv::waitKey(0);

    // cv::boxFilter(src, filtered, 8, cv::Size(50,50), cv::Point(25, 25));
    // cv::imshow("Original Image", src);
    // cv::imshow("Box Filtered Image", filtered);
    // cv::waitKey(0);

    return 0;
}
