#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <tuple>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace cv;
using namespace Eigen;

Matrix4d convertPoseMatrix(const Vector3d& R1, const Vector3d& T1, const Vector3d& R2, const Vector3d& T2) {
    Matrix3d R1_mat, R2_mat;
    R1_mat = AngleAxisd(R1.norm(), R1.normalized()).toRotationMatrix();
    R2_mat = AngleAxisd(R2.norm(), R2.normalized()).toRotationMatrix();

    Matrix3d R_rel = R2_mat * R1_mat.inverse();
    Vector3d T_rel = -R_rel * T1 + T2;

    Matrix4d P_rel = Matrix4d::Identity();
    P_rel.block<3, 3>(0, 0) = R_rel;
    P_rel.block<3, 1>(0, 3) = T_rel;
    return P_rel;
}

int main() {
    //0.4388 -0.4297 1.4819 0.8585 -0.3510 0.0863 -0.3637
    //0.4479 -0.4871 1.4361 0.8655 -0.4123 0.0487 -0.2803
    // Example pose values
    Vector3d R1(1.0, 0.0, 0.0);
    Vector3d T1(0.0, 0.0, 0.0);
    Vector3d R2(0.0, 0.0, 1.0);
    Vector3d T2(10.0, 20.0, 30.0);

    // Convert P1 to P2
    Matrix4d P_rel = convertPoseMatrix(R1, T1, R2, T2);

    // Print the resulting pose value matrix
    std::cout << "P_rel:\n" << P_rel << std::endl;

    return 0;
}