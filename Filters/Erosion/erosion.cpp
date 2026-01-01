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
        cout << "Could not open the image." << endl;
        return -1;
    }

    // Convert Color image to Gray image
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Conver the Gray Image to Binary image.
    Mat thresh;
    threshold(gray, thresh, 127, 255, THRESH_BINARY);

    // Apply the Erosion Filter
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat erosion;
    erode(thresh, erosion, kernel);

    imshow("Original Image", img);
    imshow("Gray Image", gray);
    imshow("Thresh Image", thresh);
    imshow("Erosion Image", erosion);

    waitKey(0);

    return 0;
}