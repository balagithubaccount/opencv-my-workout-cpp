#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
using namespace std;

int main()
{
    // Testing PointXYZ type cloud data.
    pcl::PointCloud<pcl::PointXYZ> cloud;

    cloud.push_back(pcl::PointXYZ(1, 1, 1));
    cloud.push_back(pcl::PointXYZ(1, 1, 1));
    cloud.push_back(pcl::PointXYZ(1, 1, 1));

    cout << "cloud size: " << cloud.size() << endl;
    cout << "cloud width: " << cloud.width << endl;
    cout << "cloud height: " << cloud.height << endl;

    cout << pcl::io::savePCDFileASCII("test_pcd.pcd", cloud);

    pcl::PointCloud<pcl::PointXYZ> pCloud;

    pCloud.width = 10;
    pCloud.height = 1;
    pCloud.is_dense = false;
    pCloud.resize(pCloud.width * pCloud.height);

    for (auto &p : pCloud)
    {
        p.x = 1024 * rand() / (RAND_MAX + 1.0f);
        p.y = 1024 * rand() / (RAND_MAX + 1.0f);
        p.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    pcl::io::savePCDFile("pcd_file.pcd", pCloud);
    pcl::io::savePCDFileASCII("pcd_file_ascii.pcd", pCloud);// difference
    pcl::io::savePCDFileBinary("pcd_file_binary.pcd", pCloud);

    for (const auto &point : pCloud)
    {
        cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << endl;
    }

    // cube point cloud data
    pcl::PointCloud<pcl::PointXYZ> cubeCloud;

    cubeCloud.push_back(pcl::PointXYZ(0, 0, 0));
    cubeCloud.push_back(pcl::PointXYZ(1, 0, 0));
    cubeCloud.push_back(pcl::PointXYZ(2, 0, 0));
    cubeCloud.push_back(pcl::PointXYZ(3, 0, 0));

    cubeCloud.push_back(pcl::PointXYZ(0, 0, 0));
    cubeCloud.push_back(pcl::PointXYZ(0, 1, 0));
    cubeCloud.push_back(pcl::PointXYZ(0, 2, 0));
    cubeCloud.push_back(pcl::PointXYZ(0, 3, 0));

    cubeCloud.push_back(pcl::PointXYZ(0, 0, 0));
    cubeCloud.push_back(pcl::PointXYZ(0, 0, 1));
    cubeCloud.push_back(pcl::PointXYZ(0, 0, 2));
    cubeCloud.push_back(pcl::PointXYZ(0, 0, 3));

    cubeCloud.push_back(pcl::PointXYZ(3, 0, 1));
    cubeCloud.push_back(pcl::PointXYZ(3, 0, 2));
    cubeCloud.push_back(pcl::PointXYZ(3, 0, 3));
    // cubeCloud.push_back(pcl::PointXYZ(0, 0, 0));

    cubeCloud.push_back(pcl::PointXYZ(2, 0, 3));
    cubeCloud.push_back(pcl::PointXYZ(1, 0, 3));
    cubeCloud.push_back(pcl::PointXYZ(0, 0, 3));
    // cubeCloud.push_back(pcl::PointXYZ(0, 0, 0));

    cubeCloud.push_back(pcl::PointXYZ(0, 1, 3));
    cubeCloud.push_back(pcl::PointXYZ(0, 2, 3));
    cubeCloud.push_back(pcl::PointXYZ(0, 3, 3));
    // cubeCloud.push_back(pcl::PointXYZ(0, 0, 0));

    cubeCloud.push_back(pcl::PointXYZ(0, 3, 2));
    cubeCloud.push_back(pcl::PointXYZ(0, 3, 1));
    cubeCloud.push_back(pcl::PointXYZ(0, 3, 0));
    // cubeCloud.push_back(pcl::PointXYZ(0, 0, 0));

    cubeCloud.push_back(pcl::PointXYZ(1, 3, 0));
    cubeCloud.push_back(pcl::PointXYZ(2, 3, 0));
    cubeCloud.push_back(pcl::PointXYZ(3, 3, 0));
    // cubeCloud.push_back(pcl::PointXYZ(0, 0, 0));

    cubeCloud.push_back(pcl::PointXYZ(3, 3, 1));
    cubeCloud.push_back(pcl::PointXYZ(3, 3, 2));
    cubeCloud.push_back(pcl::PointXYZ(3, 3, 3));
    // cubeCloud.push_back(pcl::PointXYZ(0, 0, 0));

    cubeCloud.push_back(pcl::PointXYZ(2, 3, 3));
    cubeCloud.push_back(pcl::PointXYZ(1, 3, 3));
    cubeCloud.push_back(pcl::PointXYZ(0, 3, 3));
    // cubeCloud.push_back(pcl::PointXYZ(0, 0, 0));

    cubeCloud.push_back(pcl::PointXYZ(3, 2, 3));
    cubeCloud.push_back(pcl::PointXYZ(3, 1, 3));
    cubeCloud.push_back(pcl::PointXYZ(3, 0, 3));

    cubeCloud.push_back(pcl::PointXYZ(3, 3, 0));
    cubeCloud.push_back(pcl::PointXYZ(3, 2, 0));
    cubeCloud.push_back(pcl::PointXYZ(3, 1, 0));
    cubeCloud.push_back(pcl::PointXYZ(3, 0, 0));

    pcl::io::savePCDFileASCII("cubeCloud.pcd", cubeCloud);

    cout << endl
         << "cubeCloud size: " << cubeCloud.size() << ", width: "
         << cubeCloud.width << ", height: " << cubeCloud.height << ", points size: " << cubeCloud.points.size() << endl;

    return 0;
}