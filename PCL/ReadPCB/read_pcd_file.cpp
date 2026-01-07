#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
using namespace std;

int main()
{
    pcl::PointCloud<pcl::PointXYZ> cloud;

    if (pcl::io::loadPCDFile("test_pcd.pcd", cloud) == -1)
    {
        cerr << "loadPCDFile loading error: " << endl;
        return -1;
    }

    cout << "Loaded the PCD file and have " << cloud.size() << " points are " << endl;

    for (const auto &point : cloud.points)
    {
        cout << point.x << " " << point.y << " " << point.z << endl;
    }

    return 0;
}