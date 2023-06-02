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
    if (vertexSDF[0] < isolevel) cubeIndex |= 1;
    if (vertexSDF[1] < isolevel) cubeIndex |= 2;
    if (vertexSDF[2] < isolevel) cubeIndex |= 4;
    if (vertexSDF[3] < isolevel) cubeIndex |= 8;
    if (vertexSDF[4] < isolevel) cubeIndex |= 16;
    if (vertexSDF[5] < isolevel) cubeIndex |= 32;
    if (vertexSDF[6] < isolevel) cubeIndex |= 64;
    if (vertexSDF[7] < isolevel) cubeIndex |= 128;
    return cubeIndex;
}

bool CreateMesh::checkSDFVoxel(int x, int y, int z)
{
    if(x == 0 || y == 0 || z == 0) return false;
    float checksdf = voxelUpdate.voxel[x][y][z].sdf;
    checksdf *= voxelUpdate.voxel[x+1][y][z].sdf;
    checksdf *= voxelUpdate.voxel[x][y+1][z].sdf;
    checksdf *= voxelUpdate.voxel[x][y][z+1].sdf;
    checksdf *= voxelUpdate.voxel[x+1][y+1][z].sdf;
    checksdf *= voxelUpdate.voxel[x][y+1][z+1].sdf;
    checksdf *= voxelUpdate.voxel[x+1][y][z+1].sdf;
    checksdf *= voxelUpdate.voxel[x+1][y+1][z+1].sdf;

    checksdf *= voxelUpdate.voxel[x-1][y][z].sdf;
    checksdf *= voxelUpdate.voxel[x][y-1][z].sdf;
    checksdf *= voxelUpdate.voxel[x][y][z-1].sdf;
    checksdf *= voxelUpdate.voxel[x-1][y-1][z].sdf;
    checksdf *= voxelUpdate.voxel[x][y-1][z-1].sdf;
    checksdf *= voxelUpdate.voxel[x-1][y][z-1].sdf;
    checksdf *= voxelUpdate.voxel[x-1][y-1][z-1].sdf;
    if(checksdf < 0) return true;
    else return false;
}


std::vector<Triangle> CreateMesh::generateMesh(int voxelSize, VoxelIndex maxIndex, VoxelIndex minIndex, float isolevel)
{
    std::vector<Triangle> triangles;
    // voxel 그리드 순회
    for (int x = minIndex.index_x ; x < maxIndex.index_x; x++) 
    {
        for (int y = minIndex.index_y; y < maxIndex.index_y; y++) 
        {
            for (int z = minIndex.index_z; z < maxIndex.index_z; z++) 
            {
                printf("x[%d] y[%d] z[%d]\n", x, y, z);
                // 현재 voxel의 인덱스 계산
                // int voxelIndex = x + y * gridSizeX + z * gridSizeX * gridSizeY;

                // // voxel 그리드의 꼭짓점 인덱스 계산
                // int vertexIndices[8] = {
                //     voxelIndex,
                //     voxelIndex + 1,
                //     voxelIndex + gridSizeX + 1,
                //     voxelIndex + gridSizeX,
                //     voxelIndex + gridSizeX * gridSizeY,
                //     voxelIndex + gridSizeX * gridSizeY + 1,
                //     voxelIndex + gridSizeX * gridSizeY + gridSizeX + 1,
                //     voxelIndex + gridSizeX * gridSizeY + gridSizeX
                // };
                if(checkSDFVoxel(x, y, z) == true)
                {
                    getVertexSDF(x, y, z);
                    int cubeIndex = 0;
                    cubeIndex = checkSDFSign(isolevel);
                    // 현재 votriangleIndicesxel에서 생성되는 삼각형 정보 가져오기
                    int triangleIndices[16];
                    *triangleIndices = *kTriangleTable[cubeIndex];
                    int i = 0;
                    // 삼각형 생성
                    for (int i = 0; triangleIndices[i] != -1; i += 3) 
                    {
                        // i+=1;
                        // printf("asdadsasd32 [%d]\n", i);
                        int vertexIndex1 = triangleIndices[i];
                        int vertexIndex2 = triangleIndices[i + 1];
                        int vertexIndex3 = triangleIndices[i + 2];

                        Triangle triangle;
                        triangle.v0 = vertexIndex1;
                        triangle.v1 = vertexIndex2;
                        triangle.v2 = vertexIndex3;
                        triangle.index.index_x = x;
                        triangle.index.index_y = y;
                        triangle.index.index_z = z;

                        triangles.push_back(triangle);
                    }
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

    // // 정점 데이터 작성
    // for (const Vertex& vertex : vertices) {
    //     file << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
    // }
    int i = 0;
    // 삼각형 데이터 작성
    for (const Triangle& triangle : triangles) 
    {
        i+=1;
        printf("triangle size [%d / %ld]\n", i, triangles.size());
        Point vertex;
        vertex = voxelUpdate.getVertex(triangle.index.index_x, triangle.index.index_y, triangle.index.index_z, triangle.v0);
        // file << "3 " << triangle.v0 << " " << triangle.v1 << " " << triangle.v2 << std::endl;
        file << vertex(0) << " " << vertex(1) << " " << vertex(2) << std::endl;
        vertex = voxelUpdate.getVertex(triangle.index.index_x, triangle.index.index_y, triangle.index.index_z, triangle.v1);
        // file << "3 " << triangle.v0 << " " << triangle.v1 << " " << triangle.v2 << std::endl;
        file << vertex(0) << " " << vertex(1) << " " << vertex(2) << std::endl;
        vertex = voxelUpdate.getVertex(triangle.index.index_x, triangle.index.index_y, triangle.index.index_z, triangle.v2);
        // file << "3 " << triangle.v0 << " " << triangle.v1 << " " << triangle.v2 << std::endl;
        file << vertex(0) << " " << vertex(1) << " " << vertex(2) << std::endl;
    }

    file.close();
    std::cout << "PLY file created: " << filename << std::endl;
}