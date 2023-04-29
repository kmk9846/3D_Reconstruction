#include "voxelUpdate.h"

float VoxelUpdate::calDistance(Point point)
{
    Point voxelCenter;
    voxelCenter.x = (int)point.x;
    voxelCenter.y = (int)point.y;
    voxelCenter.z = (int)point.z;
    float dx = voxelCenter.x - point.x;
    float dy = voxelCenter.y - point.y;
    float dz = voxelCenter.z - point.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

void VoxelUpdate::updateSDF(Point point)
{
    Index currentIndex = findIndex(point);
    float distance = calDistance(point);

    float prevSDF = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf;
    float prevWeight = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight;

    //update current sdf
    voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf = 
        (prevWeight * prevWeight + weight*distance)/(prevWeight+weight);
}

void VoxelUpdate::updateWeight(Point point)
{
    Index currentIndex = findIndex(point);
    float prevWeight = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight;

    //update voxel Weight
    voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight =
        min(prevWeight + weight, weightMax);
}

void VoxelUpdate::updateColor(Point point)
{
    //calculate color
    Index currentIndex = findIndex(point);
}