#include "voxelUpdate.h"

void VoxelUpdate::updateSDF(int index_x, int index_y, int index_z)
{
    //calculate voxel sdf
    voxel.voxel[index_x][index_y][index_z].sdf = 0;
}

void VoxelUpdate::updateWeight(int index_x, int index_y, int index_z)
{
    //calculate voxel Weight
    voxel.voxel[index_x][index_y][index_z].weight = 0;
}

void VoxelUpdate::updateColor(int index_x, int index_y, int index_z)
{
    //calculate color
    voxel.voxel[index_x][index_y][index_z].red = 0;
    voxel.voxel[index_x][index_y][index_z].blue = 0;
    voxel.voxel[index_x][index_y][index_z].green = 0;
}