#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
using namespace std;

int main()
{
    float width = 1; // Square width.

    int level; // Total number of rows in the Pyramid.
    cout << "Enter the Level: ";
    cin >> level;

    float xyz[3];               // store the x,y,z co-ordinate values.
    int rgb[3] = {255, 0, 255}; // store the RGB color with red, green and blue values the range (0 - 255).

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
    // pcl::visualization::PCLVisualizer viewer("Cube Viewer");
    // int lineInd = 0;
    // string lineId = to_string(lineInd);

    // int index = 0;
    // for (int row = 0; row < level; row++, temp_level--)
    // {
    //     for (int cube = 1; cube <= temp_level; cube++)
    //     {
    //         // set x, y and z coordinates values.
    //         xyz[0] = (width * cube) + ((width / 2) * (row));
    //         cerr << "row: " << row << ", cube: " << cube << ", x: " << xyz[0] << endl;
    //         xyz[1] = width * row;
    //         xyz[2] = 0;

    //         rgb[0] -= 1;
    //         rgb[1] += 1;
    //         rgb[2] -= 1;

    //         for (int box_2d = 0; box_2d < 2; box_2d++)
    //         {
    //             // bottom left(origit). starting coordinates for x,y,z like origin.(0,0,0)
    //             cloud.points[index].x = xyz[0];
    //             cloud.points[index].y = xyz[1];
    //             cloud.points[index].z = xyz[2];

    //             cloud.points[index].r = rgb[0];
    //             cloud.points[index].g = rgb[1];
    //             cloud.points[index].b = rgb[1];
    //             index++;

    //             // next point bottom right x only changed, y and z unchanged.
    //             xyz[0] += width;
    //             cloud.points[index].x = xyz[0];
    //             cloud.points[index].y = xyz[1];
    //             cloud.points[index].z = xyz[2];

    //             cloud.points[index].r = rgb[0];
    //             cloud.points[index].g = rgb[1];
    //             cloud.points[index].b = rgb[1];
    //             index++;

    //             viewer.addLine(cloud.points[index - 2], cloud.points[index - 1], rgb[0], rgb[1], rgb[2], lineId);
    //             lineId = to_string(++lineInd);

    //             // top right y only changed, x and z unchanged.
    //             xyz[1] += width;
    //             cloud.points[index].x = xyz[0];
    //             cloud.points[index].y = xyz[1];
    //             cloud.points[index].z = xyz[2];

    //             cloud.points[index].r = rgb[0];
    //             cloud.points[index].g = rgb[1];
    //             cloud.points[index].b = rgb[1];
    //             index++;

    //             viewer.addLine(cloud.points[index - 2], cloud.points[index - 1], rgb[0], rgb[1], rgb[2], lineId);
    //             lineId = to_string(++lineInd);

    //             // top left x only changed, y and z unchanged.
    //             xyz[0] -= width;
    //             cloud.points[index].x = xyz[0];
    //             cloud.points[index].y = xyz[1];
    //             cloud.points[index].z = xyz[2];

    //             cloud.points[index].r = rgb[0];
    //             cloud.points[index].g = rgb[1];
    //             cloud.points[index].b = rgb[1];
    //             index++;

    //             viewer.addLine(cloud.points[index - 2], cloud.points[index - 1], rgb[0], rgb[1], rgb[2], lineId);
    //             lineId = to_string(++lineInd);

    //             viewer.addLine(cloud.points[index - 1], cloud.points[index - 4], rgb[0], rgb[1], rgb[2], lineId);
    //             lineId = to_string(++lineInd);

    //             xyz[1] -= width;
    //             xyz[2] += width;
    //         }

    //         for (int connectLine = 1; connectLine <= 4; connectLine++)
    //         {
    //             viewer.addLine(cloud.points[index - connectLine], cloud.points[index - connectLine - 4], rgb[0], rgb[1], rgb[2], lineId);
    //             lineId = to_string(++lineInd);
    //         }
    //     }
    // }

    // for (const auto &p : cloud)
    // {
    //     cout << "x: " << p.x << ", y: " << p.y << ", z: " << p.z << endl;
    // }

    // pcl::io::savePCDFileASCII("RGBCubeCloud.pcd", cloud);
    // cout << "Cube Cloud Data saved." << endl;

    // viewer.spin();

    return 0;
}