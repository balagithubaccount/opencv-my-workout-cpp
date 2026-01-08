#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
using namespace std;

int main()
{
    float width = 1;
    // cout << "Enter the Cube width: ";
    // cin >> width;

    int level;
    cout << "Enter the Level: ";
    cin >> level;

    float xyz[3];

    if (level <= 0)
    {
        cout << "Invalid Level value: " << level << endl;
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

    pcl::PointCloud<pcl::PointXYZ> cloud;
    cloud.width = 8 * cubeCount; // 8 for no.of.corner points per cube. 8 multiplied by no.of cubes.
    cloud.height = 1;
    cloud.resize(cloud.width * cloud.height);

    cout << "cloud size: " << cloud.size() << endl;

    int index = 0;
    for (int row = 0; row < level; row++, temp_level--)
    {
        for (int cube = 1; cube <= temp_level; cube++)
        {
            xyz[0] = (width * cube) + ((width / 2) * (row));
            cerr << "row: " << row << ", cube: " << cube << ", x: " << xyz[0] << endl;
            xyz[1] = width * row;
            xyz[2] = 0;

            for (int box_2d = 0; box_2d < 2; box_2d++)
            {
                // bottom left(origit). starting coordinates for x,y,z like origin.(0,0,0)
                cloud.points[index].x = xyz[0];
                cloud.points[index].y = xyz[1];
                cloud.points[index].z = xyz[2];
                index++;

                // next point bottom right x only changed, y and z unchanged.
                xyz[0] += width;
                cloud.points[index].x = xyz[0];
                cloud.points[index].y = xyz[1];
                cloud.points[index].z = xyz[2];
                index++;

                // top right y only changed, x and z unchanged.
                xyz[1] += width;
                cloud.points[index].x = xyz[0];
                cloud.points[index].y = xyz[1];
                cloud.points[index].z = xyz[2];
                index++;

                // top left x only changed, y and z unchanged.
                xyz[0] -= width;
                cloud.points[index].x = xyz[0];
                cloud.points[index].y = xyz[1];
                cloud.points[index].z = xyz[2];
                index++;

                xyz[1] -= width;
                xyz[2] += width;
            }
        }
    }

    for (const auto &p : cloud)
    {
        cout << "x: " << p.x << ", y: " << p.y << ", z: " << p.z << endl;
    }

    pcl::io::savePCDFileASCII("CubeCloud.pcd", cloud);
    cout << "Cube Cloud Data saved." << endl;

    return 0;
}