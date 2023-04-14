#include "voxel.h"

Voxel Voxel::voxelInfo(int index_x, int index_y, int index_z)
{
    Voxel info;
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
        
    }
    else if(vertex_num == 3)
    {
        
    }
    else if(vertex_num == 4)
    {
        
    }
    else if(vertex_num == 5)
    {
        
    }
    else if(vertex_num == 6)
    {
        
    }
    else if(vertex_num == 7)
    {
        
    }
    else if(vertex_num == 8)
    {
        
    }

    return vertex;
}