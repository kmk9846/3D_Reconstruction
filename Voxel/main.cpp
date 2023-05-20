#pragma once
#include "./include/voxelUpdate.h"
#include "./include/RayCast.h"

int main()
{
    //만약 충돌 좌표가 아래와 같을 경우의 해당 포인트 클라우드가 존재하는 voxel update 하기
    Point colPoint, Origin;
    colPoint << 1.0f, 0.5f, 1.0f;
    Origin << 0.0f, 0.0f, 0.0f;

    RayCast rayCast;
    vector<VoxelIndex> findIndex;
    VoxelUpdate voxelUpdate;
    findIndex = rayCast.rayCasting(Origin, colPoint);

    for (const auto& voxelIndex : findIndex)
    {
        // cout << voxelIndex.index_x << " , " << voxelIndex.index_y << " , " << voxelIndex.index_z << endl;
        voxelUpdate.updateSDF(Origin, colPoint, voxelIndex);
        voxelUpdate.updateWeight(voxelIndex);
        printf("Index : x[%d], y[%d], z[%d]\n", voxelIndex.index_x , voxelIndex.index_y, voxelIndex.index_z);
        printf("update sdf = [%f]\n", voxelUpdate.voxel[voxelIndex.index_x][voxelIndex.index_y][voxelIndex.index_z].sdf);
        printf("update weight = [%f]\n", voxelUpdate.voxel[voxelIndex.index_x][voxelIndex.index_y][voxelIndex.index_z].weight);
        printf("================================\n");
    }

    return 0;
}