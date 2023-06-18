#include "../include/voxel.h"

VoxelGrid::VoxelGrid()
{
    for(int i = 0; i < VoxelSize; i++) 
    {
        voxel[i] = new Voxel*[VoxelSize];
        for(int j = 0; j < VoxelSize; j++) voxel[i][j] = new Voxel[VoxelSize];
    }

    for(int i = 0; i < VoxelSize; i++)
    {
        for(int j = 0; j < VoxelSize; j++)
        {
            for(int k = 0; k < VoxelSize; k++)
            {
                voxel[i][j][k].weight = 0;
                voxel[i][j][k].sdf = 0.0;
                voxel[i][j][k].red = 0;
                voxel[i][j][k].green = 0;
                voxel[i][j][k].blue = 0;
            }
        }
    }
}

VoxelGrid::~VoxelGrid()
{
    for(int i = 0; i < VoxelSize; i++) 
    {
        for(int j = 0; j < VoxelSize; j++) delete[] voxel[i][j];
        delete[] voxel[i];
    }
    delete[] voxel;
}