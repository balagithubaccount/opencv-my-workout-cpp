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

    imshow("Original Image", img);

    Mat transformX;
    Mat transformY;
    Mat transformXY;

    // Transforming image along x
    for (int alongX = 1; alongX <= 300; alongX += 20)
    {
        Mat T = (Mat_<double>(2, 3) << 1, 0, alongX, 0, 1, 0);

        // Apply the transformation along x direction only.
        warpAffine(img, transformX, T, img.size() * 2);

        imshow("Translation X", transformX);
        waitKey(0);
    }

    // Transforming image along y
    for (int alongY = 1; alongY <= 300; alongY += 20)
    {
        Mat T = (Mat_<double>(2, 3) << 1, 0, 0, 0, 1, alongY);

        // Apply the transformation along x direction only.
        warpAffine(img, transformY, T, img.size() * 2);

        imshow("Translation Y", transformY);
        waitKey(0);
    }

    // Transforming image along x and y
    for (int alongXY = 1; alongXY <= 300; alongXY += 20)
    {
        Mat T = (Mat_<double>(2, 3) << 1, 0, alongXY, 0, 1, alongXY);

        // Apply the transformation along x direction only.
        warpAffine(img, transformXY, T, img.size() * 2);

        imshow("Translation X", transformXY);
        waitKey(0);
    }

    destroyAllWindows();

    return 0;
}