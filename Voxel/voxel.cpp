#include "voxel.h"

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
                voxel[i][j][k].sdf = 0;
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

Index VoxelGrid::findIndex(Point point)
{
    Index index;
    index.index_x = (int)point.x;
    index.index_y = (int)point.y;
    index.index_z = (int)point.z;
    return index;
}

Point VoxelGrid::getVertex(int index_x, int index_y, int index_z, int vertex_num)
{
    Point vertex;
    if(vertex_num == 1)
    {
        vertex.x = index_x;
        vertex.y = index_y;
        vertex.z = index_z;
    }
    else if(vertex_num == 2)
    {
        vertex.x = index_x+1;
        vertex.y = index_y;
        vertex.z = index_z;
    }
    else if(vertex_num == 3)
    {
        vertex.x = index_x+1;
        vertex.y = index_y;
        vertex.z = index_z+1;
    }
    else if(vertex_num == 4)
    {
        vertex.x = index_x;
        vertex.y = index_y;
        vertex.z = index_z+1;
    }
    else if(vertex_num == 5)
    {
        vertex.x = index_x;
        vertex.y = index_y+1;
        vertex.z = index_z;
    }
    else if(vertex_num == 6)
    {
        vertex.x = index_x+1;
        vertex.y = index_y+1;
        vertex.z = index_z;
    }
    else if(vertex_num == 7)
    {
        vertex.x = index_x+1;
        vertex.y = index_y+1;
        vertex.z = index_z+1;
    }
    else if(vertex_num == 8)
    {
        vertex.x = index_x;
        vertex.y = index_y+1;
        vertex.z = index_z+1;
    }

    return vertex;
}