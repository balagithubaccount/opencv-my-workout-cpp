#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/extract_indices.h>
using namespace std;
using namespace pcl;

// Find the pattern for the given point cloud data.
void findPattern(PointCloud<PointXYZ>::Ptr &cloud)
{
    // Slized Point Cloud Object along z-axis.
    PointCloud<PointXYZ>::Ptr slizedCloud(new PointCloud<PointXYZ>);

    // PassThrough: Cut the point cloud along z axis (height 0.2m)
    PassThrough<PointXYZ> passThrough;
    passThrough.setInputCloud(cloud);
    passThrough.setFilterFieldName("z");
    passThrough.setFilterLimits(1.4, 1.5);
    passThrough.setNegative(false); // keep only 0.0 to 0.2
    passThrough.filter(*slizedCloud);

    // Save the Slized Point Cloud Data
    io::savePCDFileASCII("slizedCloudZ.pcd", *slizedCloud);

    for (int width = 30; width <= 60; width += 10)
    {
        cout << "Along x and y axis slizing range: " << (width / 2) / 100.0 << endl;
        // PassThrough: Slize the point cloud along x axis.
        passThrough.setInputCloud(slizedCloud);
        passThrough.setFilterFieldName("x");
        passThrough.setFilterLimits((-width / 2) / 100.0, (width / 2) / 100.0);
        passThrough.setNegative(false);
        passThrough.filter(*slizedCloud);

        // PassThrough: Slize the point cloud along y axis.
        passThrough.setInputCloud(slizedCloud);
        passThrough.setFilterFieldName("y");
        passThrough.setFilterLimits((-width / 2) / 100.0, (width / 2) / 100.0);
        passThrough.setNegative(false);
        passThrough.filter(*slizedCloud);

        cout << "width: " << width << ", size: " << slizedCloud->size() << endl;

        string range = to_string(width);
        if (slizedCloud->size() > 0)
        {
            io::savePCDFileASCII("slizedCloud_" + range + ".pcd", *slizedCloud);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Argument count error: " << argc << endl;
        return -1;
    }
    // Point Cloud Object
    PointCloud<PointXYZ>::Ptr cloud(new PointCloud<PointXYZ>);

    if (io::loadPCDFile(argv[1], *cloud) == -1)
    {
        cout << "could not load the pcd file: " << argv[1] << endl;
        return -1;
    }

    findPattern(cloud);
    return 0;
}