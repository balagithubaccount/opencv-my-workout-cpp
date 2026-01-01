#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    // Step:1 - Create Image.
    // Mat img(5, 5, CV_8UC3, Scalar(0, 255, 0));

    Mat img = imread("tree.png", IMREAD_COLOR);
    if (img.empty())
    {
        cout << "Could Not open the image." << endl;
        return -1;
    }

    cvtColor(img, img, COLOR_BGR2GRAY);

    cout << "img:\n"
         << img << endl;

    Mat thresh;
    threshold(img, thresh, 127, 255, THRESH_BINARY);

    cout << "thresh:\n"
         << thresh << endl;

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    cout << "kernel:\n"
         << kernel << endl;

    Mat dilated;
    dilate(thresh, dilated, kernel);

    cout << "dilated:\n"
         << dilated << endl;

    // Apply the Closing filter
    Mat closing;
    morphologyEx(thresh, closing, MORPH_CLOSE, kernel);

    cout << "closing:\n"
         << closing << endl;

    imshow("Original Image", img);
    imshow("Threshold Image", thresh);
    imshow("Kernel Image", kernel);
    imshow("Dilated Image", dilated);
    waitKey(0);

    return 0;
}