#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    // Read the image
    Mat img = imread("road.jpg", IMREAD_COLOR);
    if (img.empty())
    {
        cout << "Could not read the image." << endl;
        return -1;
    }

    Mat gray, blur, edges;

    // Convert the color image to grayscal image
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Blur the image
    GaussianBlur(gray, blur, Size(5, 5), 1.5);

    // Edge detector
    Canny(blur, edges, 50, 150);

    // Threshold
    Mat thresh;
    threshold(gray, thresh, 127, 255, THRESH_BINARY);

    // Hough Transformation need to understand briefly.
    std::vector<Vec2f> lines;
    HoughLinesP(thresh, lines, 1, 180, 150);

    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0];
        float theta = lines[i][1];

        cout << "rho: " << rho << ", theta: " << theta << endl;

        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;

        Point pt1, pt2;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));

        line(img, pt1, pt2, Scalar(0, 0, 255), 2);
    }

    imshow("Original Image", img);
    imshow("Gray Image", gray);
    imshow("Blur Image", blur);
    imshow("Edge Image", edges);
    imshow("Thresh Image", thresh);
    waitKey(0);

    return 0;
}