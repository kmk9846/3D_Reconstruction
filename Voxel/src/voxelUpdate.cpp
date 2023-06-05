#include "../include/voxelUpdate.h"

float VoxelUpdate::getSDF(const Point& origin, const Point& point, VoxelIndex centerIndex)
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

void VoxelUpdate::updateSDF(const Point& origin, const Point& point, VoxelIndex currentIndex)
{
    //Index currentIndex = findIndex(point);
    float distance = getSDF(origin, point, currentIndex);
    if(currentIndex.index_x <= 0 || currentIndex.index_y <= 0 || currentIndex.index_z <= 0) return;
    else
    {
        float prevSDF = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf;
        float prevWeight = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight;
        //update current sdf
        voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf = 
        (prevWeight * prevWeight + weight*distance)/(prevWeight+weight);
    }
}

void VoxelUpdate::updateWeight(VoxelIndex currentIndex)
{
    //Index currentIndex = findIndex(point);
    if(currentIndex.index_x <= 0 || currentIndex.index_y <= 0 || currentIndex.index_z <= 0) return;
    else
    {
        float prevWeight = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight;

        //update voxel Weight
        voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight =
            min(prevWeight + weight, weightMax);
    }
}

void VoxelUpdate::updateColor(const Point& point)
{
    //calculate color
    VoxelIndex currentIndex = findIndex(point);
}