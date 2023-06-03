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
    int checkCreate;
    void getVertexSDF(int x, int y, int z);
    int checkSDFSign(int isoLevel);
    bool checkSDFVoxel(int x, int y, int z);
    int getVertexNum(int e0, int e1, int e2);
    std::vector<Triangle> generateMesh(int voxelSize, VoxelIndex maxIndex, VoxelIndex minIndex, float isolevel);
    void writePLY(const std::vector<Triangle>& triangles);
};

