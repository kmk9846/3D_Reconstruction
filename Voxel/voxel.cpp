#include "voxel.h"

Voxel::Voxel()
{
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

Voxel_info Voxel::voxelInfo(int index_x, int index_y, int index_z)
{
    Voxel_info info;
    info = voxel[index_x][index_y][index_z];
    return info;
}

Point Voxel::getVertex(int index_x, int index_y, int index_z, int vertex_num)
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