#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "voxel.h"

using namespace std;

const float weight = 1.0;
const float weightMax = 10000.0; // 만에서 10만

class VoxelUpdate : public VoxelGrid {
public:
    VoxelUpdate() : VoxelGrid() {};

    //update sdf
    float getSDF(const Point& origin, const Point& point, Index centerIndex);
    void updateSDF(const Point& origin, const Point& point, Index currentIndex);
    void updateWeight(Index currentIndex);
    void updateColor(const Point& point);

};