#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
using namespace std;

static float cubeWidth;

void addPointsToEdge(const pcl::PointXYZRGB &startPoint, const pcl::PointXYZRGB &endPoint, const char &fieldName,
                     pcl::PointCloud<pcl::PointXYZRGB> &cloud, int index)
{
}

int main()
{
    float cubeWidth = 1; // Square width.

    int level; // Total number of rows in the Pyramid.
    cout << "Enter the Level: ";
    cin >> level;

    cout << "Enter the width(in mm): ";
    cin >> cubeWidth; // in millimeter

    float xyz[3];               // store the x,y,z co-ordinate values.
    int rgb[3] = {0, 127, 255}; // store the RGB color with red, green and blue values the range (0 - 255).

    if (level <= 0 || cubeWidth <= 0)
    {
        cout << "Invalid Level value or width value: " << level << ":" << cubeWidth << endl;
        return -1;
    }

    int temp_level = level;

    // set cube width value from millimeter to meter.
    cubeWidth /= 1000;

    // Find the width based on the input level
    int cubeCount = 0;
    for (int lev = level; lev > 0; lev--)
    {
        cubeCount += lev;
    }
    cout << "cube count: " << cubeCount << endl;

    pcl::PointCloud<pcl::PointXYZRGB> cloud;
    cloud.width = 8 * cubeCount * 18 * 12; // 8 for no.of.corner points per cube. so 8 multiplied by no.of cubes. 18 for line making points for each cube with 12 lines.
    cloud.height = 1;
    cloud.resize(cloud.width * cloud.height);

    cout << "cloud size: " << cloud.size() << endl;

    // Create visualizer
    // pcl::visualization::PCLVisualizer viewer("Cube Viewer");
    // int lineInd = 0;
    // string lineId = to_string(lineInd);

    int col_r, col_g, col_b;
    col_r = 35;
    col_g = 50;
    col_b = -10;

    int index = 0;
    for (int row = 0; row < level; row++, temp_level--)
    {
        cout << "Color r: " << rgb[0] << ", g: " << rgb[1] << ", b: " << rgb[2] << endl;
        float horiz_x = ((cubeWidth / 2) * (row));

        for (int cube = 1; cube <= temp_level; cube++)
        {
            // set x, y and z coordinates values.
            xyz[0] = (cubeWidth * cube) + horiz_x;
            xyz[1] = cubeWidth * row;
            xyz[2] = 0;

            cout << "row: " << row << ", cube: " << cube << ", x: " << xyz[0] << endl;

            for (int box_2d = 0; box_2d < 2; box_2d++)
            {
                // bottom left(origit). starting coordinates for x,y,z like origin.(0,0,0)
                cloud.points[index].x = xyz[0];
                cloud.points[index].y = xyz[1];
                cloud.points[index].z = xyz[2];

                cloud.points[index].r = rgb[0];
                cloud.points[index].g = rgb[1];
                cloud.points[index].b = rgb[2];
                index++;

                // next point bottom right x only changed, y and z unchanged.
                xyz[0] += cubeWidth;
                cloud.points[index].x = xyz[0];
                cloud.points[index].y = xyz[1];
                cloud.points[index].z = xyz[2];

                cloud.points[index].r = rgb[0];
                cloud.points[index].g = rgb[1];
                cloud.points[index].b = rgb[2];
                index++;

                // viewer.addLine(cloud.points[index - 2], cloud.points[index - 1], rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0, lineId);
                // lineId = to_string(++lineInd);

                addPointsToEdge(cloud.points[index - 2], cloud.points[index - 1], 'x', cloud, index);
                // index += 18;

                // top right y only changed, x and z unchanged.
                xyz[1] += cubeWidth;
                cloud.points[index].x = xyz[0];
                cloud.points[index].y = xyz[1];
                cloud.points[index].z = xyz[2];

                cloud.points[index].r = rgb[0];
                cloud.points[index].g = rgb[1];
                cloud.points[index].b = rgb[2];
                index++;

                // viewer.addLine(cloud.points[index - 2], cloud.points[index - 1], rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0, lineId);
                // lineId = to_string(++lineInd);

                addPointsToEdge(cloud.points[index - 2], cloud.points[index - 1], 'y', cloud, index);
                // index += 18;

                // top left x only changed, y and z unchanged.
                xyz[0] -= cubeWidth;
                cloud.points[index].x = xyz[0];
                cloud.points[index].y = xyz[1];
                cloud.points[index].z = xyz[2];

                cloud.points[index].r = rgb[0];
                cloud.points[index].g = rgb[1];
                cloud.points[index].b = rgb[2];
                index++;

                // viewer.addLine(cloud.points[index - 2], cloud.points[index - 1], rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0, lineId);
                // lineId = to_string(++lineInd);

                addPointsToEdge(cloud.points[index - 2], cloud.points[index - 1], 'x', cloud, index);
                // index += 18;

                // viewer.addLine(cloud.points[index - 1], cloud.points[index - 4], rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0, lineId);
                // lineId = to_string(++lineInd);

                addPointsToEdge(cloud.points[index - 1], cloud.points[index - 4], 'y', cloud, index);
                // index += 18;

                xyz[1] -= cubeWidth;
                xyz[2] += cubeWidth;
            }

            for (int connectLine = 1; connectLine <= 4; connectLine++)
            {
                // viewer.addLine(cloud.points[index - connectLine], cloud.points[index - connectLine - 4], rgb[0] / 255.0, rgb[1] / 255.0, rgb[2] / 255.0, lineId);
                // lineId = to_string(++lineInd);

                addPointsToEdge(cloud.points[index - 1], cloud.points[index - 4], 'y', cloud, index);
                // index += 18;
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

    // Add width for each line.
    // for (int index = 0; index < lineInd; index++)
    // {
    //     viewer.setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_LINE_WIDTH, 5.0, to_string(index));
    // }

    for (const auto &p : cloud)
    {
        cout << "x: " << p.x << ", y: " << p.y << ", z: " << p.z << ", RGB: " << (int)p.r << " " << (int)p.g << " " << (int)p.b << endl;
    }

    pcl::io::savePCDFileASCII("RGBCubeCloud.pcd", cloud);
    cout << "Cube Cloud Data saved." << endl;

    // viewer.spin();

    return 0;
}