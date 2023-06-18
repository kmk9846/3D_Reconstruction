#include "../include/RayCast.h"
#include <cmath>
#include <cfloat>

vector<VoxelIndex> RayCast::rayCasting(const Point& origin, const Point& point)
{
    vector<VoxelIndex> findVoxelIndex;
    VoxelIndex currentIndex;
    VoxelIndex targetIndex;

    //Ray 방향
    Point rayDirection;
    rayDirection = (point - origin);

    Point step;
    step << ((rayDirection(0) < 0) ? -1 : 1),
            ((rayDirection(1) < 0) ? -1 : 1),
            ((rayDirection(2) < 0) ? -1 : 1);

    currentIndex.index_x = std::floor(origin(0) / VoxelUnit);
    currentIndex.index_y = std::floor(origin(1) / VoxelUnit);
    currentIndex.index_z = std::floor(origin(2) / VoxelUnit);

    targetIndex.index_x = std::floor(point(0) / VoxelUnit);
    targetIndex.index_y = std::floor(point(1) / VoxelUnit);
    targetIndex.index_z = std::floor(point(2) / VoxelUnit); 

    int truncatedX = (targetIndex.index_x - currentIndex.index_x < 0) ? -1 : 1;
    int truncatedY = (targetIndex.index_y - currentIndex.index_y < 0) ? -1 : 1;
    int truncatedZ = (targetIndex.index_z - currentIndex.index_z < 0) ? -1 : 1;

    double next_voxel_boundary_x = (currentIndex.index_x + step(0)) * VoxelUnit; // correct
    double next_voxel_boundary_y = (currentIndex.index_y + step(1)) * VoxelUnit; // correct
    double next_voxel_boundary_z = (currentIndex.index_z + step(2)) * VoxelUnit; // correct

    double tMaxX = (rayDirection(0) != 0) ? (next_voxel_boundary_x - origin(0))/rayDirection(0) : DBL_MAX; 
    double tMaxY = (rayDirection(1) != 0) ? (next_voxel_boundary_y - origin(1))/rayDirection(1) : DBL_MAX; 
    double tMaxZ = (rayDirection(2) != 0) ? (next_voxel_boundary_z - origin(2))/rayDirection(2) : DBL_MAX; 

    Point delta;
    delta << ((rayDirection(0)!=0) ? VoxelUnit/rayDirection(0) * step(0) : DBL_MAX),
             ((rayDirection(1)!=0) ? VoxelUnit/rayDirection(1) * step(1) : DBL_MAX),
             ((rayDirection(2)!=0) ? VoxelUnit/rayDirection(2) * step(2) : DBL_MAX);

    VoxelIndex diff;
    diff.index_x = 0;
    diff.index_y = 0;
    diff.index_z = 0;
        
    bool neg_ray=false;
    if (currentIndex.index_x != targetIndex.index_x && rayDirection(0) < 0) { diff.index_x--; neg_ray=true; }
    if (currentIndex.index_y != targetIndex.index_y && rayDirection(1) < 0) { diff.index_y--; neg_ray=true; }
    if (currentIndex.index_z != targetIndex.index_z && rayDirection(2) < 0) { diff.index_z--; neg_ray=true; }

    VoxelIndex inputIndex;
    inputIndex.index_x = currentIndex.index_x + VoxelSize/2;
    inputIndex.index_y = currentIndex.index_y + VoxelSize/2;
    inputIndex.index_z = currentIndex.index_z + VoxelSize/2;
    if(inputIndex.index_x < 512 && inputIndex.index_y < 512 && inputIndex.index_z < 512) findVoxelIndex.push_back(inputIndex);
    if (neg_ray) {
        currentIndex.index_x += diff.index_x;
        currentIndex.index_y += diff.index_y;
        currentIndex.index_z += diff.index_z;
        
        VoxelIndex inputIndex;
        inputIndex.index_x = currentIndex.index_x + VoxelSize/2;
        inputIndex.index_y = currentIndex.index_y + VoxelSize/2;
        inputIndex.index_z = currentIndex.index_z + VoxelSize/2;
        if(inputIndex.index_x < 512 && inputIndex.index_y < 512 && inputIndex.index_z < 512) findVoxelIndex.push_back(inputIndex);
    }

    while(endRay(currentIndex, targetIndex, truncatedX, truncatedY, truncatedZ))
    {
        if (tMaxX < tMaxY) {
            if (tMaxX < tMaxZ) 
            {
                currentIndex.index_x += step(0);
                tMaxX += delta(0);
            } else 
            {
                currentIndex.index_z += step(2);
                tMaxZ += delta(2);
            }
        } 
        else {
            if (tMaxY < tMaxZ) 
            {
                currentIndex.index_y += step(1);
                tMaxY += delta(1);
            } else 
            {
                currentIndex.index_z += step(2);
                tMaxZ += delta(2);
            }
        }
        VoxelIndex inputIndex;
        inputIndex.index_x = currentIndex.index_x + VoxelSize/2;
        inputIndex.index_y = currentIndex.index_y + VoxelSize/2;
        inputIndex.index_z = currentIndex.index_z + VoxelSize/2;
        if(inputIndex.index_x < 512 && inputIndex.index_y < 512 && inputIndex.index_z < 512) findVoxelIndex.push_back(inputIndex);
    }
    return findVoxelIndex;
}


// 뒤에 어느정도 더 해주기 voxel 의 4배 정도
bool RayCast::endRay(VoxelIndex currentIndex, VoxelIndex targetIndex, 
    int truncatedX, int truncatedY, int truncatedZ)
{
    if((currentIndex.index_x != targetIndex.index_x + truncatedX * 4) && 
        (currentIndex.index_y != targetIndex.index_y + truncatedY * 4) &&
        (currentIndex.index_z != targetIndex.index_z + truncatedZ * 4)) return true;
    else return false;
}