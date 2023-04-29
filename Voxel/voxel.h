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
}Voxel_info;

typedef struct _Point{
    float x;
    float y;
    float z;
}Point;

class Voxel{
public:
    //init voxel data
    Voxel();
    Voxel_info voxel[VoxelSize][VoxelSize][VoxelSize];
    //index로 voxel 정보 불러오기
    Voxel_info voxelInfo(int index_x, int index_y, int index_z);
    //voxel 정보로 index 찾기
    Point getVertex(int index_x, int index_y, int index_z, int vertex_num);
};
