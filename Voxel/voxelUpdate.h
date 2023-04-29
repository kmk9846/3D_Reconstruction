#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "voxel.h"

class VoxelUpdate{
public:
    VoxelUpdate() {};
    Voxel voxel;

    //update sdf
    void updateSDF(int index_x, int index_y, int index_z);
    void updateWeight(int index_x, int index_y, int index_z);
    void updateColor(int index_x, int index_y, int index_z);

};