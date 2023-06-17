#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Core>
#include "voxel.h"

using namespace std;

class RayCast
{
public:
    RayCast() {}

    //index 벡터에 ray casting 으로 찾은 voxel 의 index (x, y, z) 를 push한다. 
    vector<VoxelIndex> rayCasting(const Point& origin, const Point& point);
    bool endRay(VoxelIndex currentIndex, VoxelIndex targetIndex, int truncatedX, int truncatedY, int truncatedZ);
};