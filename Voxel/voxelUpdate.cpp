#include "voxelUpdate.h"

float VoxelUpdate::getSDF(const Point& origin, const Point& point, Index centerIndex)
{
    Point voxelCenter;
    voxelCenter << static_cast<float>(centerIndex.index_x + VoxelUnit/2), static_cast<float>(centerIndex.index_y + VoxelUnit/2), 
                    static_cast<float>(centerIndex.index_z + VoxelUnit/2);
    const Point voxelToorigin = voxelCenter - origin;
    const Point pointToorigin = point - origin;

    const float dist = pointToorigin.norm();
    const float projectDist = voxelToorigin.dot(pointToorigin)/dist;

    const float sdf = static_cast<float>(dist - projectDist);
    return sdf;
}

void VoxelUpdate::updateSDF(const Point& origin, const Point& point, Index currentIndex)
{
    //Index currentIndex = findIndex(point);
    float distance = getSDF(origin, point, currentIndex);
    
    float prevSDF = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf;
    float prevWeight = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight;

    //update current sdf
    voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf = 
        (prevWeight * prevWeight + weight*distance)/(prevWeight+weight);
}

void VoxelUpdate::updateWeight(Index currentIndex)
{
    //Index currentIndex = findIndex(point);
    float prevWeight = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight;

    //update voxel Weight
    voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight =
        min(prevWeight + weight, weightMax);
}

void VoxelUpdate::updateColor(const Point& point)
{
    //calculate color
    Index currentIndex = findIndex(point);
}