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

    cvtColor(img, img, COLOR_BGR2GRAY);

    Mat Transform;

    // Scaling X direction only
    for (double scaleX = 0; scaleX <= 2; scaleX += 0.1)
    {
        Mat T = (Mat_<double>(2, 3) << scaleX, 0, 0, 0, 1, 0);

        warpAffine(img, Transform, T, Size(img.size().width * 4, img.size().height * 2));

        // if (scaleX == 0.5)
        // {
        //     imwrite("scaleX.jpeg", Transform);
        // }

        // imwrite("scaleX.jpeg", Transform);

        imshow("Scaling X Image", Transform);
        waitKey(0);
    }

    // Scaling Y direction only
    for (double scaleY = 0; scaleY <= 2; scaleY += 0.1)
    {
        Mat T = (Mat_<double>(2, 3) << 1, 0, 0, 0, scaleY, 0);

        warpAffine(img, Transform, T, Size(img.size().width * 2, img.size().height * 3));

        imshow("Scaling Y Image", Transform);
        waitKey(0);
    }

    // Scaling X and Y directions.
    for (double scaleXY = 0; scaleXY <= 20; scaleXY += 0.1)
    {
        Mat T = (Mat_<double>(2, 3) << scaleXY, 0, 0, 0, scaleXY, 0);

        warpAffine(img, Transform, T, Size(img.size().width * 3, img.size().height * 3));

        imshow("Scaling X & Y Image", Transform);
        waitKey(100);
    }

    destroyAllWindows();

    return 0;
}