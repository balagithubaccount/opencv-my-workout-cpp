#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

// int main()
// {
//     cv::Mat src(5, 5, CV_8UC1, cv::Scalar(255));
//     cv::Mat gaussian;
//     if(src.empty())
//     {
//         cout << "Could not creat the image" << endl;
//         return -1;
//     }
//     cout << src << endl;
//     cv::imshow("Source", src);
//     cv::GaussianBlur(src, gaussian, cv::Size(3,3), 1.1);
//     cout << endl << gaussian << endl;
//     cv::imshow("GaussianBlur", gaussian);
//     cv::waitKey(0);
//     return 0;
// }

// visual understanding for image coordinate systerm
int main()
{
    Mat img = Mat::zeros(400, 400, CV_8UC3);

    if (img.empty())
    {
        cout << "could not create the image." << endl;
        return -1;
    }

    // Draw a circle to the image
    circle(img, Point(0, 0), 5, Scalar(0,0,255), -1);

    // Write a text to the image
    putText(img, "(0,0)", Point(0, 0), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);

    // Another point
    circle(img, Point(200, 300), 5, Scalar(0, 255, 0), -1);
    putText(img, "(200,300)", Point(205, 315),
            FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,255,0), 1);

    imshow("Coordinate System", img);
    waitKey(0);

    return 0;
}