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
    //index 벡터에 ray casting 으로 찾은 voxel 의 index (x, y, z) 를 push한다. 
    vector<VoxelIndex> rayCasting(const Point& camera, const Point& point, int truncateSize);
    VoxelIndex offsetIndex(VoxelIndex inputIndex);
    VoxelIndex pointToVoxel(const Point& point);
    vector<PointsData> grouping(vector<PointsData> points);
    // point cloud 뒤의 4개의 voxel 까지 update
    bool endRay(VoxelIndex currentIndex, VoxelIndex targetIndex, int truncatedX, int truncatedY, int truncatedZ);
};