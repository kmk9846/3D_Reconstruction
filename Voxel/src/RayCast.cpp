#include "../include/RayCast.h"

vector<VoxelIndex> RayCast::rayCasting(const Point& origin, const Point& point)
{
    vector<VoxelIndex> findVoxelIndex;

    //Ray 방향
    Point rayDirection;
    rayDirection = (point - origin).normalized();

    float rayLength = (point - origin).norm();

    Point delta;
    delta << (VoxelUnit / abs(rayDirection(0))), 
            (VoxelUnit / abs(rayDirection(1))), 
            (VoxelUnit / abs(rayDirection(2)));

    Point step;
    step << ((rayDirection(0) < 0) ? -1 : 1),
            ((rayDirection(1) < 0) ? -1 : 1),
            ((rayDirection(2) < 0) ? -1 : 1);

    Point tMax;
    tMax << (delta(0) * ((rayDirection(0) > 0) ? floor(origin(0)/VoxelUnit) : ceil(origin(0)/VoxelUnit) + 0.5f)),
            (delta(1) * ((rayDirection(1) > 0) ? floor(origin(1)/VoxelUnit) : ceil(origin(1)/VoxelUnit) + 0.5f)),
            (delta(2) * ((rayDirection(2) > 0) ? floor(origin(2)/VoxelUnit) : ceil(origin(2)/VoxelUnit) + 0.5f));

    int currentX = static_cast<int>(origin(0) / VoxelUnit);
    int currentY = static_cast<int>(origin(1) / VoxelUnit);
    int currentZ = static_cast<int>(origin(2) / VoxelUnit);   

    while (endRay(currentX, currentY, currentZ, origin, rayDirection, point, rayLength)) 
    {
        VoxelIndex findIndex;
        findIndex.index_x = currentX;
        findIndex.index_y = currentY;
        findIndex.index_z = currentZ;
                        
        findVoxelIndex.push_back(findIndex);

        if (tMax(0) < tMax(1)) 
        {
            if (tMax(0) < tMax(2)) 
            {
                currentX += step(0);
                tMax(0) += delta(0);
            } 
            else 
            {
                currentZ += step(2);
                tMax(2) += delta(2);
            }
        } 
        else 
        {
            if (tMax(1) < tMax(2)) 
            {
                currentY += step(1);
                tMax(1) += delta(1);
            } 
            else 
            {
                currentZ += step(2);
                tMax(2) += delta(2);
            }
        }
    }

    return findVoxelIndex;
}

bool RayCast::endRay(float currentX, float currentY, float currentZ, const Point& origin, const Point& rayDirection, 
                    const Point& point, float rayLength)
{
    // Ray의 종료 조건 확인
    float distX = (currentX + 0.5f) * VoxelUnit - origin(0);
    float distY = (currentY + 0.5f) * VoxelUnit - origin(1);
    float distZ = (currentZ + 0.5f) * VoxelUnit - origin(2);
    if (distX * rayDirection(0) >= point(0) || distY * rayDirection(1) >= point(1) 
            || distZ * rayDirection(2) >= point(2)) return false;
    else return true;
}