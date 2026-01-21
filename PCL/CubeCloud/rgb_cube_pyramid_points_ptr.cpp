#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vector>
#include <cmath>
using namespace std;

static float cubeWidth;
vector<pcl::PointXYZ> selectedPoints;

// For make line with point between start and end point.(18 points)
void addPointsToEdge(const pcl::PointXYZRGB startPoint, const pcl::PointXYZRGB endPoint, const char &fieldName,
                     pcl::PointCloud<pcl::PointXYZRGB> &cloud, int &index)
{
    cout << "startPoint: " << startPoint << ", endPoint: " << endPoint << ", fieldName: " << fieldName << ", index: " << index << endl;

    // sign of the distance variable is represent the direction to generate the points.
    float distance;

    // make points along x axis
    if (fieldName == 'x')
    {
        // move the index to next of the start point
        index--;

        // generate the 18 points between start and end points.
        distance = abs((startPoint.x - endPoint.x) / 19);
        cout << "distance: " << distance << endl;

        if (startPoint.x < endPoint.x)
        {
            distance *= 1; // make points along x axis from left to right.
            for (int it = 1; it <= 18; it++)
            {
                cloud.points[index++] = pcl::PointXYZRGB(startPoint.x + (distance * it), startPoint.y, startPoint.z, startPoint.r, startPoint.g, startPoint.b);
            }
        }
        else if (startPoint.x > endPoint.x)
        {
            distance *= -1; // make points along x axis from right to left.
            for (int it = 1; it <= 18; it++)
            {
                cloud.points[index++] = pcl::PointXYZRGB(startPoint.x + (distance * it), startPoint.y, startPoint.z, startPoint.r, startPoint.g, startPoint.b);
            }
        }
        else
        {
            distance = 0;
            cerr << "Invalid start and end points: " << endl;
        }
    }
    // make points along y axis
    else if (fieldName == 'y')
    {
        // generate the 18 points between start and end points.
        distance = abs((startPoint.y - endPoint.y) / 19);
        cout << "distance: " << distance << endl;

        if (startPoint.y < endPoint.y)
        {
            // move the index to next of the start point
            index--;

            distance *= 1; // make points along y axis from bottom to top.
            for (int it = 1; it <= 18; it++)
            {
                cloud.points[index++] = pcl::PointXYZRGB(startPoint.x, startPoint.y + (distance * it), startPoint.z, startPoint.r, startPoint.g, startPoint.b);
            }
        }
        else if (startPoint.y > endPoint.y)
        {
            distance *= -1; // make points along y axis from top to bottom.
            for (int it = 1; it <= 18; it++)
            {
                cloud.points[index++] = pcl::PointXYZRGB(startPoint.x, startPoint.y + (distance * it), startPoint.z, endPoint.r, endPoint.g, endPoint.b);
            }
        }
        else
        {
            distance = 0;
            cerr << "Invalid start and end points: " << endl;
        }
    }
    // make points along z axis
    else if (fieldName == 'z')
    {
        // generate the 18 points between start and end points.
        distance = abs((startPoint.z - endPoint.z) / 19);
        cout << "distance: " << distance << endl;

        if (startPoint.z < endPoint.z)
        {
            distance *= 1; // make points along z axis from back to front.
            for (int it = 1; it <= 18; it++)
            {
                cloud.points[index++] = pcl::PointXYZRGB(startPoint.x, startPoint.y, startPoint.z + (distance * it), startPoint.r, startPoint.g, startPoint.b);
            }
        }
        else if (startPoint.z > endPoint.z)
        {
            distance *= -1; // make points along z axis from front to back.
            for (int it = 1; it <= 18; it++)
            {
                cloud.points[index++] = pcl::PointXYZRGB(startPoint.x, startPoint.y, startPoint.z + (distance * it), endPoint.r, endPoint.g, endPoint.b);
            }
        }
        else
        {
            distance = 0;
            cerr << "Invalid start and end points: " << endl;
        }
    }
    else
    {
        cerr << "Invalid fieldName: " << fieldName << endl;
    }

    // move the end point after the mid points.
    cout << "move index: " << index << endl;
    if (!((fieldName == 'y' && startPoint.y > endPoint.y) || (fieldName == 'z')))
    {
        cloud.points[index++] = pcl::PointXYZRGB(endPoint);
    }
}

// This function is called automatically when you click on a point in the viewer.
void pointPickingCallback(const pcl::visualization::PointPickingEvent &event)
{
    // Step 1: Check if the click actually hit a point (not empty space)
    if (event.getPointIndex() == -1)
    {
        cout << "No point was clicked.\nTry clicking directly on a point." << endl;
        return;
    }

    // Step 2: Get the 3D coordinates of the  clicked point.
    float x, y, z;
    event.getPoint(x, y, z);

    // Create a PCL point object with these coordinates
    pcl::PointXYZ clickedPoint(x, y, z);
    // cout << "\n=================================================" << endl;
    cout << "\nPoint Clicked at: (" << x << ", " << y << ", " << z << ")" << endl;

    // Step 3: Process based on how many points we already have

    if (selectedPoints.size() < 2) // we need two points total
    {
        // Add current point to our list
        selectedPoints.push_back(clickedPoint);

        if (selectedPoints.size() == 1)
        {
            // First point selected
            cout << "First point selected!" << endl;
            cout << "Now click on a second point..." << endl;
        }
        else if (selectedPoints.size() == 2)
        {
            // Second point selected. Now calculate the Distance
            cout << "Second point selected!" << endl;

            float dx = selectedPoints[1].x - selectedPoints[0].x;
            float dy = selectedPoints[1].y - selectedPoints[0].y;
            float dz = selectedPoints[1].z - selectedPoints[0].z;

            float distance = sqrt(dx * dx + dy * dy + dz * dz);

            cout << "***Distance Calculation***" << endl;
            cout << "Point 1: (" << selectedPoints[0].x << ", " << selectedPoints[0].y << ", " << selectedPoints[0].z << ")" << endl;
            cout << "Point 2: (" << selectedPoints[1].x << ", " << selectedPoints[1].y << ", " << selectedPoints[1].z << ")" << endl;
            cout << "Distance: " << distance << " m" << endl;
            cout << "=================================================\n"
                 << endl;

            // Reset for next measurement
            cout << "Click two more points to measure again..." << endl;
            selectedPoints.clear();
        }
    }
}

int main()
{
    int level; // Total number of rows in the Pyramid.
    cout << "Enter the Level(no.of.row's): ";
    cin >> level;

    cout << "Enter the width(in millimeter): ";
    cin >> cubeWidth; // in millimeter

    float xyz[3];               // store the x,y,z co-ordinate values.
    int rgb[3] = {0, 127, 255}; // store the RGB color with red, green and blue values the range (0 - 255).

    // validate the user inputs
    if (level <= 0 || cubeWidth <= 0)
    {
        cout << "Invalid Level value or width value: " << level << ":" << cubeWidth << endl;
        return -1;
    }

    // store the user input for further usecase.
    int temp_level = level;

    // set cube width value from millimeter to meter.(1000 millimeter = 1 meter)
    cubeWidth /= 1000;

    // Find the width based on the input level
    int cubeCount = 0;
    for (int lev = level; lev > 0; lev--)
    {
        cubeCount += lev;
    }
    cout << "cube count: " << cubeCount << ", cubeWidth: " << cubeWidth << endl;

    // Point Cloud Declaration.
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    // no.of.corner points per cube is 8.
    // 8 multiplied by no.of cubes. 18 for line making points for each cube with 12 edges.
    // 18*18 each faces points. each cube has 6 faces.
    cloud->width = (8 * cubeCount) + (18 * 12 * cubeCount) + (pow(18, 2) * 6 * cubeCount);
    cloud->height = 1;
    cloud->resize(cloud->width * cloud->height);

    cout << "cloud size: " << cloud->size() << endl;

    // Handle the RGB colors.
    int col_r, col_g, col_b;
    col_r = 35;
    col_g = 50;
    col_b = -10;

    int index = 0;
    // each iteration create the single row.
    for (int row = 0; row < level; row++, temp_level--)
    {
        cout << "Color r: " << rgb[0] << ", g: " << rgb[1] << ", b: " << rgb[2] << endl;
        float horiz_x = ((cubeWidth / 2) * (row));

        // each iteration create the single cube.
        for (int cube = 1; cube <= temp_level; cube++)
        {
            // set x, y and z coordinates values.
            xyz[0] = (cubeWidth * cube) + horiz_x;
            xyz[1] = cubeWidth * row;
            xyz[2] = 0;

            cout << "row: " << row << ", cube: " << cube << ", x: " << xyz[0] << endl;

            // each iteration create the single square
            for (int box_2d = 0; box_2d < 2; box_2d++)
            {
                // bottom left(origit). starting coordinates for x,y,z like origin.(0,0,0)
                cloud->points[index].x = xyz[0];
                cloud->points[index].y = xyz[1];
                cloud->points[index].z = xyz[2];

                cloud->points[index].r = rgb[0];
                cloud->points[index].g = rgb[1];
                cloud->points[index].b = rgb[2];
                index++;

                // next point bottom right x only changed, y and z unchanged.
                xyz[0] += cubeWidth;
                cloud->points[index].x = xyz[0];
                cloud->points[index].y = xyz[1];
                cloud->points[index].z = xyz[2];

                cloud->points[index].r = rgb[0];
                cloud->points[index].g = rgb[1];
                cloud->points[index].b = rgb[2];
                index++;

                // cout << "index: " << index << endl;
                // Make points bottom left to bottom right along x axis.
                addPointsToEdge(cloud->points[index - 2], cloud->points[index - 1], 'x', *cloud, index);

                // top right y only changed, x and z unchanged.
                xyz[1] += cubeWidth;
                cloud->points[index].x = xyz[0];
                cloud->points[index].y = xyz[1];
                cloud->points[index].z = xyz[2];

                cloud->points[index].r = rgb[0];
                cloud->points[index].g = rgb[1];
                cloud->points[index].b = rgb[2];
                index++;

                // cout << "index: " << index << endl;
                // Make points bottom right to top right along y axis.
                addPointsToEdge(cloud->points[index - 2], cloud->points[index - 1], 'y', *cloud, index);

                // top left x only changed, y and z unchanged.
                xyz[0] -= cubeWidth;
                cloud->points[index].x = xyz[0];
                cloud->points[index].y = xyz[1];
                cloud->points[index].z = xyz[2];

                cloud->points[index].r = rgb[0];
                cloud->points[index].g = rgb[1];
                cloud->points[index].b = rgb[2];
                index++;

                // cout << "index: " << index << endl;
                // Make points top right to top left along x axis.
                addPointsToEdge(cloud->points[index - 2], cloud->points[index - 1], 'x', *cloud, index);

                // cout << "index: " << index << endl;
                // Make points top left to bottom left along y axis.
                addPointsToEdge(cloud->points[index - 1], cloud->points[index - 58], 'y', *cloud, index);

                xyz[1] -= cubeWidth;
                xyz[2] += cubeWidth;
            }

            // For make Point cloud for 'Z' axis.(connect the corners for back and front square)
            for (int connectLine = 0, subInd = 1; connectLine <= 3; connectLine++, subInd++)
            {
                addPointsToEdge(cloud->points[index - (connectLine * 18) - (subInd * 19)],
                                cloud->points[index - (connectLine * 18) - ((subInd + 4) * 19)],
                                'z', *cloud, index);
                // cout << "connectLine: " << subInd << ", index: " << index << endl;
            }

            // For make Point cloud to back face on the cube.
            for (int backface = 1; backface <= 18; backface++)
            {
                addPointsToEdge(cloud->points[index - ((backface + 3) * 18) - (5 * 19) - backface],
                                cloud->points[index - ((backface + 3) * 18) - (8 * 19) + backface],
                                'y', *cloud, index);
            }

            // For make Point cloud to back face on the cube.
            for (int frontface = 1; frontface <= 18; frontface++)
            {
                // 18 x 18 backface point cloud -> 324
                addPointsToEdge(cloud->points[index - 324 - ((frontface + 3) * 18) - (1 * 19) - frontface],
                                cloud->points[index - 324 - ((frontface + 3) * 18) - (4 * 19) + frontface],
                                'y', *cloud, index);
            }

            // For make Point cloud to top face on the cube.
            for (int topface = 1; topface <= 18; topface++)
            {
                // 18 x 18 x 2 backface and frontface point cloud -> 648
                addPointsToEdge(cloud->points[index - 648 - ((topface + 3) * 18) - (1 * 19) - topface],
                                cloud->points[index - 648 - ((topface + 3) * 18) - (5 * 19) - topface],
                                'z', *cloud, index);
            }

            // For make Point cloud to right face on the cube.
            for (int rightface = 1; rightface <= 18; rightface++)
            {
                // 18 x 18 x 3 backface, frontface and topface point cloud -> 972
                addPointsToEdge(cloud->points[index - 972 - ((rightface + 3) * 18) - (2 * 19) - rightface],
                                cloud->points[index - 972 - ((rightface + 3) * 18) - (6 * 19) - rightface],
                                'z', *cloud, index);
            }

            // For make Point cloud to bottom face on the cube.
            for (int botface = 1; botface <= 18; botface++)
            {
                // 18 x 18 x 3 backface, frontface, topface and rightface point cloud -> 1296
                addPointsToEdge(cloud->points[index - 1296 - ((botface + 3) * 18) - (4 * 19) + botface],
                                cloud->points[index - 1296 - ((botface + 3) * 18) - (8 * 19) + botface],
                                'z', *cloud, index);
            }

            // For make Point cloud to left face on the cube.
            for (int leftface = 1; leftface <= 18; leftface++)
            {
                // 18 x 18 x 3 backface, frontface, topface, rightface and bottomface point cloud -> 1620
                addPointsToEdge(cloud->points[index - 1620 - ((leftface + 3) * 18) - (1 * 19) + leftface],
                                cloud->points[index - 1620 - ((leftface + 3) * 18) - (5 * 19) + leftface],
                                'z', *cloud, index);
            }
            // cout << "end index: " << index << endl;
        }

        // Handle the color RGB values. if exceed 255 and less 0
        col_r = (rgb[0] + col_r < 0 || rgb[0] < 0) ? 35 : (rgb[0] + col_r > 255 || rgb[0] > 255) ? -35
                                                                                                 : col_r;
        col_g = (rgb[1] + col_g < 0 || rgb[1] < 0) ? 50 : (rgb[1] + col_g > 255 || rgb[1] > 255) ? -50
                                                                                                 : col_g;
        col_b = (rgb[2] + col_b < 0 || rgb[2] < 0) ? 10 : (rgb[2] + col_b > 255 || rgb[2] > 255) ? -10
                                                                                                 : col_b;

        rgb[0] += col_r;
        rgb[1] += col_g;
        rgb[2] += col_b;
    }

    // print point cloud data's.
    // for (const auto &p : cloud)
    // {
    //     cout << "x: " << p.x << ", y: " << p.y << ", z: " << p.z << ", RGB: " << (int)p.r << " " << (int)p.g << " " << (int)p.b << endl;
    // }

    pcl::io::savePCDFileASCII("RGBCubeCloud.pcd", *cloud);
    cout << "Cube Cloud Data saved." << endl;

    // Create visualizer
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Cube"));

    // pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb_hander(cloud);
    viewer->addPointCloud<pcl::PointXYZRGB>(cloud, "cubecloud");

    // Set point size for Point Cloud Points.
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cubecloud");

    viewer->registerPointPickingCallback(pointPickingCallback);

    cout << "\n*** INSTRUCTIONS ***" << std::endl;
    cout << "1. Shift + Click on any point to select it" << std::endl;

    viewer->spin();
    // while (!viewer->wasStopped())
    // {
    //     viewer->spinOnce(100);
    // }

    return 0;
}