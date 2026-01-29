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

struct PlaneCoefficients
{
    int size;
    ModelCoefficients::Ptr modelCoefficients;
};

// Find the pattern for the given point cloud data.
void findPattern(PointCloud<PointXYZ>::Ptr &cloud)
{
    // Slized Point Cloud Object along z-axis.
    PointCloud<PointXYZ>::Ptr slizedCloud(new PointCloud<PointXYZ>);
    vector<PlaneCoefficients> PlaneCoefficientsList;

    // PassThrough: Cut the point cloud along z axis (height 0.2m)
    PassThrough<PointXYZ> passThrough;
    passThrough.setInputCloud(cloud);
    passThrough.setFilterFieldName("z");
    passThrough.setFilterLimits(1.4, 1.6); // 1.6 - 1.4 = 0.2 m  or 20 cm
    passThrough.setNegative(false);        // keep only given limits.
    passThrough.filter(*slizedCloud);

    cout << "Slized(z-axis) cloud size: " << slizedCloud->size() << endl;

    // Save the Slized Point Cloud Data
    io::savePCDFileASCII("slizedCloudZ.pcd", *slizedCloud);

    string range;

    // PassThrough the point cloud datd.
    for (int width = 30; width <= 60; width += 10)
    {
        cout << "Along x and y axis slizing range: " << (width / 2) / 100.0 << endl;
        PointCloud<PointXYZ>::Ptr slizedXYCloud(new PointCloud<PointXYZ>);

        // PassThrough: Slize the point cloud along x axis.
        passThrough.setInputCloud(slizedCloud);
        passThrough.setFilterFieldName("x");
        passThrough.setFilterLimits((-width / 2) / 100.0, (width / 2) / 100.0);
        passThrough.setNegative(false);
        passThrough.filter(*slizedXYCloud);

        // PassThrough: Slize the point cloud along y axis.
        passThrough.setInputCloud(slizedXYCloud);
        passThrough.setFilterFieldName("y");
        passThrough.setFilterLimits((-width / 2) / 100.0, (width / 2) / 100.0);
        passThrough.setNegative(false);
        passThrough.filter(*slizedXYCloud);

        cout << "width: " << width << ", size: " << slizedXYCloud->size() << endl;

        range = to_string(width);
        if (slizedXYCloud->size() > 0)
        {
            io::savePCDFileASCII("slizedCloud_" + range + ".pcd", *slizedXYCloud);
        }
    }

    // Plane Fit on the point cloud data.
    for (int width = 30; width <= 60; width += 10)
    {
        PointCloud<PointXYZ>::Ptr pCloud(new PointCloud<PointXYZ>);
        PlaneCoefficients pc;
        pc.size = width;

        range = to_string(width);
        if (io::loadPCDFile("slizedCloud_" + range + ".pcd", *pCloud) != -1)
        {
            ModelCoefficients::Ptr coefficients(new ModelCoefficients);
            PointIndices::Ptr inliers(new PointIndices);

            SACSegmentation<PointXYZ> seg;

            seg.setOptimizeCoefficients(true);
            seg.setModelType(SACMODEL_PLANE);
            seg.setMethodType(SAC_RANSAC);
            seg.setDistanceThreshold(0.002); // Distance in meter (0.2 cm)

            seg.setInputCloud(pCloud);
            seg.segment(*inliers, *coefficients);

            cout << "Plane Inliers Point Size for width-" << width << ": "
                 << inliers->indices.size() << endl;

            ExtractIndices<PointXYZ> extract;

            extract.setInputCloud(pCloud);
            extract.setIndices(inliers);
            extract.setNegative(false);
            extract.filter(*pCloud);

            pc.modelCoefficients = coefficients;

            cout << "Plane Fit size for range - " << range << ": " << pCloud->size() << endl;

            // Store the PCD file - Plane Fitted indices.
            // if (pCloud->size() > 0)
            // {
            //     io::savePCDFileASCII("planeFit_" + range + ".pcd", *pCloud);
            //     cout << "Plane equation: " << *coefficients << endl;
            // }

            PlaneCoefficientsList.push_back(pc);
        }
        else
        {
            cout << "slizedCloud_" + range + ".pcd  could not load the file." << endl;
        }
    }
    cout << "\nPassThrough Size\tX\tY\tZ\tD" << endl;
    for (auto &pc : PlaneCoefficientsList)
    {
        cout << pc.size << "\t";
        for (auto &val : pc.modelCoefficients->values)
        {
            cout << val << "\t";
        }
        cout << endl;
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