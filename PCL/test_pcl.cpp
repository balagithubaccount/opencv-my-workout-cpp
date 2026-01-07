#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <iostream>

int main()
{
    pcl::PointCloud<pcl::PointXYZ> cloud;

    cloud.push_back(pcl::PointXYZ(1.0f, 2.0f, 3.0f));
    std::cout << "PCL is working, points = " << cloud.size() << std::endl;

    return 0;
}