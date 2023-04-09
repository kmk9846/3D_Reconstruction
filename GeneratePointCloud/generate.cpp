#include "GeneratePointCloud.h"

int main(int argc, char* argv[])
{
    string rgbImg = argv[1];
    string depthImg = argv[2];
    float pose_x = atof(argv[3]);
    float pose_y = atof(argv[4]);
    float pose_z = atof(argv[5]);
    string outputfile = argv[6];

    Vector3d point3d;
    point3d << pose_x, pose_y, pose_z;

    GeneratePointCloud generatePointCloud;
    Matrix4d m = generatePointCloud.toHomogeneousMatrix(point3d);
    vector<string> points = generatePointCloud.generate_pointcloud(rgbImg + ".png", depthImg + ".png", m);
    generatePointCloud.write_ply(outputfile + ".ply", points);

    return 0;
}