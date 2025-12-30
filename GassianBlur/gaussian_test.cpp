#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat img(50, 50, CV_8UC3, Scalar(55, 155, 255));
    // Mat img = imread("tree.png", IMREAD_COLOR);

    if (img.empty())
    {
        cout << "could not open the image." << endl;
        return -1;
    }

    cout << "rows: " << img.rows << endl;
    cout << "cols: " << img.cols << endl;
    cout << "size: " << img.size() << endl;
    cout << "depth: " << img.depth() << endl;
    cout << "type: " << img.type() << endl;

    cout << "img:\n"
         << img << endl;
    imshow("Original Image", img);

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    cout << "gray img:\n"
         << gray << endl;
    imshow("Gray Image", gray);

    Mat blur;
    GaussianBlur(gray, blur, Size(3, 3), 5);
    cout << "blur img:\n"
         << blur << endl;
    imshow("Blur Image", blur);

    waitKey(0);

    return 0;
}
