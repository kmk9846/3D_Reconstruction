#pragma once
#ifndef VOXEL_H
#define VOXEL_H

const int Voxel_Grid = 32;
const int Voxel_Leaf = 1;
const int VoxelNuum = Voxel_Grid/Voxel_Leaf;

typedef struct _Voxel{
    float weight;
    float sdf;
    float red;
    float green;
    float blue;
}Voxel;

class Voxel{
public:
    Voxel();
    
    //index로 voxel 정보 불러오기

    //voxel 정보로 index 찾기
};

#endif
