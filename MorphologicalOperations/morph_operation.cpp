#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    // Step 1: Read the image.
    Mat img = imread("coins_bg_black.png", IMREAD_GRAYSCALE);

    if (img.empty())
    {
        cout << "Could not read the image." << endl;
        return -1;
    }

    // cout << "tree.png\n"
    //      << img << endl;

    // Convert the Gray image to binary image.
    Mat thresh;
    threshold(img, thresh, 127, 255, THRESH_BINARY);

    // Structured Element (kernel)
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    // cout << "kernel:\n"
    //      << kernel << endl;

    // Apply the Dilation Filter
    Mat dilated;
    dilate(thresh, dilated, kernel); // grow the boundary pixels

    // cout << "dilated:\n"
    //      << dilated << endl;

    // Apply the Erosion filter
    Mat erosion;
    erode(thresh, erosion, kernel);

    // Apply the Opening filter (Erosion --> Dilation)
    Mat opening;
    morphologyEx(thresh, opening, MORPH_OPEN, kernel);

    // Apply the Closing Filter (Dilation --> Erosion)
    Mat closing;
    morphologyEx(thresh, closing, MORPH_CLOSE, kernel);

    imshow("Original Gray Image", img); // shrink the boundary pixels
    imshow("thresh", thresh);
    imshow("Dilated", dilated);
    imshow("Erosion", erosion);
    imshow("Opening", opening);
    imshow("Closing", closing);

    waitKey(0);

    return 0;
}