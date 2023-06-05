#include "../include/createMesh.h"

void CreateMesh::getVertexSDF(int x, int y, int z)
{ 
    for(int i = 1; i  < 8; i++)
    {
        if(x == 0 || y == 0 || z == 0) break;
        // {
        //     for(int k = 0; k < 8; k++)
        //     {
        //         vertexSDF[k] = voxelUpdate.voxel[x][y][z].sdf;
        //     }
        //     break;
        // }

        if(i == 1)
        {
            vertexSDF[0] = (voxelUpdate.voxel[x][y][z].sdf + voxelUpdate.voxel[x - 1][y][z].sdf + voxelUpdate.voxel[x - 1][y][z - 1].sdf + voxelUpdate.voxel[x][y][z - 1].sdf + voxelUpdate.voxel[x][y - 1][z].sdf+ voxelUpdate.voxel[x - 1][y - 1][z - 1].sdf 
                        + voxelUpdate.voxel[x - 1][y - 1][z].sdf + voxelUpdate.voxel[x][y - 1][z - 1].sdf) / 8.0;
        }
        else if(i == 2)
        {
            vertexSDF[1] = (voxelUpdate.voxel[x][y][z].sdf + voxelUpdate.voxel[x + 1][y][z].sdf + voxelUpdate.voxel[x][y][z - 1].sdf + voxelUpdate.voxel[x + 1][y][z - 1].sdf + voxelUpdate.voxel[x][y - 1][z].sdf + voxelUpdate.voxel[x][y - 1][z - 1].sdf 
                        + voxelUpdate.voxel[x - 1][y - 1][z].sdf + voxelUpdate.voxel[x - 1][y - 1][z - 1].sdf) / 8.0;
        }
        else if(i == 3)
        {
            vertexSDF[2] = (voxelUpdate.voxel[x][y][z].sdf + voxelUpdate.voxel[x + 1][y][z].sdf + voxelUpdate.voxel[x][y - 1][z].sdf + voxelUpdate.voxel[x + 1][y - 1][z].sdf + voxelUpdate.voxel[x][y][z + 1].sdf + voxelUpdate.voxel[x][y - 1][z + 1].sdf 
                        + voxelUpdate.voxel[x + 1][y][z + 1].sdf + voxelUpdate.voxel[x + 1][y - 1][z + 1].sdf) / 8.0;
        }
        else if(i == 4)
        {
            vertexSDF[3] = (voxelUpdate.voxel[x][y][z].sdf + voxelUpdate.voxel[x - 1][y][z].sdf + voxelUpdate.voxel[x - 1][y][z - 1].sdf + voxelUpdate.voxel[x][y][z - 1].sdf + voxelUpdate.voxel[x][y - 1][z].sdf + voxelUpdate.voxel[x - 1][y - 1][z - 1].sdf 
                        + voxelUpdate.voxel[x - 1][y - 1][z].sdf + voxelUpdate.voxel[x][y - 1][z - 1].sdf) / 8.0;
        }
        else if(i == 5)
        {
            vertexSDF[4] = (voxelUpdate.voxel[x][y][z].sdf + voxelUpdate.voxel[x - 1][y][z].sdf + voxelUpdate.voxel[x - 1][y][z - 1].sdf + voxelUpdate.voxel[x][y][z - 1].sdf + voxelUpdate.voxel[x][y + 1][z].sdf + voxelUpdate.voxel[x - 1][y + 1][z].sdf 
                        + voxelUpdate.voxel[x - 1][y + 1][z - 1].sdf + voxelUpdate.voxel[x][y + 1][z - 1].sdf) / 8.0;
        }
        else if(i == 6)
        {
            vertexSDF[5] = (voxelUpdate.voxel[x][y][z].sdf + voxelUpdate.voxel[x + 1][y][z].sdf + voxelUpdate.voxel[x][y][z - 1].sdf + voxelUpdate.voxel[x + 1][y][z - 1].sdf + voxelUpdate.voxel[x][y + 1][z].sdf + voxelUpdate.voxel[x][y + 1][z - 1].sdf 
                        + voxelUpdate.voxel[x + 1][y + 1][z].sdf + voxelUpdate.voxel[x + 1][y + 1][z - 1].sdf) / 8.0;
        }
        else if(i == 7)
        {
            vertexSDF[6] = (voxelUpdate.voxel[x][y][z].sdf + voxelUpdate.voxel[x + 1][y][z].sdf + voxelUpdate.voxel[x][y + 1][z].sdf + voxelUpdate.voxel[x + 1][y + 1][z].sdf + voxelUpdate.voxel[x][y][z + 1].sdf + voxelUpdate.voxel[x][y + 1][z + 1].sdf 
                        + voxelUpdate.voxel[x + 1][y + 1][z + 1].sdf + voxelUpdate.voxel[x + 1][y + 1][z + 1].sdf) / 8.0;
        }
        else if(i == 8)
        {
            vertexSDF[7] = (voxelUpdate.voxel[x][y][z].sdf + voxelUpdate.voxel[x - 1][y][z].sdf + voxelUpdate.voxel[x - 1][y][z - 1].sdf + voxelUpdate.voxel[x][y][z - 1].sdf + voxelUpdate.voxel[x][y + 1][z].sdf + voxelUpdate.voxel[x - 1][y + 1][z].sdf 
                        + voxelUpdate.voxel[x][y + 1][z + 1].sdf + voxelUpdate.voxel[x - 1][y + 1][z + 1].sdf) / 8.0;
        }
    }
}

//여기를 thread 로 구현하자
// 생각해보니 음수에서 양수로 바뀌는 부분만 따지면 되는거 아닌가?
int CreateMesh::checkSDFSign(int isolevel)
{
    int cubeIndex = 0;
    checkCreate = 0;
    // for(int i = 0; i < 8; i++) printf("[%d]%lf ", i, vertexSDF[i]);
    // printf("\n");
    if (vertexSDF[0] < isolevel) 
    {
        checkCreate += 1;
        cubeIndex |= 1;
    }
    if (vertexSDF[1] < isolevel) 
    {
        checkCreate += 1;
        cubeIndex |= 2;
    }
    if (vertexSDF[2] < isolevel) 
    {
        checkCreate += 1;
        cubeIndex |= 4;
    }
    if (vertexSDF[3] < isolevel) 
    {
        checkCreate += 1;
        cubeIndex |= 8;
    }
    if (vertexSDF[4] < isolevel) 
    {
        checkCreate += 1;
        cubeIndex |= 16;
    }
    if (vertexSDF[5] < isolevel) 
    {
        checkCreate += 1;
        cubeIndex |= 32;
    }
    if (vertexSDF[6] < isolevel) 
    {
        checkCreate += 1;
        cubeIndex |= 64;
    }
    if (vertexSDF[7] < isolevel) 
    {
        checkCreate += 1;
        cubeIndex |= 128;
    }
    return cubeIndex;
}

bool CreateMesh::checkSDFVoxel(int x, int y, int z)
{
    if(x == 0 || y == 0 || z == 0) return false;
    float checksdf = voxelUpdate.voxel[x][y][z].sdf;
    // checksdf *= voxelUpdate.voxel[x+1][y][z].sdf;
    // checksdf *= voxelUpdate.voxel[x][y+1][z].sdf;
    // checksdf *= voxelUpdate.voxel[x][y][z+1].sdf;
    // checksdf *= voxelUpdate.voxel[x+1][y+1][z].sdf;
    // checksdf *= voxelUpdate.voxel[x][y+1][z+1].sdf;
    // checksdf *= voxelUpdate.voxel[x+1][y][z+1].sdf;
    // checksdf *= voxelUpdate.voxel[x+1][y+1][z+1].sdf;

    // checksdf *= voxelUpdate.voxel[x-1][y][z].sdf;
    // checksdf *= voxelUpdate.voxel[x][y-1][z].sdf;
    // checksdf *= voxelUpdate.voxel[x][y][z-1].sdf;
    // checksdf *= voxelUpdate.voxel[x-1][y-1][z].sdf;
    // checksdf *= voxelUpdate.voxel[x][y-1][z-1].sdf;
    // checksdf *= voxelUpdate.voxel[x-1][y][z-1].sdf;
    // checksdf *= voxelUpdate.voxel[x-1][y-1][z-1].sdf;
    if(checksdf < 0) return true;
    else return false;
}

int CreateMesh::getVertexNum(int e0, int e1, int e2)
{
    int e_1 = e0 + 1;
    int e_2 = e1 + 1;
    int e_3 = e2 + 1;
    int checkSum = e_1 + e_2 + e_3;
    if(checkSum == 14) return 1;
    if(checkSum == 13) return 2;
    if(checkSum == 16) return 3;
    if(checkSum == 19) return 4;
    if(checkSum == 22) return 5;
    if(checkSum == 21) return 6;
    if(checkSum == 24) return 7;
    if(checkSum == 27) return 8;

    // if((e0 == 0 && e1 == 3 && e2 == 8) || (e0 == 0 && e1 == 8 && e2 == 3) || 
    //     (e0 == 3 && e1 == 8 && e2 == 0) || (e0 == 3 && e1 == 0 && e2 == 8) ||
    //     (e0 == 8 && e1 == 0 && e2 == 3) || (e0 == 8 && e1 == 3 && e2 == 0)) return 1;
    // if((e0 == 0 && e1 == 1 && e2 == 9) || (e0 == 0 && e1 == 9 && e2 == 1) || 
    //     (e0 == 1 && e1 == 0 && e2 == 9) || (e0 == 1 && e1 == 9 && e2 == 0) ||
    //     (e0 == 9 && e1 == 0 && e2 == 1) || (e0 == 9 && e1 == 1 && e2 == 0)) return 2;
    // if((e0 == 1 && e1 == 2 && e2 == 10) || (e0 == 1 && e1 == 10 && e2 == 2) || 
    //     (e0 == 2 && e1 == 1 && e2 == 10) || (e0 == 2 && e1 == 10 && e2 == 1) ||
    //     (e0 == 10 && e1 == 1 && e2 == 2) || (e0 == 10 && e1 == 2 && e2 == 1)) return 3;
    // if((e0 == 2 && e1 == 3 && e2 == 11) || (e0 == 2 && e1 == 11 && e2 == 3) || 
    //     (e0 == 3 && e1 == 2 && e2 == 11) || (e0 == 3 && e1 == 11 && e2 == 2) ||
    //     (e0 == 11 && e1 == 2 && e2 == 3) || (e0 == 11 && e1 == 3 && e2 == 2)) return 4;
    // if((e0 == 4 && e1 == 7 && e2 == 8) || (e0 == 4 && e1 == 8 && e2 == 7) || 
    //     (e0 == 7 && e1 == 8 && e2 == 4) || (e0 == 7 && e1 == 4 && e2 == 8) ||
    //     (e0 == 8 && e1 == 4 && e2 == 7) || (e0 == 8 && e1 == 7 && e2 == 4)) return 5;
    // if((e0 == 4 && e1 == 5 && e2 == 9) || (e0 == 4 && e1 == 9 && e2 == 5) || 
    //     (e0 == 5 && e1 == 4 && e2 == 9) || (e0 == 5 && e1 == 9 && e2 == 4) ||
    //     (e0 == 9 && e1 == 4 && e2 == 5) || (e0 == 9 && e1 == 5 && e2 == 4)) return 6;
    // if((e0 == 5 && e1 == 6 && e2 == 10) || (e0 == 5 && e1 == 10 && e2 == 6) || 
    //     (e0 == 6 && e1 == 5 && e2 == 10) || (e0 == 6 && e1 == 10 && e2 == 5) ||
    //     (e0 == 10 && e1 == 5 && e2 == 6) || (e0 == 10 && e1 == 6 && e2 == 5)) return 7;
    // if((e0 == 6 && e1 == 7 && e2 == 11) || (e0 == 6 && e1 == 11 && e2 == 7) || 
    //     (e0 == 7 && e1 == 6 && e2 == 11) || (e0 == 7 && e1 == 11 && e2 == 6) ||
    //     (e0 == 11 && e1 == 6 && e2 == 7) || (e0 == 11 && e1 == 7 && e2 == 6)) return 8;
}

std::vector<Triangle> CreateMesh::generateMesh(int voxelSize, VoxelIndex maxIndex, VoxelIndex minIndex, float isolevel)
{
    std::vector<Triangle> triangles;
    //vertex point
    // voxel 그리드 순회
    for (int x = minIndex.index_x ; x < maxIndex.index_x; x++) 
    {
        for (int y = minIndex.index_y; y < maxIndex.index_y; y++) 
        {
            for (int z = minIndex.index_z; z < maxIndex.index_z; z++) 
            {
                getVertexSDF(x, y, z);
                int cubeIndex = 0;
                cubeIndex = checkSDFSign(isolevel);
                if(checkCreate < 8 && checkCreate >= 3)
                {
                    printf("x[%d] y[%d] z[%d]\n", x, y, z);
                    printf("cubeindex : %d\n", cubeIndex);
                    // 삼각형 생성
                    for (int i = 0; kTriangleTable[cubeIndex][i] != -1; i += 3) 
                    {
                        // i+=1;
                        // printf("index [%d, %d, %d]\n", triangleIndices[i], triangleIndices[i+1], triangleIndices[i+2]);
                        //vertexonce edge 
                        int vertexIndex1 = kTriangleTable[cubeIndex][i];
                        int vertexIndex2 = kTriangleTable[cubeIndex][i+1];
                        int vertexIndex3 = kTriangleTable[cubeIndex][i+2];

                        Triangle triangle;
                        triangle.e0 = vertexIndex1;
                        triangle.e1 = vertexIndex2;
                        triangle.e2 = vertexIndex3;
                        triangle.index.index_x = x;
                        triangle.index.index_y = y;
                        triangle.index.index_z = z;

                        triangles.push_back(triangle);
                    }
                    printf("=====================\n");
                }else continue;
            }
        }
    }

    return triangles;
}

void CreateMesh::writePLY(const std::vector<Triangle>& triangles) 
{
    printf("start writting\n");
    std::string filename = "mesh.ply";
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Failed to create PLY file: " << filename << std::endl;
        return;
    }

    // PLY 파일 헤더 작성
    file << "ply" << std::endl;
    file << "format ascii 1.0" << std::endl;
    file << "element vertex " << triangles.size() << std::endl;
    file << "property float x" << std::endl;
    file << "property float y" << std::endl;
    file << "property float z" << std::endl;
    // file << "element face " << triangles.size() << std::endl;
    // file << "property list uchar int vertex_indices" << std::endl;
    file << "end_header" << std::endl;

    for (const Triangle& triangle : triangles) 
    {
        Point vertex;
        int vertexNum = getVertexNum(triangle.e0, triangle.e1, triangle.e2);
        vertex = voxelUpdate.getVertex(triangle.index.index_x, triangle.index.index_y, triangle.index.index_z, vertexNum);
        file << vertex(0) << " " << vertex(1) << " " << vertex(2) << std::endl;  
    }

    file.close();
    std::cout << "PLY file created: " << filename << std::endl;
}