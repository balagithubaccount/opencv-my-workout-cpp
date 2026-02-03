#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <opencv2/opencv.hpp>
using namespace std;

void depthToCloud(cv::Mat depthImage, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, cv::Mat Qmatrix)
{
    cv::Mat depth;

    depthImage.convertTo(depth, CV_64F);

    /*
    QMatrix(0,3) - cx - center of x
    QMatrix(1,3) - cy - center of y
    QMatrix(2,3) - focal length
    QMatrix(3,2) - 1 / baseline (For stereo camera's)
    */

    double focal_length = Qmatrix.at<double>(2, 3);
    double cx = Qmatrix.at<double>(0, 3);
    double cy = Qmatrix.at<double>(1, 3);
    cloud->points.resize(depth.size().height * depth.size().width);
    int index = 0;
    // Basically, now 3D Projected values are in Mat, let's convert to Point Cloud Data Mat->PC.
    for (int j = 0; j < depth.size().height; j++)
    {
        for (int i = 0; i < depth.size().width; i++)
        {
            if (depth.at<double>(cv::Point(i, j)) == 0)
            {
                index++;
                continue;
            }
            pcl::PointXYZ point;
            /*
            2d to 3d formula can be found from the opencv topic "Camera Calibration and 3D Reconstruction".
            Link here : https://docs.opencv.org/master/d9/d0c/group__calib3d.html
            */
            point.z = depth.at<double>(cv::Point(i, j)) / 1000;
            point.x = ((i + cx) / focal_length) * point.z;
            point.y = ((j + cy) / focal_length) * point.z;

            cloud->points[index++] = point;
            // cloud->points.push_back(point);
        }
    }

    cloud->width = depth.size().width;
    cloud->height = depth.size().height;

    pcl::io::savePCDFileASCII("GROUND.pcd", *cloud);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Invalid Argument count: " << argc << endl;
        return -1;
    }

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cv::Mat depthImage = cv::imread(argv[1], cv::IMREAD_UNCHANGED); // Depth Image file .PFM 

    if (depthImage.empty())
    {
        cout << "Could not read the image: " << argv[1] << endl;
        return -1;
    }

    cv::Mat qMatrix = (cv::Mat_<double>(4, 4) << 1.000000, 0.000000, 0.000000, -315.702484,
                       0.000000, 1.000000, 0.000000, -236.546494,
                       0.000000, 0.000000, 0.000000, 574.150146,
                       0.000000, 0.000000, 0.000000, 0.000000);

    depthToCloud(depthImage, cloud, qMatrix);
    return 0;
}