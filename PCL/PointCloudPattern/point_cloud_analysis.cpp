#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/common/common.h>
using namespace std;
using namespace pcl;

// Analysis Point Cloud - ROI (PassThrough, PlaneFit, Depth, Angle, Inliers) (Limit values unit in meters)(ROI value in cm)
void findROIDetails(PointCloud<PointXYZ>::Ptr &cloud, const int &roiSize,
                    const float &depthFilterLimitMin, const float &depthFilterLimitMax)
{
    // Slized Point Cloud Object along z-axis.
    PointCloud<PointXYZ>::Ptr slizedCloud(new PointCloud<PointXYZ>);

    // PassThrough: Cut the point cloud along z axis (height 0.2m)
    PassThrough<PointXYZ> passThrough;
    passThrough.setInputCloud(cloud);
    passThrough.setFilterFieldName("z");
    passThrough.setFilterLimits(depthFilterLimitMin, depthFilterLimitMax); // values unit in meter
    passThrough.setNegative(false);                                        // keep only given limits.
    passThrough.filter(*slizedCloud);

    cout << "Slized(z-axis) cloud points size: " << slizedCloud->size() << endl;

    if (slizedCloud->size() <= 0)
    {
        cout << "Slizing point cloud along z axis error: " << endl;
        return;
    }

    // Save the Slized Point Cloud Data
    io::savePCDFileASCII("slizedCloudZ.pcd", *slizedCloud);

    string range;

    cout << "Along x and y axis slizing range: " << (roiSize / 2) / 100.0 << " meter." << endl;
    PointCloud<PointXYZ>::Ptr slizedXYCloud(new PointCloud<PointXYZ>);

    // PassThrough: Slize the point cloud along x axis.
    passThrough.setInputCloud(slizedCloud);
    passThrough.setFilterFieldName("x");
    passThrough.setFilterLimits((-roiSize / 2) / 100.0, (roiSize / 2) / 100.0);
    passThrough.setNegative(false);
    passThrough.filter(*slizedXYCloud);

    // PassThrough: Slize the point cloud along y axis.
    passThrough.setInputCloud(slizedXYCloud);
    passThrough.setFilterFieldName("y");
    passThrough.setFilterLimits((-roiSize / 2) / 100.0, (roiSize / 2) / 100.0);
    passThrough.setNegative(false);
    passThrough.filter(*slizedXYCloud);

    cout << "ROI Size: " << roiSize << " cm, Points size: " << slizedXYCloud->size() << endl;

    range = to_string(roiSize);
    if (slizedXYCloud->size() > 0)
    {
        io::savePCDFileASCII("slizedCloud_" + range + ".pcd", *slizedXYCloud);
    }

    // Plane Fit on the point cloud data.
    PointCloud<PointXYZ>::Ptr pCloud(new PointCloud<PointXYZ>);

    range = to_string(roiSize);
    if (io::loadPCDFile("slizedCloud_" + range + ".pcd", *pCloud) != -1)
    {
        ModelCoefficients::Ptr coefficients(new ModelCoefficients);
        PointIndices::Ptr inliers(new PointIndices);

        SACSegmentation<PointXYZ> seg;

        seg.setOptimizeCoefficients(true);
        seg.setModelType(SACMODEL_PLANE);
        seg.setMethodType(SAC_RANSAC);
        seg.setDistanceThreshold(0.02); // Distance in meter (2.0 cm)

        seg.setInputCloud(pCloud);
        seg.segment(*inliers, *coefficients);

        cout << "Plane Inliers Point Size for ROI(" << range << " cm): "
             << inliers->indices.size() << endl;

        ExtractIndices<PointXYZ> extract;

        extract.setInputCloud(pCloud);
        extract.setIndices(inliers);
        extract.setNegative(false);
        extract.filter(*pCloud);

        cout << "Plane Fit size for range - " << range << ": " << pCloud->size() << endl;

        // 1. Plane Coefficients (ax + by + cz + d = 0)
        float a = coefficients->values[0];
        float b = coefficients->values[1];
        float c = coefficients->values[2];
        float d = coefficients->values[3];

        // 2. Depth Calculation
        float normal = sqrt(a * a + b * b + c * c);
        float depth = abs(d) / normal;

        // 3. Angle Calculation
        float angleRad = acos(abs(c)) / normal;
        float angleDeg = (angleRad) * (180 / M_PI);

        cout << "Along z axis slizing size(m): " << abs(depthFilterLimitMax - depthFilterLimitMin)
             << " (" << depthFilterLimitMin << " to " << depthFilterLimitMax << ") " << endl;
        cout << "Range(RIO): " << range << " cm, Depth: " << depth << " m, Actual Depth: " << d << " m, Angle(Deg): " << angleDeg << endl;

        // Store the PCD file - Plane Fitted indices.
        if (pCloud->size() > 0)
        {
            io::savePCDFileASCII("planeFit_" + range + ".pcd", *pCloud);
        }
    }
    else
    {
        cout << "slizedCloud_" + range + ".pcd  could not load the file." << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Argument count error: " << argc << endl;
        return -1;
    }
    // Point Cloud Object
    PointCloud<PointXYZ>::Ptr cloud(new PointCloud<PointXYZ>);

    if (io::loadPCDFile(argv[1], *cloud) == -1) // argv[1] -> .pcd file path or file name
    {
        cout << "could not load the pcd file: " << argv[1] << endl;
        return -1;
    }

    PointXYZ minPoint, maxPoint;
    getMinMax3D(*cloud, minPoint, maxPoint);

    cout << "Point Cloud Min and Max values are:\n"
         << minPoint << "\n"
         << maxPoint << endl;

    float depthLimitMin;
    float depthLimitMax;
    cout << "Enter the min value for the Height(z): ";
    cin >> depthLimitMin;
    cout << "Enter the max value for the Height(z): ";
    cin >> depthLimitMax;

    if (depthLimitMin == depthLimitMax || depthLimitMin < minPoint.z || depthLimitMax > maxPoint.z)
    {
        cout << "Invalid Depth Limit Min or Max value: "
             << depthLimitMin << ", " << depthLimitMax << endl;
        return -1;
    }

    // Find the Depth and Angle for the given ROI using PassThrough Filter and PlaneFit Segmentation.
    // arguments(pcd ground cloud, ROI value(cm), Depth Filter Limit min and max values(m))
    findROIDetails(cloud, stoi(argv[2]), depthLimitMin, depthLimitMax);

    return 0;
}