#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{

    // Read Image
    Mat img = imread("coins_bg_black.png", IMREAD_COLOR);
    if (img.empty())
    {
        cout << "Could not the open image." << endl;
        return -1;
    }

    // Convert color img to Gray img
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Convert into binary image
    Mat thresh;
    threshold(gray, thresh, 127, 255, THRESH_BINARY);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat dilated;
    dilate(thresh, dilated, kernel);

    // Apply the closing filter
    Mat closing;
    morphologyEx(thresh, closing, MORPH_CLOSE, kernel);

    imshow("Original Image", img);
    imshow("Gray Image", gray);
    imshow("Thresh Image", thresh);
    imshow("Dilated Image", dilated);
    imshow("Closing Image", closing);
    waitKey(0);

    return 0;
}
