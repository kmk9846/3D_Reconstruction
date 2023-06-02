#pragma once
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

typedef Eigen::Matrix<float, 3, 1> Point;
const int VoxelSize = 1024;
const float VoxelUnit = 0.5;

typedef struct _Voxel{
    float weight;
    float sdf;
    uchar red;
    uchar green;
    uchar blue;
}Voxel;

typedef struct _VoxelIndex{
    int index_x;
    int index_y;
    int index_z;
}VoxelIndex;


class VoxelGrid{
public:
    //init voxel data
    VoxelGrid();
    ~VoxelGrid();
    //크기떄문에 동적으로 할당하기
    Voxel ***voxel = new Voxel**[VoxelSize];

    //index로 voxel 정보 불러오기
    VoxelIndex findIndex(const Point& point);
    //voxel 정보로 index 찾기
    Point getVertex(int index_x, int index_y, int index_z, int vertex_num);
};
