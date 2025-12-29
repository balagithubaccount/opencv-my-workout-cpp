#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;

int main()
{
    cv::Mat gray(480, 640, CV_8UC1);
    cv::Mat color(480, 640, CV_8UC3, cv::Scalar(0, 255, 0));
    if(gray.empty()) {
        cout << "Error: could not found image." << endl;
        return -1;
    }

    cv::imshow("First Image", gray);
    cv::imshow("Green Image", color);
    cv::waitKey(0);

    return 0;
}