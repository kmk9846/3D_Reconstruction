#include "voxelUpdate.h"

int main()
{
    //만약 충돌 좌표가 아래와 같을 경우의 해당 포인트 클라우드가 존재하는 voxel update 하기
    Point colPoint;
    colPoint.x = 510.6;
    colPoint.y = 490.2;
    colPoint.z = 500.7;

    // VoxelGrid voxelgrid;
    VoxelUpdate voxelUpdate;
    voxelUpdate.updateSDF(colPoint);
    voxelUpdate.updateWeight(colPoint);
    
    // //해당 인덱스
    Index findIndex = voxelUpdate.findIndex(colPoint);

    printf("Index : x[%d], y[%d], z[%d]\n", findIndex.index_x, findIndex.index_y, findIndex.index_z);
    printf("update sdf = [%f]\n", voxelUpdate.voxel[findIndex.index_x][findIndex.index_y][findIndex.index_z].sdf);
    printf("update weight = [%f]\n", voxelUpdate.voxel[findIndex.index_x][findIndex.index_y][findIndex.index_z].weight);
    return 0;
}