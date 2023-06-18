#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "voxel.h"

using namespace std;

const float weight = 1.0;
const float weightMax = 100000.0; // 만에서 10만

class VoxelUpdate : public VoxelGrid {
public:
    VoxelUpdate() : VoxelGrid() {};

    //update sdf, weight, color
    float getSDF(const Point& origin, const Point& point, VoxelIndex centerIndex);
    void getColor(VoxelIndex centerIndex, uchar red, uchar green, uchar blue);
    void updateSDF(const Point& origin, const Point& point, VoxelIndex currentIndex, float currentSDF);
    void updateWeight(VoxelIndex currentIndex);
};