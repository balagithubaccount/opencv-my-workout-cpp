#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("nature.jpeg");
    if (img.empty())
    {
        cout << "Could not read the image." << endl;
        return -1;
    }
    double scaleX = 0;
    for (double scaleX = 0; scaleX <= 1; scaleX += 0.1)
    {
        Mat T = (Mat_<double>(2, 3) << scaleX, 0, 0, 0, 1, 0);

        Mat Transform;
        warpAffine(img, Transform, T, img.size());

        imshow("Original Image", img);
        imshow("Translated Image", Transform);
        waitKey(0);
    }
    destroyAllWindo

    return 0;
}