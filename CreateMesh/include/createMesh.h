#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <Eigen/Core>
#include "../../Voxel/include/voxelUpdate.h"
#include "../../Voxel/include/voxel.h"
#include "meshTable.h"

typedef struct _Triangle {
    int e0, e1, e2;
}Triangle;

typedef struct _MeshInfo {
    float x, y, z;
    uchar red, green, blue;
}MeshInfo;


class CreateMesh
{
public:
    CreateMesh() {}
    VoxelUpdate voxelUpdate;
    float vertexSDF[8];
    std::vector<MeshInfo> PointVector;
    std::vector<Triangle> triangleVertex;
    std::vector<float> color;
    //sdf 배열을 구하고, 부호 확인
    void getSDFArray(int x, int y, int z);
    int checkSDFSign(int isolevel);
    //해당 edge 번호의 좌표를 계산
    Point getVertex(int edge_num, const Point& voxelOrigin);
    //Mesh에 필요한 vertex 와 삼각형 계산 후, ply 파일 생성
    void generateMesh(int voxelSize, VoxelIndex maxIndex, VoxelIndex minIndex, float isolevel);
    void writePLY();
};

