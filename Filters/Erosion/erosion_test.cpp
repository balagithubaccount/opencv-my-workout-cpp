#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("tree.png", IMREAD_COLOR);
    if (img.empty())
    {
        cout << "Could not open the image." << endl;
        return -1;
    }

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    cout << "gray:\n"
         << gray << endl;

    Mat thresh;
    threshold(gray, thresh, 127, 255, THRESH_BINARY);

    cout << "thresh:\n"
         << thresh << endl;

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat erosion;
    erode(thresh, erosion, kernel);

    cout << "erosion:\n"
         << erosion << endl;

    return 0;
}