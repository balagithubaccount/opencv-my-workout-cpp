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

    Mat rotated_mat = getRotationMatrix2D(Point2f(img.size().width / 2, img.size().height / 2), 90, 1);
    Mat rotated_img;
    warpAffine(img, rotated_img, rotated_mat, img.size() * 2);
    Mat transpose_img;
    transpose(rotated_img, transpose_img);

    imshow("Original Image", img);
    imshow("Rotated Image", rotated_img);
    imshow("Transpose Image", transpose_img);
    waitKey(0);

    destroyAllWindows();
    return 0;
}