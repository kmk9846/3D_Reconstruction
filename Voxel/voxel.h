#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

const int VoxelSize = 512;

typedef struct _Voxel{
    float weight;
    float sdf;
    uchar red;
    uchar green;
    uchar blue;
}Voxel;

typedef struct _Point{
    float x;
    float y;
    float z;
}Point;

class Voxel{
public:
    Voxel() {};
    Voxel voxel[VoxelSize][VoxelSize][VoxelSize];
    //index로 voxel 정보 불러오기
    Voxel voxelInfo(int index_x, int index_y, int index_z);
    Point getVertex(int index_x, int index_y, int index_z, int vertex_num);
    //voxel 정보로 index 찾기

};
