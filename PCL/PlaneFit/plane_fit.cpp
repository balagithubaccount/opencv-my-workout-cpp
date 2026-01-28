#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
using namespace std;
using namespace pcl;

int main(int argc, char *argv[])
{
    // Point Cloud Object
    PointCloud<PointXYZ>::Ptr cloud(new PointCloud<PointXYZ>);
    PointCloud<PointXYZ>::Ptr planeCloud(new PointCloud<PointXYZ>);
    PointCloud<PointXYZ>::Ptr objectCloud(new PointCloud<PointXYZ>);
    PointCloud<PointXYZ>::Ptr passThroughCloud(new PointCloud<PointXYZ>);

    // Sample Data
    cloud->width = 15;
    cloud->height = 1;
    cloud->resize(cloud->width * cloud->height);

    for (auto &point : cloud->points)
    {
        point.x = (rand() % 100) / 10.0f;
        point.y = (rand() % 100) / 10.0f;
        point.z = 1.0;
    }

    if (argc > 1)
    {
        if (io::loadPCDFile(argv[1], *cloud) == -1)
        {
            cout << "could not load the pcd file: " << argv[1] << endl;
        }
    }

    // Store the Plane coefficients x,y,z and d values (ax + by + cz + d = 0)
    ModelCoefficients::Ptr coefficients(new ModelCoefficients);
    PointIndices::Ptr inliers(new PointIndices);

    SACSegmentation<PointXYZ> seg;

    seg.setOptimizeCoefficients(true);
    seg.setModelType(SACMODEL_PLANE);
    seg.setMethodType(SAC_RANSAC);
    seg.setDistanceThreshold(0.002); // Distance in meter

    seg.setInputCloud(cloud);
    seg.segment(*inliers, *coefficients);

    cout << "Plane surface Point Size: " << inliers->indices.size() << endl;

    if (inliers->indices.size() == 0)
    {
        cerr << "Plane surface not found: " << endl;
    }
    else
    {
        cout << "Plane Equation: " << coefficients->values[0] << "x + "
             << coefficients->values[1] << "y + "
             << coefficients->values[2] << "z + "
             << coefficients->values[3] << " = 0" << endl;

        // for (int ind = 0; ind < inliers->indices.size(); ind++)
        // {
        //     planeCloud->push_back(cloud->points[inliers->indices[ind]]);
        // }
        // cout << "planeCloud size: " << planeCloud->width << ", " << planeCloud->height << endl;

        ExtractIndices<PointXYZ> extract;

        extract.setInputCloud(cloud);
        extract.setIndices(inliers);

        extract.setNegative(false);
        extract.filter(*planeCloud);

        extract.setNegative(true);
        extract.filter(*objectCloud);

        io::savePCDFileASCII("PlaneCloud.pcd", *planeCloud);
        io::savePCDFileASCII("ObjectCloud.pcd", *objectCloud);
    }

    PassThrough<PointXYZ> passThrough;
    passThrough.setInputCloud(cloud);
    passThrough.setFilterFieldName("x");
    passThrough.setFilterLimits(-0.1, 0.3);
    // passThrough.setNegative(true);
    passThrough.setFilterLimitsNegative(true);
    passThrough.filter(*passThroughCloud);

    io::savePCDFileASCII("passThroughCloud.pcd", *passThroughCloud);

    return 0;
}