#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

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

typedef struct _Index{
    int index_x;
    int index_y;
    int index_z;
}Index;

class VoxelGrid{
public:
    //init voxel data
    VoxelGrid();
    ~VoxelGrid();
    //크기떄문에 동적으로 할당하기
    Voxel ***voxel = new Voxel**[VoxelSize];
    // Voxel voxel[VoxelSize][VoxelSize][VoxelSize];
    //index로 voxel 정보 불러오기
    Index findIndex(Point point);
    //voxel 정보로 index 찾기
    Point getVertex(int index_x, int index_y, int index_z, int vertex_num);
};
