#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "voxel.h"

using namespace std;

const float weight = 1.0;
const float weightMax = 10.0;

class VoxelUpdate : public VoxelGrid {
public:
    VoxelUpdate() : VoxelGrid() {};

    //update sdf
    float calDistance(Point point);
    void updateSDF(Point point);
    void updateWeight(Point point);
    void updateColor(Point point);

};