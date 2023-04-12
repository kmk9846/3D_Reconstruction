// #include <Eigen/Dense> // or <Eigen/Core> if you only need vector/matrix operations
// using namespace Eigen;

// Matrix4d ominus(Matrix4d a, Matrix4d b)
// {
//     // Compute the relative 3D transformation between a and b
//     return a.inverse() * b;
// }



#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include <Eigen/Dense> // or <Eigen/Core> if you only need vector/matrix operations
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "GeneratePointCloud.h"

using namespace std;
using namespace cv;
using namespace Eigen;

typedef map<double, Matrix4d> PoseMap;


// Helper function to convert a 1D vector to a 4x4 homogeneous matrix
Matrix4d transform44(const std::vector<double>& v)
{
    Matrix4d T = Matrix4d::Identity();
    T.block(0, 3, 3, 1) = Vector3d(v[1], v[2], v[3]);
    Quaterniond q(v[7], v[4], v[5], v[6]);
    T.block(0, 0, 3, 3) = q.toRotationMatrix();
    return T;
}

// Read a trajectory from a text file
PoseMap read_trajectory(const std::string& filename, bool matrix = true)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file '" << filename << "'" << std::endl;
        exit(1);
    }

    PoseMap traj;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::vector<double> values((std::istream_iterator<double>(iss)), std::istream_iterator<double>());

        if (values.size() != 8) {
            std::cerr << "Warning: line has " << values.size() << " values, expected 8" << std::endl;
            continue;
        }

        if (values[4] == 0 && values[5] == 0 && values[6] == 0 && values[7] == 0) {
            std::cerr << "Warning: quaternion values are all zero" << std::endl;
            continue;
        }

        if (std::any_of(values.begin(), values.end(), [](double v) { return std::isnan(v); })) {
            std::cerr << "Warning: line contains NaN values" << std::endl;
            continue;
        }

        if (matrix) {
            traj[values[0]] = transform44(values);
        }
        else {
            // Store the pose as a vector of doubles
            traj[values[0]] = MatrixXd::Map(&values[1], 7, 1).cast<double>();
        }
    }

    file.close();

    return traj;
}

int main(int argc, char* argv[])
{
    std::string ground = argv[1];
    std::string rgbImg = argv[2];
    std::string depthImg = argv[3];
    // string depthImg = argv[2];
    // float pose_x = atof(argv[3]);
    // float pose_y = atof(argv[4]);
    // float pose_z = atof(argv[5]);
    // float qx = atof(argv[6]);
    // float qy = atof(argv[7]);
    // float qz = atof(argv[8]);
    // float qw = atof(argv[9]); 
    // string outputfile = argv[10];

    // Vector3f point3d;
    // point3d << pose_x, pose_y, pose_z;

    // Quaternionf q(qx, qy, qz, qw);

    // GeneratePointCloud generatePointCloud;
    // Vector3f euler = generatePointCloud.quaternionToEuler(q);
    // Matrix4f m = generatePointCloud.createTransformMatrix(point3d, euler);
    // generatePointCloud.generate_pointcloud(rgbImg + ".png", depthImg + ".png", m);
    // generatePointCloud.write_ply(outputfile + ".ply", generatePointCloud.points);

    PoseMap pm = read_trajectory(ground, true);
    // for (const auto& elem : pm) {
    //     double key = elem.first;
    //     Eigen::Matrix4d value = elem.second;
    //     cout << fixed;
    //     cout << setprecision(6);
    //     std::cout << "key: " << key << std::endl;
    //     std::cout << "value: " << std::endl;
    //     std::cout << value << std::endl;
    // }
    GeneratePointCloud generatePointCloud;
    //Eigen::Matrix4d d_mat = Eigen::Matrix4d::Identity(); // 샘플 Matrix4d 변수
    Matrix4f f_mat = pm[1305031791.2606].cast<float>();
    cout << f_mat << endl;
    generatePointCloud.generate_pointcloud(rgbImg + ".png", depthImg + ".png", f_mat);
    generatePointCloud.write_ply("outPut_test2.ply", generatePointCloud.points);

    return 0;
}