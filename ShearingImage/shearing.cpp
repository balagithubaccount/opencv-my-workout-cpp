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

    Mat translation;

    imshow("Original Image", img);

    // Shearing along X direction.
    for (double shearX = 0; shearX <= 1; shearX += 0.1)
    {
        Mat T = (Mat_<double>(2, 3) << 1, shearX, 0, 0, 1, 0);

        warpAffine(img, translation, T, img.size() * 2);

        imshow("Shearing along X", translation);
        waitKey(0);
    }

    // Shearing along Y direction.
    for (double shearY = 0; shearY <= 1; shearY += 0.1)
    {
        Mat T = (Mat_<double>(2, 3) << 1, 0, 0, shearY, 1, 0);

        warpAffine(img, translation, T, img.size() * 2);

        imshow("Shearing along Y", translation);
        waitKey(0);
    }

    // Shearing along X and Y direction.
    for (double shearXY = 0; shearXY <= 1; shearXY += 0.1)
    {
        Mat T = (Mat_<double>(2, 3) << 1, shearXY, 0, shearXY, 1, 0);

        warpAffine(img, translation, T, img.size() * 2);

        imshow("Shearing along X and Y", translation);
        waitKey(0);
    }

    // Shearing along -X direction.
    for (double shearX = 0; shearX <= 1; shearX += 0.1)
    {
        Mat T = (Mat_<double>(2, 3) << 1, -shearX, 0, 0, 1, 0);

        warpAffine(img, translation, T, img.size() * 2);

        imshow("Shearing along X", translation);
        waitKey(0);
    }

    // Shearing along -Y direction.
    for (double shearY = 0; shearY <= 1; shearY += 0.1)
    {
        Mat T = (Mat_<double>(2, 3) << 1, 0, 0, -shearY, 1, 0);

        warpAffine(img, translation, T, img.size() * 2);

        imshow("Shearing along Y", translation);
        waitKey(0);
    }

    // Shearing along -X and -Y direction.
    for (double shearXY = 0; shearXY <= 1; shearXY += 0.1)
    {
        Mat T = (Mat_<double>(2, 3) << 1, -shearXY, 0, -shearXY, 1, 0);

        warpAffine(img, translation, T, img.size() * 2);

        imshow("Shearing along X and Y", translation);
        waitKey(0);
    }

    return 0;
}