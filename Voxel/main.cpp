#pragma once
#include "./include/voxelUpdate.h"
#include "./include/RayCast.h"

int main()
{
    Point colPoint, Origin;
    colPoint << 0.03f, 0.03f, 0.03f;
    Origin << -0.01f, -0.01f, -0.01f;

    RayCast rayCast;
    vector<VoxelIndex> findIndex;
    VoxelUpdate voxelUpdate;
    findIndex = rayCast.rayCasting(Origin, colPoint);
    
    for (const auto& voxelIndex : findIndex)
    {
        if(voxelIndex.index_x >=0 && voxelIndex.index_y >=0 && voxelIndex.index_z >= 0)
        {
            voxelUpdate.updateSDF(Origin, colPoint, voxelIndex);
            voxelUpdate.updateWeight(voxelIndex);
            printf("Index : x[%d], y[%d], z[%d]\n", voxelIndex.index_x , voxelIndex.index_y, voxelIndex.index_z);
            printf("update sdf = [%f]\n", voxelUpdate.voxel[voxelIndex.index_x][voxelIndex.index_y][voxelIndex.index_z].sdf);
            printf("update weight = [%f]\n", voxelUpdate.voxel[voxelIndex.index_x][voxelIndex.index_y][voxelIndex.index_z].weight);
            printf("================================\n");
        }
    }

    return 0;
}