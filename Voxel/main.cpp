#pragma once
#include "voxelUpdate.h"
#include "RayCast.h"

int main()
{
    //만약 충돌 좌표가 아래와 같을 경우의 해당 포인트 클라우드가 존재하는 voxel update 하기
    Point colPoint, Origin;
    colPoint << 2.0f, 2.0f, 2.0f;
    Origin << 0.0f, 0.0f, 0.0f;

    RayCast rayCast;
    vector<Index> findIndex;
    VoxelUpdate voxelUpdate;
    findIndex = rayCast.rayCasting(Origin, colPoint);

    for (const auto& voxelIndex : findIndex)
    {
        voxelUpdate.updateSDF(Origin, colPoint, voxelIndex);
        voxelUpdate.updateWeight(voxelIndex);
    }
    
    // //해당 인덱스
    //Index findIndex = voxelUpdate.findIndex(colPoint);
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                printf("Index : x[%d], y[%d], z[%d]\n", i, j, k);
                printf("update sdf = [%f]\n", voxelUpdate.voxel[i][j][k].sdf);
                printf("update weight = [%f]\n", voxelUpdate.voxel[i][j][k].weight);
                printf("================================\n");
    
            }
        }
    }

    return 0;
}