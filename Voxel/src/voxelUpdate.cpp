#include "../include/voxelUpdate.h"

float VoxelUpdate::getSDF(const Point& origin, const Point& point, VoxelIndex centerIndex)
{
    Point voxelCenter;
    if(centerIndex.index_x <= 0 || centerIndex.index_y <= 0 || centerIndex.index_z <= 0) return 0;
    else
    {
        voxelCenter << static_cast<float>(centerIndex.index_x*VoxelUnit + VoxelUnit/2), static_cast<float>(centerIndex.index_y*VoxelUnit + VoxelUnit/2), 
                    static_cast<float>(centerIndex.index_z*VoxelUnit + VoxelUnit/2);
        const Point voxelToorigin = voxelCenter - origin;
        const Point pointToorigin = point - origin;

        const float dist = pointToorigin.norm();
        const float projectDist = voxelToorigin.dot(pointToorigin)/dist;

        // printf("target [%d] %f [%d] %f [%d] %f\n", centerIndex.index_x, voxelCenter(0), 
        //                 centerIndex.index_y, voxelCenter(1), centerIndex.index_z, voxelCenter(2));
        // printf("origin : %f %f %f\n", origin(0), origin(1), origin(2));
        // printf("point : %f %f %f\n", point(0), point(1), point(2));

        const float sdf = dist - projectDist;
        // printf("dist : %f - dot : %f = sdf %f\n", dist, projectDist, sdf);
        // if(sdf< 0)
        // {
        //     printf("center : [%d]%f [%d]%f [%d]%f\n", centerIndex.index_x, voxelCenter(0), centerIndex.index_y, voxelCenter(1),
        //         centerIndex.index_z, voxelCenter(2));
        //     printf("point : [%d]%f [%d]%f [%d]%f %f\n", centerIndex.index_x, point(0), centerIndex.index_y, point(1),
        //         centerIndex.index_z, point(2), sdf);
        // }
        return sdf;
    }
}

void VoxelUpdate::updateSDF(const Point& origin, const Point& point, VoxelIndex currentIndex, float currentSDF)
{
    if(currentIndex.index_x <= 0 || currentIndex.index_y <= 0 || currentIndex.index_z <= 0) return;
    else
    {
        if(voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf  == 1) 
            voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf = currentSDF;
        else
        {
            float prevSDF = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf;
            float prevWeight = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight;
            //update current sdf
            voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf = 
            (prevWeight * prevSDF + weight*currentSDF)/(prevWeight+weight);
        }
    }
}

void VoxelUpdate::updateWeight(VoxelIndex currentIndex)
{
    //Index currentIndex = findIndex(point);
    if(currentIndex.index_x <= 0 || currentIndex.index_y <= 0 || currentIndex.index_z <= 0) return;
    else
    {
        float prevWeight = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight;

        //update voxel Weight
        voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight =
            min(prevWeight + weight, weightMax);
    }
}

void VoxelUpdate::getColor(VoxelIndex centerIndex, uchar red, uchar green, uchar blue)
{
    if(centerIndex.index_x <= 0 || centerIndex.index_y <= 0 || centerIndex.index_z <= 0) return;
    else
    {
        //update voxel Weight
        voxel[centerIndex.index_x][centerIndex.index_y][centerIndex.index_z].red = red;
        voxel[centerIndex.index_x][centerIndex.index_y][centerIndex.index_z].blue = blue;
        voxel[centerIndex.index_x][centerIndex.index_y][centerIndex.index_z].green = green;
    }
}