#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;

int main()
{
    cv::Mat src(5, 5, CV_8UC1, cv::Scalar(255));
    cv::Mat gaussian;
    if(src.empty())
    {
        cout << "Could not creat the image" << endl;
        return -1;
    }
    cout << src << endl;
    cv::imshow("Source", src);
    cv::GaussianBlur(src, gaussian, cv::Size(3,3), 1.1);
    cout << endl << gaussian << endl;
    cv::imshow("GaussianBlur", gaussian);
    cv::waitKey(0);
    return 0;
}