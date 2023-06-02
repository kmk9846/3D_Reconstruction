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
    int v0, v1, v2;
    VoxelIndex index;
}Triangle;

class CreateMesh
{
public:
    CreateMesh() {}
    VoxelUpdate voxelUpdate;
    float vertexSDF[8];
    int maxIndex;
    int minIndex;
    void getVertexSDF(int x, int y, int z);
    int checkSDFSign(int isoLevel);
    bool checkSDFVoxel(int x, int y, int z);
    std::vector<Triangle> generateMesh(int voxelSize, VoxelIndex maxIndex, VoxelIndex minIndex, float isolevel);
    void writePLY(const std::vector<Triangle>& triangles);
};

