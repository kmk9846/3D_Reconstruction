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


class CreateMesh
{
public:
    CreateMesh() {}
    VoxelUpdate voxelUpdate;
    float vertexSDF[8];
    int maxIndex;
    int minIndex;
    int checkCreate;
    std::vector<Point> PointVector;
    std::vector<Triangle> triangleVertex;
    void getSDFArray(int x, int y, int z);
    int checkSDFSign(int isolevel);
    int getVertexNum(int e0, int e1, int e2);
    Point getVertex(int edge_num, const Point& voxelOrigin);
    void generateMesh(int voxelSize, VoxelIndex maxIndex, VoxelIndex minIndex, float isolevel);
    void writePLY();
};

