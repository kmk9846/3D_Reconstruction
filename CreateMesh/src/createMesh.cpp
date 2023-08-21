#include "../include/createMesh.h"
#include <cmath>

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

int CreateMesh::checkSDFSign()
{
    int cubeIndex = 0;
    for(int i = 0; i < 8; i++)
    {
        if(vertexSDF[i] == 0)
        {
            cubeIndex = 0;
            return cubeIndex;
        }
        if(vertexSDF[i] < 0)
        {
            int num = std::pow(2, i);
            cubeIndex |= num;
        }
    }
    return cubeIndex;
}

Point CreateMesh::interpolation(int vertexnum1, int vertexnum2, const Point& voxelOrigin)
{
    Point interpolation;
    
    if(vertexSDF[vertexnum1-1] == 0) interpolation = getVertex(vertexnum1, voxelOrigin);
    else if(vertexSDF[vertexnum2-1] == 0) interpolation = getVertex(vertexnum2, voxelOrigin);
    else
    {
        Point point1 = getVertex(vertexnum1, voxelOrigin);
        Point point2 = getVertex(vertexnum2, voxelOrigin);

        interpolation = ((getVertex(vertexnum1, voxelOrigin) * abs(vertexSDF[vertexnum2-1])) +
                        (getVertex(vertexnum2, voxelOrigin) * abs(vertexSDF[vertexnum1-1]))) /
                        ((abs(vertexSDF[vertexnum1-1])) + (abs(vertexSDF[vertexnum2-1])));
        // interpolation = ((getVertex(vertexnum1, voxelOrigin)) +
        //                 (getVertex(vertexnum2, voxelOrigin) )) /
        //                 2;
        
    }
    return interpolation;
}

Point CreateMesh::getVertex(int vertex_num, const Point& voxelOrigin)
{
    Point vertex = voxelOrigin;
    if(vertex_num == 1) return vertex;
    else if(vertex_num == 2)
    {
        vertex(0) += VoxelUnit;
    }   
    else if(vertex_num == 3)
    {   
        vertex(0) += VoxelUnit;
        vertex(2) += VoxelUnit;
    }
    else if(vertex_num == 4) vertex(2) += VoxelUnit;
    else if(vertex_num == 5) vertex(1) += VoxelUnit;
    else if(vertex_num == 6)
    {  
        vertex(0) += VoxelUnit;
        vertex(1) += VoxelUnit;
    }
    else if(vertex_num == 7)
    {
        vertex(0) += VoxelUnit;
        vertex(1) += VoxelUnit;
        vertex(2) += VoxelUnit;
    }
    else if(vertex_num == 8)
    {
        vertex(1) += VoxelUnit;
        vertex(2) += VoxelUnit;
    }
    return vertex;
}

Point CreateMesh::getSDFVertex(int edge_num, const Point& voxelCenter)
{
    Point SDFvertex;
    if(edge_num == 0) SDFvertex << interpolation(1, 2, voxelCenter);
    else if(edge_num == 1) SDFvertex << interpolation(2, 3, voxelCenter);
    else if(edge_num == 2) SDFvertex << interpolation(3, 4, voxelCenter);
    else if(edge_num == 3) SDFvertex << interpolation(1, 4, voxelCenter);
    else if(edge_num == 4) SDFvertex << interpolation(5, 6, voxelCenter);
    else if(edge_num == 5) SDFvertex << interpolation(6, 7, voxelCenter);
    else if(edge_num == 6) SDFvertex << interpolation(7, 8, voxelCenter);
    else if(edge_num == 7) SDFvertex << interpolation(5, 8, voxelCenter);
    else if(edge_num == 8) SDFvertex << interpolation(1, 5, voxelCenter);
    else if(edge_num == 9) SDFvertex << interpolation(2, 6, voxelCenter);
    else if(edge_num == 10) SDFvertex << interpolation(3, 7, voxelCenter);
    else if(edge_num == 11) SDFvertex << interpolation(4, 8, voxelCenter);
    return SDFvertex;
}

bool CreateMesh::checkDuplicate(const MeshInfo& a, const MeshInfo& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

// 벡터에 요소를 추가할 때 중복 체크
bool CreateMesh::isDuplicateExists(const std::vector<MeshInfo>& vec, const MeshInfo& newItem) {
    for (const auto& item : vec) {
        if (checkDuplicate(item, newItem)) {
            return true;
        }
    }
    return false;
}

void CreateMesh::generateMesh(int voxelSizeX, int voxelSizeY, int voxelSizeZ, VoxelIndex maxIndex, VoxelIndex minIndex, float isolevel)
{
    //vertex point
    // voxel 그리드 순회
    for (int x = minIndex.index_x; x < maxIndex.index_x; x++) 
    {
        for (int y = minIndex.index_y; y < maxIndex.index_y; y++) 
        {
            for (int z = minIndex.index_z; z < maxIndex.index_z; z++) 
            {
                VoxelIndex voxelIndex;
                voxelIndex.index_x = x;
                voxelIndex.index_y = y;
                voxelIndex.index_z = z;
                getSDFArray(x, y, z);
                int cubeIndex = 0;
                cubeIndex = checkSDFSign();
                if(cubeIndex < 255 && cubeIndex > 0)
                {
                    // 삼각형 생성 
                    Triangle triangle;
                    MeshInfo mesh;
                    Point vertex;
                    Point voxelCenter;
                    bool trianglePush = false;
                    for (int i = 0; kTriangleTable[cubeIndex][i] != -1; i += 3) 
                    { 
                        int vertexIndex1 = kTriangleTable[cubeIndex][i];
                        int vertexIndex2 = kTriangleTable[cubeIndex][i+1];
                        int vertexIndex3 = kTriangleTable[cubeIndex][i+2];

                        triangle.e0 = vertexIndex1;
                        triangle.e1 = vertexIndex2;
                        triangle.e2 = vertexIndex3;
                        triangleVertex.push_back(triangle);
                        voxelCenter = voxelUpdate.centerVoxel(voxelIndex);
                        for(int k = 0; k < 3; k ++)
                        {
                            if(k == 0)
                            {
                                vertex = getSDFVertex(vertexIndex1, voxelCenter);
                                mesh.x = vertex(0);
                                mesh.y = vertex(1);
                                mesh.z = vertex(2);
                                mesh.red = voxelUpdate.voxel[x][y][z].red;
                                mesh.green = voxelUpdate.voxel[x][y][z].green;
                                mesh.blue = voxelUpdate.voxel[x][y][z].blue;
                                // if (isDuplicateExists(PointVector, mesh) == false) 
                                // {
                                //     PointVector.push_back(mesh);
                                //     trianglePush = true;
                                // }
                                PointVector.push_back(mesh);
                            }
                            else if(k == 1)
                            {   
                                vertex = getSDFVertex(vertexIndex2, voxelCenter);
                                mesh.x = vertex(0);
                                mesh.y = vertex(1);
                                mesh.z = vertex(2);
                                mesh.red = voxelUpdate.voxel[x][y][z].red;
                                mesh.green = voxelUpdate.voxel[x][y][z].green;
                                mesh.blue = voxelUpdate.voxel[x][y][z].blue;
                                // if (isDuplicateExists(PointVector, mesh)== false) 
                                // {
                                //     PointVector.push_back(mesh);
                                //     trianglePush = true;
                                // }
                                PointVector.push_back(mesh);
                            }
                            else if(k == 2)
                            {
                                vertex = getSDFVertex(vertexIndex3, voxelCenter);
                                mesh.x = vertex(0);
                                mesh.y = vertex(1);
                                mesh.z = vertex(2);
                                mesh.red = voxelUpdate.voxel[x][y][z].red;
                                mesh.green = voxelUpdate.voxel[x][y][z].green;
                                mesh.blue = voxelUpdate.voxel[x][y][z].blue;
                                // if (isDuplicateExists(PointVector, mesh)== false) 
                                // {
                                //     PointVector.push_back(mesh);
                                //     trianglePush = true;
                                // }
                                PointVector.push_back(mesh);
                            }
                        }
                        // if(trianglePush == true) triangleVertex.push_back(triangle);

                    }
                }else continue;
            }
        }
    }
}



void CreateMesh::writePLY(int num) 
{
    printf("start writting\n");
    std::string filename = "mesh" + to_string(num) + ".ply";
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
    file << "property uchar red" << std::endl;
    file << "property uchar green" << std::endl;
    file << "property uchar blue" << std::endl;
    file << "element face " << triangleVertex.size() << std::endl;
    file << "property list uint8 int32 vertex_indices" << std::endl;
    file << "end_header" << std::endl;
    for(const MeshInfo& mesh : PointVector) 
    {
        file << mesh.x << " " << mesh.y << " " << mesh.z << " " << to_string(mesh.red)
            << " " << to_string(mesh.green) << " " << to_string(mesh.blue) << std::endl;
    }
    int i = 0;

    for(const Triangle& triangle : triangleVertex)
    {
        file << "3 " << i << " " << i+1 << " " << i + 2 << std::endl;
        i += 3;
    }

    file.close();
    std::cout << "PLY file created: " << filename << std::endl;
}