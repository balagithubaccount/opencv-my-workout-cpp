#include <iostream>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
using namespace std;
using namespace pcl;

int main()
{
    // Point Cloud Object
    PointCloud<PointXYZ>::Ptr cloud(new PointCloud<PointXYZ>);

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

    ModelCoefficients::Ptr coefficients(new ModelCoefficients);
    PointIndices::Ptr inliers(new PointIndices);

    SACSegmentation<PointXYZ> seg;

    seg.setOptimizeCoefficients(true);
    seg.setModelType(SACMODEL_PLANE);
    seg.setMethodType(SAC_RANSAC);
    seg.setDistanceThreshold(0.01);

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
    }

    return 0;
}