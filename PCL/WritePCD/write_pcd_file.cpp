#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
using namespace std;

int main()
{
    pcl::PointCloud<pcl::PointXYZ> cloud;

    cloud.push_back(pcl::PointXYZ(1, 1, 1));
    cloud.push_back(pcl::PointXYZ(1, 1, 1));
    cloud.push_back(pcl::PointXYZ(1, 1, 1));

    cout << "cloud size: " << cloud.size() << endl;
    cout << "cloud width: " << cloud.width << endl;
    cout << "cloud height: " << cloud.height << endl;

    cout << pcl::io::savePCDFileASCII("test_pcd.pcd", cloud);

    return 0;
}