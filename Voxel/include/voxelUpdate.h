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
    ~VoxelUpdate() {}
    //update sdf, weight, color
    float getSDF(const Point& camera, const Point& point, VoxelIndex targetIndex);
    float exponentialWeight(float dist);
    float linearWeight(float dist);
    float constantWeight(float dist);
    float narrowExpWeight(float dist);
    float narrowLinearWeight(float dist);
    float normalDistributionWeight(float dist);
    void getColor(VoxelIndex centerIndex, uchar red, uchar green, uchar blue);
    void updateSDF(VoxelIndex currentIndex, float currentSDF, float weightValue);
    void updateWeight(VoxelIndex currentIndex, float weightValue);
};