#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
using namespace std;

int main()
{
    pcl::PointCloud<pcl::PointXYZ> cloudXYZ;
    cloudXYZ.width = 5;
    cloudXYZ.height = 1;
    cloudXYZ.resize(cloudXYZ.width * cloudXYZ.height);

    for (auto &p : cloudXYZ)
    {
        p.x = 1024 * rand() / (RAND_MAX / 2.0f);
        p.y = 1024 * rand() / (RAND_MAX / 3.0f);
        p.z = 1024 * rand() / (RAND_MAX / 3.0f);
    }

    cout << "cloudXYZ width: " << cloudXYZ.width << ", size: " << cloudXYZ.size() << ", height: "
         << cloudXYZ.height << ",dense: " << cloudXYZ.is_dense << endl;

    pcl::io::savePCDFileASCII("cloudXYZ.pcd", cloudXYZ);

    pcl::PointCloud<pcl::PointXYZI> cloudXYZI;
    cloudXYZI.width = 6;
    cloudXYZI.height = 1;
    cloudXYZI.resize(cloudXYZI.width * cloudXYZI.height);

    for (auto &p : cloudXYZI)
    {
        p.x = 1024 * rand() / (RAND_MAX / 2.0f);
        p.y = 1024 * rand() / (RAND_MAX / 3.0f);
        p.z = 1024 * rand() / (RAND_MAX / 3.0f);
        p.intensity = rand();
    }

    cout << "cloudXYZI width: " << cloudXYZI.width << ", size: " << cloudXYZI.size() << ", height: "
         << cloudXYZI.height << ",dense: " << cloudXYZI.is_dense << endl;

    pcl::io::savePCDFileASCII("cloudXYZI.pcd", cloudXYZI);

    pcl::PointCloud<pcl::PointXYZRGB> cloudXYZRGB;
    cloudXYZRGB.width = 4;
    cloudXYZRGB.height = 1;
    cloudXYZRGB.resize(cloudXYZRGB.width * cloudXYZRGB.height);

    for (auto &p : cloudXYZRGB)
    {
        p.x = 1024 * rand() / (RAND_MAX / 2.0f);
        p.y = 1024 * rand() / (RAND_MAX / 2.0f);
        p.z = 1024 * rand() / (RAND_MAX / 2.0f);
        p.r = 255;
        p.g = 1;
        p.b = 0;
    }

    cout << "cloudXYZRGB width: " << cloudXYZRGB.width << ", size: " << cloudXYZRGB.size() << ", height: "
         << cloudXYZRGB.height << ",dense: " << cloudXYZRGB.is_dense << endl;

    pcl::io::savePCDFileASCII("cloudXYZRGB.pcd", cloudXYZRGB);

    return 0;
}