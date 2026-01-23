#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vector>
#include <cmath>
#include <vtkObject.h>
using namespace std;
using namespace pcl;

vector<PointXYZ> selectedPoints;
visualization::PCLVisualizer::Ptr viewer;

void pointPickingCallback(const visualization::PointPickingEvent &event)
{
    // This function is called automatically when user click on a point in the viewer

    // Step 1: Check if the click actually hit a point (not empty space)
    if (event.getPointIndex() == -1)
    {
        cout << "No point was clicked. Try clicking directly on a point." << endl;
        return;
    }

    // Step 2: Get the 3D coordinates from the clicked point
    float x, y, z;
    event.getPoint(x, y, z);

    // Create a PCL Point object with these coordinates
    PointXYZ clickedPoint(x, y, z);

    cout << "\nPoint Clicked at: (" << x << ", " << y << ", " << z << ")" << endl;

    if (selectedPoints.size() <= 2)
    {
        // Add this point to our list
        selectedPoints.push_back(clickedPoint);

        if (selectedPoints.size() == 1)
        {
            // First Point Selected
            cout << "First Point Selected!" << endl;
            cout << "Now click on a second point..." << endl;

            // Add the sphere shape for first selected point with radius and a Red color.
            viewer->addSphere(clickedPoint, 0.02, 1.0, 0, 0, "sphere1");
        }
        else if (selectedPoints.size() == 2)
        {
            // Second Point Selected
            cout << "Second Point Selected!" << endl;

            // Add the sphere shape for second selected piont with radius and a Green color.
            viewer->addSphere(clickedPoint, 0.02, 0, 1.0, 0, "sphere2");

            // Add the line between two selected points.
            viewer->addLine(selectedPoints[0], selectedPoints[1], 0, 0, 1.0, "line");

            // Calculate Distance between two selected points using Euclidean distance formula
            // Distance = squrt((x2-x1)² + (y2-y1)² + (z2-z1)²);

            float dx = selectedPoints[1].x - selectedPoints[0].x;
            float dy = selectedPoints[1].y - selectedPoints[0].y;
            float dz = selectedPoints[1].z - selectedPoints[0].z;

            float distance = sqrt(dx * dx + dy * dy + dz * dz);

            // Distance Calculation
            cout << "\n***Distance Calculation***" << endl;
            cout << "Point 1: (" << selectedPoints[0].x << "," << selectedPoints[0].y << "," << selectedPoints[0].z << ")" << endl;
            cout << "Point 2: (" << selectedPoints[1].x << "," << selectedPoints[1].y << "," << selectedPoints[1].z << ")" << endl;
            cout << "Distance: " << distance << " units.(meter)" << endl;
            cout << "======================================\n";
        }
        else
        {
            // Remove Sphere and Line and clear the selected point list.
            selectedPoints.clear();

            viewer->removeShape("sphere1");
            viewer->removeShape("sphere2");
            viewer->removeShape("line");

            // First Point Selected.
            selectedPoints.push_back(clickedPoint);
            
            // First Point Selected
            cout << "First Point Selected!" << endl;
            cout << "Now click on a second point..." << endl;

            // Add the sphere shape for first selected point with radius and a Red color.
            viewer->addSphere(clickedPoint, 0.02, 1.0, 0, 0, "sphere1");
        }
    }
}

int main(int argc, char *argv[])
{
    cout << "==== PCL Point Distance Measurement Tool ==== " << endl;

    if (argc < 2)
    {
        cout << "Mismatch argument count." << endl;
        return -1;
    }

    // Step 1: Load the Point Cloud Data from file
    PointCloud<PointXYZRGB>::Ptr cloud(new PointCloud<PointXYZRGB>);

    if (io::loadPCDFile<PointXYZRGB>(argv[1], *cloud) == -1)
    {
        cerr << "Error: Could not load point cloud file!" << endl;
        return -1;
    }

    vtkObject::GlobalWarningDisplayOff();
    cout << "Loaded point cloud with " << cloud->points.size() << " points." << std::endl;

    // Step 2: Create the visualizer window
    viewer.reset(new visualization::PCLVisualizer("Distance Measurement Tool"));

    // Step 3: Load Point Cloud Data to viewer
    viewer->addPointCloud(cloud, "cloud");

    // Set point size for better visibility
    viewer->setPointCloudRenderingProperties(visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloud");

    // Step 4: Register the callback function.
    // This connects our function to mouse click events
    viewer->registerPointPickingCallback(pointPickingCallback);

    cout << "\n*******Instructions*******" << endl;
    cout << "1. Shift + Click on a point to select it." << endl;
    cout << "2. Fist click will show a RED sphere" << endl;
    cout << "3. Second click will show a GREEN sphere and calculate distance" << endl;
    cout << "4. A BLUE line will connect the two points" << endl;
    cout << "5. Click two more points to measure again." << endl;
    cout << "6. Press 'q' to quit\n"
         << endl;

    viewer->spin();

    return 0;
}