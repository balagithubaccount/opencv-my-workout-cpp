#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    // Step 1: Load the image
    // Mat img = imread("circle.png");
    // Mat img = imread("square.png");
    // Mat img = imread("triangle.png");
    // Mat img = imread("rectangle.png");
    // Mat img = imread("rectangle_2.png");

    cout << "argv[1]: " << argv[1] << endl;
    Mat img = imread(argv[1]);

    if (img.empty())
    {
        cout << "Could not load image!" << endl;
        return -1;
    }

    namedWindow("Original", WINDOW_NORMAL);
    imshow("Original", img);

    // Step 2: Convert to grayscale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    imshow("Gray Image", gray);

    // Step 3: Apply blur to reduce noise
    Mat blurred;
    GaussianBlur(gray, blurred, Size(1, 1), 0);
    imshow("Blur Image", blurred);

    // cout << "Original Image: " << endl << img << endl << endl;
    // cout << "Gray Image: " << endl << gray << endl << endl;
    // cout << "Blurred Image: " << endl << blurred << blurred << endl;

    Mat edges;
    Canny(blurred, edges, 100, 150);

    imshow("Edges", edges);

    // Step 4: Apply thresholding
    Mat thresh;
    threshold(edges, thresh, 127, 255, THRESH_BINARY);
    imshow("Thresh", thresh);

    // Step 5: Find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // drawContours(img, contours, -1, Scalar(0, 255, 0), 2);
    // imshow("Original With Contours", img);

    // Process each contour (should be just one in your case)
    for (int i = 0; i < contours.size(); i++)
    {
        // Approximate the contour to a polygon
        vector<Point> approx;

        double peri = arcLength(contours[i], true);
        // approxPolyDP(contours[i], approx, 0.04 * peri, true);
        approxPolyDP(contours[i], approx, 10, true);

        cout << "approx points: ";
        for (int j = 0; j < approx.size(); j++)
        {
            cout << "x: " << approx[j].x << ", y: " << approx[j].y << endl;
            // img.at<Vec3b>(approx[j].x, approx[j].y) = red_color;
            circle(img, Point(approx[j].x, approx[j].y), 10, Scalar(0, 0, 255));
        }

        int vertices = approx.size();
        cout << "contours[i] size: " << contours[i].size() << " - vertices: " << vertices << endl;

        // Determine shape based on vertices
        string shape;

        if (vertices == 3)
        {
            shape = "Triangle";
        }
        else if (vertices == 4)
        {
            // Check if it's square or rectangle
            Rect boundRect = boundingRect(approx);
            double aspectRatio = (double)boundRect.width / boundRect.height;

            if (aspectRatio >= 0.95 && aspectRatio <= 1.05)
            {
                shape = "Square";
            }
            else
            {
                shape = "Rectangle";
            }
        }
        else if (vertices > 7)
        {
            // Circle has many vertices after approximation
            shape = "Unknown";

            Rect rect = boundingRect(approx);

            Point center = Point(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f);
            cout << "center: " << center << endl;

            vector<double> distances;
            for (const Point &p : approx)
            {
                distances.push_back(norm(p - center));
            }

            double meanRadius = 0;
            for (double d : distances)
            {
                cout << "distance: " << d << endl;
                meanRadius += d;
            }
            meanRadius /= distances.size();
            cout << "meanRadius: " << meanRadius << endl;

            double maxError = 0;
            for (double d : distances)
            {
                maxError = max(maxError, abs(d - meanRadius));
                cout << "abs(d - meanRadius): " << abs(d - meanRadius) << endl;
            }
            cout << "maxError: " << maxError << endl;

            if (maxError < 5.0)
            {
                shape = "Circle";
            }
        }
        else
        {
            shape = "Unknown";
        }

        // Draw the contour and label
        drawContours(img, contours, i, Scalar(0, 255, 0), 2);

        // Get centroid to place text
        Moments M = moments(contours[i]);
        int cx = int(M.m10 / M.m00);
        int cy = int(M.m01 / M.m00);

        putText(img, shape, Point(cx - 50, cy),
                FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 0, 0), 2);

        imshow("Original with Contours", img);
        cout << "Detected Shape: " << shape << endl;
    }

    waitKey(0);
    destroyAllWindows();

    return 0;
}