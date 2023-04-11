#include "GeneratePointCloud.h"

int main(int argc, char* argv[])
{
    string rgbImg = argv[1];
    string depthImg = argv[2];
    float pose_x = atof(argv[3]);
    float pose_y = atof(argv[4]);
    float pose_z = atof(argv[5]);
    float qx = atof(argv[6]);
    float qy = atof(argv[7]);
    float qz = atof(argv[8]);
    float qw = atof(argv[9]); 
    string outputfile = argv[10];

    Vector3f point3d;
    point3d << pose_x, pose_y, pose_z;

    Quaternionf q(qx, qy, qz, qw);

    GeneratePointCloud generatePointCloud;
    Vector3f euler = generatePointCloud.quaternionToEuler(q);
    Matrix4f m = generatePointCloud.createTransformMatrix(point3d, euler);
    vector<string> points = generatePointCloud.generate_pointcloud(rgbImg + ".png", depthImg + ".png", m);
    generatePointCloud.write_ply(outputfile + ".ply", points);

    return 0;
}