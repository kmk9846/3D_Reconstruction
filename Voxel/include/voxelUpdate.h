#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "voxel.h"

using namespace std;

const float weight = 1.0;
const float weightMax = 100000.0;

class VoxelUpdate : public VoxelGrid {
public:
    VoxelUpdate() : VoxelGrid() {};
    ~VoxelUpdate() {}
    //update sdf, weight, color
    float getSDF(const Point& camera, const Point& point, VoxelIndex targetIndex);
    float exponentialWeight(float dist, int truncateSize);
    float linearWeight(float dist, int truncateSize);
    float constantWeight(float dist, int truncateSize);
    float narrowExpWeight(float dist, int truncateSize);
    float narrowLinearWeight(float dist, int truncateSize);
    float normalDistributionWeight(float dist, int truncateSize);
    void getColor(VoxelIndex centerIndex, uchar red, uchar green, uchar blue);
    void updateSDF(VoxelIndex currentIndex, float currentSDF, float weightValue);
    void updateColor(VoxelIndex currentIndex, uchar red, uchar green, uchar blue, float weightValue);
    void updateWeight(VoxelIndex currentIndex, float weightValue);
};