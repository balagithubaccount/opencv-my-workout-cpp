#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void test();

int main()
{
    // Read the image
    Mat img = imread("Hills.jpg");
    if (img.empty())
    {
        cout << "Could not read the image." << endl;
        return -1;
    }

    test();

    int tx, ty;
    tx = ty = 10;

    int scaleX, scaleY;
    int shearX, shearY;

    // cout << "enter the shift value for x: ";
    // cin >> tx;
    // cout << "enter the shift value for y: ";
    // cin >> ty;
    // cout << "enter the scaleX value: ";
    // cin >> scaleX;
    // cout << "enter the scaleY value: ";
    // cin >> scaleY;
    // cout << "enter the shear X value: ";
    // cin >> shearX;
    // cout << "enter the shear Y value: ";
    // cin >> shearY;

    // Mat translated;
    // Mat T = (Mat_<double>(2, 3) << scaleX, shearX, tx,
    //          shearY, scaleY, ty);

    for (int i = 0; i <= 10; i++)
    {
        Mat translated;
        Mat T = (Mat_<double>(2, 3) << i, 0, tx,
                 0, 1, ty);

        warpAffine(img, translated, T, img.size());

        imshow("Original Image", img);
        imshow("Translated Image", translated);
        waitKey(0);
    }

    destroyAllWindows();

    return 0;
}

void test()
{
    Mat img(3, 3, CV_8UC1, Scalar(255));
    // cout << "img:\n"
    //      << img;

    for (float i = 0; i <= 1; i+=0.1)
    {
        Mat trans;
        Mat T = (Mat_<double>(2, 3) << i, 0, 0, 0, 1, 0);

        cout << "T:\n"
             << T << endl;

        cout << "img:\n"
             << img << endl;

        warpAffine(img, trans, T, Size(20, 20));

        cout << "translated:\n"
             << trans << endl;

        imshow("10 x 10 Image", img);
        imshow("Translated Image", trans);
        waitKey(0);
    }
    // Mat trans;
    // Mat T = (Mat_<double>(2, 3) << 1, 0, -5, 0, 1, 5);

    // warpAffine(img, trans, T, Size(20, 20));

    // cout << "translated:\n"
    //      << trans << endl;

    // imshow("10 x 10 Image", img);
    // imshow("Translated Image", trans);
    // waitKey(0);
}