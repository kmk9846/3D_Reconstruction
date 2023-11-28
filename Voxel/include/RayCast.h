#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Core>
#include "voxel.h"
#include "../../GeneratePointCloud/include/GeneratePointCloud.h"

using namespace std;

class RayCast
{
public:
    RayCast() {}
    ~RayCast() {}
    vector<VoxelIndex> rayCasting(const Point& camera, const Point& point, int truncateSize);
    VoxelIndex offsetIndex(VoxelIndex inputIndex);
    VoxelIndex pointToVoxel(const Point& point);
    vector<PointsData> grouping(vector<PointsData> points);
    bool endRay(VoxelIndex currentIndex, VoxelIndex targetIndex, int truncatedX, int truncatedY, int truncatedZ);
};