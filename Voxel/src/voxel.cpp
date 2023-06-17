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

VoxelIndex VoxelGrid::findIndex(const Point& point)
{
    VoxelIndex index;
    index.index_x = (int)point(0);
    index.index_y = (int)point(1);
    index.index_z = (int)point(2);
    return index;
}

Point VoxelGrid::getVertex(int index_x, int index_y, int index_z, int vertex_num)
{
    Point vertex;
    if(vertex_num == 1) vertex << float(index_x), float(index_y), float(index_z);
    else if(vertex_num == 2) vertex << float(index_x+VoxelUnit), float(index_y), float(index_z);
    else if(vertex_num == 3) vertex << float(index_x+VoxelUnit), float(index_y), float(index_z+VoxelUnit);
    else if(vertex_num == 4) vertex << float(index_x), float(index_y), float(index_z+VoxelUnit);
    else if(vertex_num == 5) vertex << float(index_x), float(index_y+VoxelUnit), float(index_z);
    else if(vertex_num == 6) vertex << float(index_x+VoxelUnit), float(index_y+VoxelUnit), float(index_z);
    else if(vertex_num == 7) vertex << float(index_x+VoxelUnit), float(index_y+VoxelUnit), float(index_z+VoxelUnit);
    else if(vertex_num == 8) vertex << float(index_x), float(index_y+VoxelUnit), float(index_z+VoxelUnit);

    return vertex;
}