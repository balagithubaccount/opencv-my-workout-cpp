#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/io/pcd_io.h>
using namespace std;

int main()
{
    // Declaration
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudXYZ(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ> filterCloudXYZ;

    // Fill in the cloud data
    cloudXYZ->width = 20;
    cloudXYZ->height = 1;
    cloudXYZ->resize(cloudXYZ->width * cloudXYZ->height);

    int val = -9;
    for (auto &p : *cloudXYZ)
    {
        p.x = val;
        p.y = val + 1;
        p.z = val + 2;

        ++val;
    }

    pcl::io::savePCDFile("sourceCloud.pcd", *cloudXYZ);

    cout << "cloudXYZ - Before PassThrough filter: " << endl;
    for (const auto &p : *cloudXYZ)
    {
        cout << "x: " << p.x << ", y: " << p.y << ", z: " << p.z << endl;
    }

    pcl::PassThrough<pcl::PointXYZ> passThroughXYZ;

    passThroughXYZ.setInputCloud(cloudXYZ);
    passThroughXYZ.setFilterFieldName("x");
    passThroughXYZ.setFilterLimits(1, 5);
    passThroughXYZ.setFilterLimitsNegative(true);
    passThroughXYZ.filter(filterCloudXYZ);

    pcl::io::savePCDFileASCII("filteredCloud.pcd", filterCloudXYZ);

    cout << "filterCloudXYZ - After PassThrough filter: " << endl;
    for (const auto &p : filterCloudXYZ)
    {
        cout << "x: " << p.x << ", y: " << p.y << ", z: " << p.z << endl;
    }

    return 0;
}