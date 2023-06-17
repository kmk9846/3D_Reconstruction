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
    int maxIndex;
    int minIndex;
    int checkCreate;
    std::vector<MeshInfo> PointVector;
    std::vector<Triangle> triangleVertex;
    std::vector<float> color;
    void getSDFArray(int x, int y, int z);
    int checkSDFSign(int isolevel);
    Point getVertex(int edge_num, const Point& voxelOrigin);
    void generateMesh(int voxelSize, VoxelIndex maxIndex, VoxelIndex minIndex, float isolevel);
    void writePLY();
};

