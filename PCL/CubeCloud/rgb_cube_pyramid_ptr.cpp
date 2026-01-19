#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
using namespace std;

int main()
{
    float width = 5; // Square width.

    int level; // Total number of rows in the Pyramid.
    cout << "Enter the Level: ";
    cin >> level;

    static float xyz[3];        // store the x,y,z co-ordinate values.
    int rgb[3] = {0, 127, 255}; // store the RGB color with red, green and blue values the range (0 - 255).

    if (level <= 0)
    {
        cout << "Invalid Level(row) value: " << level << endl;
        return -1;
    }

    int temp_level = level;

    // Find the width based on the input level
    int cubeCount = 0;
    for (int lev = level; lev > 0; lev--)
    {
        cubeCount += lev;
    }
    cout << "cube count: " << cubeCount << endl;

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudPtr(new pcl::PointCloud<pcl::PointXYZRGB>);
    cloudPtr->width = 8 * cubeCount; // 8 for no.of.corner points per cube. 8 multiplied by no.of cubes.
    cloudPtr->height = 1;
    cloudPtr->resize(cloudPtr->width * cloudPtr->height);

    cout << "cloudPtr size: " << cloudPtr->size() << endl;

    // Create visualizer
    pcl::visualization::PCLVisualizer viewer("Cube Viewer");
    int lineInd = 0;
    string lineId = to_string(lineInd);

    int col_r, col_g, col_b;
    col_r = 35;
    col_g = 50;
    col_b = -10;

    int index = 0;
    for (int row = 0; row < level; row++, temp_level--)
    {
        cout << "Color r: " << rgb[0] << ", g: " << rgb[1] << ", b: " << rgb[2] << endl;
        float horiz_x = ((width / 2) * (row));

        for (int cube = 1; cube <= temp_level; cube++)
        {
            // set x, y and z coordinates values.
            xyz[0] = (width * cube) + horiz_x;
            cerr << "row: " << row << ", cube: " << cube << ", x: " << xyz[0] << endl;
            xyz[1] = width * row;
            xyz[2] = 0;

            for (int box_2d = 0; box_2d < 2; box_2d++)
            {
                // bottom left(origit). starting coordinates for x,y,z like origin.(0,0,0)
                cloudPtr->points[index].x = xyz[0];
                cloudPtr->points[index].y = xyz[1];
                cloudPtr->points[index].z = xyz[2];

                cloudPtr->points[index].r = rgb[0];
                cloudPtr->points[index].g = rgb[1];
                cloudPtr->points[index].b = rgb[2];
                index++;

                // next point bottom right x only changed, y and z unchanged.
                xyz[0] += width;
                cloudPtr->points[index].x = xyz[0];
                cloudPtr->points[index].y = xyz[1];
                cloudPtr->points[index].z = xyz[2];

                cloudPtr->points[index].r = rgb[0];
                cloudPtr->points[index].g = rgb[1];
                cloudPtr->points[index].b = rgb[2];
                index++;

                viewer.addLine(cloudPtr->points[index - 2], cloudPtr->points[index - 1], rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0, lineId);
                lineId = to_string(++lineInd);

                // top right y only changed, x and z unchanged.
                xyz[1] += width;
                cloudPtr->points[index].x = xyz[0];
                cloudPtr->points[index].y = xyz[1];
                cloudPtr->points[index].z = xyz[2];

                cloudPtr->points[index].r = rgb[0];
                cloudPtr->points[index].g = rgb[1];
                cloudPtr->points[index].b = rgb[2];
                index++;

                viewer.addLine(cloudPtr->points[index - 2], cloudPtr->points[index - 1], rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0, lineId);
                lineId = to_string(++lineInd);

                // top left x only changed, y and z unchanged.
                xyz[0] -= width;
                cloudPtr->points[index].x = xyz[0];
                cloudPtr->points[index].y = xyz[1];
                cloudPtr->points[index].z = xyz[2];

                cloudPtr->points[index].r = rgb[0];
                cloudPtr->points[index].g = rgb[1];
                cloudPtr->points[index].b = rgb[2];
                index++;

                viewer.addLine(cloudPtr->points[index - 2], cloudPtr->points[index - 1], rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0, lineId);
                lineId = to_string(++lineInd);

                viewer.addLine(cloudPtr->points[index - 1], cloudPtr->points[index - 4], rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0, lineId);
                lineId = to_string(++lineInd);

                xyz[1] -= width;
                xyz[2] += width;
            }

            for (int connectLine = 1; connectLine <= 4; connectLine++)
            {
                viewer.addLine(cloudPtr->points[index - connectLine], cloudPtr->points[index - connectLine - 4], rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0, lineId);
                lineId = to_string(++lineInd);
            }
        }

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

    for (const auto &p : *cloudPtr)
    {
        cout << "x: " << p.x << ", y: " << p.y << ", z: " << p.z << endl;
    }

    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb_handler(cloudPtr);
    viewer.addPointCloud<pcl::PointXYZRGB>(cloudPtr, rgb_handler, "cloud_ptr");

    // Set width for each line.
    for (int index = 0; index < lineInd; index++)
    {
        viewer.setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_LINE_WIDTH, 4.0, to_string(index));
    }

    // Set size for Point Cloud Data.
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 8, "cloud_ptr");

    pcl::io::savePCDFileASCII("RGBCubeCloud.pcd", *cloudPtr);
    cout << "Cube Cloud Data saved." << endl;

    viewer.spin();

    return 0;
}