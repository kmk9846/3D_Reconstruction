#include "../include/createMesh.h"

void CreateMesh::getSDFArray(int x, int y, int z)
{ 
    // 주변 8개로 sdf 배열 얻기
    vertexSDF[0] = voxelUpdate.voxel[x][y][z].sdf;
    vertexSDF[1] = voxelUpdate.voxel[x+1][y][z].sdf;
    vertexSDF[2] = voxelUpdate.voxel[x+1][y][z+1].sdf;
    vertexSDF[3] = voxelUpdate.voxel[x][y][z+1].sdf;
    vertexSDF[4] = voxelUpdate.voxel[x][y+1][z].sdf;
    vertexSDF[5] = voxelUpdate.voxel[x+1][y+1][z].sdf;
    vertexSDF[6] = voxelUpdate.voxel[x+1][y+1][z+1].sdf;
    vertexSDF[7] = voxelUpdate.voxel[x][y+1][z+1].sdf;
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
}

Point CreateMesh::getVertex(int edge_num, const Point& voxelOrigin)
{
    Point vertex;
    float bound = 2.0;
    if(edge_num == 0)
    {
        vertex <<   (voxelOrigin(0) + voxelOrigin(0) + VoxelUnit)/bound,
                    (voxelOrigin(1) + voxelOrigin(1))/bound,
                    (voxelOrigin(2) + voxelOrigin(2))/bound;
    }
    else if(edge_num == 1)
    {
        vertex <<   (voxelOrigin(0) + VoxelUnit + voxelOrigin(0) + VoxelUnit)/bound,
                    (voxelOrigin(1) + voxelOrigin(1))/bound,
                    (voxelOrigin(2) + voxelOrigin(2) + VoxelUnit)/bound;
    }
    else if(edge_num == 2)
    {   
        vertex <<   (voxelOrigin(0) + VoxelUnit + voxelOrigin(0) + VoxelUnit)/bound,
                    (voxelOrigin(1) + voxelOrigin(1))/bound,
                    (voxelOrigin(2) + VoxelUnit + voxelOrigin(2) + VoxelUnit)/bound;
    }
    else if(edge_num == 3)
    {
        vertex <<   (voxelOrigin(0) + voxelOrigin(0))/bound,
                    (voxelOrigin(1) + voxelOrigin(1))/bound,
                    (voxelOrigin(2) + voxelOrigin(2) + VoxelUnit)/bound;
    }
    else if(edge_num == 4)
    {
        vertex <<   (voxelOrigin(0) + voxelOrigin(0) + VoxelUnit)/bound,
                    (voxelOrigin(1) + VoxelUnit + voxelOrigin(1) + VoxelUnit)/bound,
                    (voxelOrigin(2) + voxelOrigin(2))/bound;
    }
    else if(edge_num == 5)
    {
        vertex <<   (voxelOrigin(0) + VoxelUnit + voxelOrigin(0) + VoxelUnit)/bound,
                    (voxelOrigin(1) + VoxelUnit + voxelOrigin(1) + VoxelUnit)/bound,
                    (voxelOrigin(2) + voxelOrigin(2) + VoxelUnit)/bound;
    }
    else if(edge_num == 6)
    {
        vertex <<   (voxelOrigin(0) + VoxelUnit + voxelOrigin(0))/bound,
                    (voxelOrigin(1) + VoxelUnit + voxelOrigin(1) + VoxelUnit)/bound,
                    (voxelOrigin(2) + VoxelUnit + voxelOrigin(2) + VoxelUnit)/bound;
    }
    else if(edge_num == 7)
    {
        vertex <<   (voxelOrigin(0) + voxelOrigin(0))/bound,
                    (voxelOrigin(1) + VoxelUnit + voxelOrigin(1) + VoxelUnit)/bound,
                    (voxelOrigin(2) + voxelOrigin(2) + VoxelUnit)/bound;
    }
    else if(edge_num == 8)
    {
        vertex <<   (voxelOrigin(0) + voxelOrigin(0))/bound,
                    (voxelOrigin(1) + voxelOrigin(1) + VoxelUnit)/bound,
                    (voxelOrigin(2) + voxelOrigin(2))/bound;
    }
    else if(edge_num == 9)
    {
        vertex <<   (voxelOrigin(0) + VoxelUnit + voxelOrigin(0)+ VoxelUnit)/bound,
                    (voxelOrigin(1) + voxelOrigin(1) + VoxelUnit)/bound,
                    (voxelOrigin(2) + voxelOrigin(2))/bound;
    }
    else if(edge_num == 10)
    {
        vertex <<   (voxelOrigin(0) + VoxelUnit + voxelOrigin(0)+ VoxelUnit)/bound,
                    (voxelOrigin(1) + voxelOrigin(1) + VoxelUnit)/bound,
                    (voxelOrigin(2) + VoxelUnit + voxelOrigin(2) + VoxelUnit)/bound;
    }
    else if(edge_num == 11)
    {
        vertex <<   (voxelOrigin(0) + voxelOrigin(0))/bound,
                    (voxelOrigin(1) + voxelOrigin(1) + VoxelUnit)/bound,
                    (voxelOrigin(2) + VoxelUnit + voxelOrigin(2) + VoxelUnit)/bound;
    }
    return vertex;
}

void CreateMesh::generateMesh(int voxelSize, VoxelIndex maxIndex, VoxelIndex minIndex, float isolevel)
{
    //vertex point
    // voxel 그리드 순회
    for (int x = minIndex.index_x ; x < maxIndex.index_x-1; x++) 
    {
        for (int y = minIndex.index_y; y < maxIndex.index_y-1; y++) 
        {
            for (int z = minIndex.index_z; z < maxIndex.index_z-1; z++) 
            {
                getSDFArray(x, y, z);
                int cubeIndex = 0;
                cubeIndex = checkSDFSign(isolevel);
                if(checkCreate < 8 && checkCreate >= 1)
                {
                    // printf("x[%d] y[%d] z[%d]\n", x, y, z);
                    // printf("cubeindex : %d\n", cubeIndex);
                    // 삼각형 생성
                    Triangle triangle;
                    Point vertex;
                    Point voxelCenter;
                    for (int i = 0; kTriangleTable[cubeIndex][i] != -1; i += 3) 
                    {
                        // i+=1;
                        // printf("index [%d, %d, %d]\n", triangleIndices[i], triangleIndices[i+1], triangleIndices[i+2]);
                        //vertexonce edge 
                        int vertexIndex1 = kTriangleTable[cubeIndex][i];
                        int vertexIndex2 = kTriangleTable[cubeIndex][i+1];
                        int vertexIndex3 = kTriangleTable[cubeIndex][i+2];

                        triangle.e0 = vertexIndex1;
                        triangle.e1 = vertexIndex2;
                        triangle.e2 = vertexIndex3;
                        triangleVertex.push_back(triangle);
                        voxelCenter <<  static_cast<float>(x*VoxelUnit + VoxelUnit/2), 
                                        static_cast<float>(y*VoxelUnit + VoxelUnit/2), 
                                        static_cast<float>(z*VoxelUnit + VoxelUnit/2);
                        for(int i = 0; i < 3; i ++)
                        {
                            if(i == 0)
                            {
                                vertex << getVertex(vertexIndex1, voxelCenter);
                                PointVector.push_back(vertex);
                            }
                            else if(i == 1)
                            {   
                                vertex << getVertex(vertexIndex2, voxelCenter);
                                PointVector.push_back(vertex);
                            }
                            else if(1 == 2)
                            {
                                vertex << getVertex(vertexIndex3, voxelCenter);
                                PointVector.push_back(vertex);
                            }
                            
                        }
                    }
                    // printf("=====================\n");
                }else continue;
            }
        }
    }
}

void CreateMesh::writePLY() 
{
    printf("start writting\n");
    std::string filename = "mesh.ply";
    std::ofstream file(filename);
    if (!file) 
    {
        std::cerr << "Failed to create PLY file: " << filename << std::endl;
        return;
    }

    // PLY 파일 헤더 작성
    file << "ply" << std::endl;
    file << "format ascii 1.0" << std::endl;
    file << "element vertex " << PointVector.size() << std::endl;
    file << "property float x" << std::endl;
    file << "property float y" << std::endl;
    file << "property float z" << std::endl;
    // file << "element face " << triangleVertex.size() << std::endl;
    // file << "property list uint8 int32 vertex_indices" << std::endl;
    file << "end_header" << std::endl;

    for(const Point& vertex : PointVector) file << vertex(0) << " " << vertex(1) << " " << vertex(2) << std::endl;  
    // int i = 0;
    // for(const Triangle& triangle : triangleVertex)
    // {
    //     file << "3 " << i << " " << i+1 << " " << i + 2 << std::endl;
    //     i += 3;
    // }

    file.close();
    std::cout << "PLY file created: " << filename << std::endl;
}