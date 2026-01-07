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
    Point2f center(img.cols / 2.0f, img.rows / 2.0f);

    for (int i = 0; i <= 360; i++)
    {
        // Get Rotaion 2 x 3 matrix
        Mat rotated_mat = getRotationMatrix2D(center, i, 1);

        cout << "rotated_mat: " << endl
             << rotated_mat << endl;

        // rotated_mat.at<double>(0, 2) += 50;
        // rotated_mat.at<double>(1, 2) += 50;

        // cout << "new rotated_mat: " << endl
        //      << rotated_mat << endl;

        Mat rotated_img;
        warpAffine(img, rotated_img, rotated_mat, img.size() * 2, INTER_CUBIC);

        imshow("Rotated Image", rotated_img);
        waitKey(0);
    }

    // Mat rotated_mat = getRotationMatrix2D(Point2f(img.size().width / 2, img.size().height / 2), 90, 1);
    // Mat rotated_img;
    // warpAffine(img, rotated_img, rotated_mat, img.size() * 2);

    // Mat transpose_img;
    // transpose(rotated_img, transpose_img);

    // imshow("Rotated Image", rotated_img);
    // imshow("Transpose Image", transpose_img);
    waitKey(0);

    destroyAllWindows();
    return 0;
}