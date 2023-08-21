#include "../include/voxelUpdate.h"
#include "cmath"

float VoxelUpdate::getSDF(const Point& camera, const Point& point, VoxelIndex targetIndex)
{
    Point voxelCenter;
    if(targetIndex.index_x <= 0 || targetIndex.index_y <= 0 || targetIndex.index_z <= 0) return 0;
    else
    {
        voxelCenter = centerVoxel(targetIndex);
        const Point voxelTocamera = voxelCenter - camera;
        const Point pointTocamera = point - camera;

        const float dist = pointTocamera.norm();
        const float projectDist = voxelTocamera.dot(pointTocamera)/dist;
        const float sdf = dist - projectDist;
        return sdf;
    }
}

float VoxelUpdate::exponentialWeight(float dist)
{
    float epsilon = 0.01;
    float delta = 0.05;
    float sigma = 1;
    if (dist < epsilon) return 1.0f;
    else if (dist >= epsilon && dist <= delta) return std::exp(-sigma * std::pow(dist - epsilon, 2));
    else return 0.0f;
}

float VoxelUpdate::linearWeight(float dist)
{
    float epsilon = 0.01;
    float delta = 0.05;
    if(dist < epsilon) return 1.0f;
    else if(dist >= epsilon && dist <= delta) return (-25*dist + 1.25);
    else return 0.0f;
}

float VoxelUpdate::constantWeight(float dist) 
{
    return 1;
}

float VoxelUpdate::narrowExpWeight(float dist)
{
    float epsilon = 0.01;
    float delta = 0.05;
    float sigma = 1;
    if (dist < epsilon && dist > epsilon) return 1.0f;
    else if(dist <= -epsilon && dist >= -delta) return std::exp(-sigma * std::pow(dist - epsilon, 2));
    else if (dist >= epsilon && dist <= delta) return std::exp(-sigma * std::pow(-1*dist - epsilon, 2));
    else return 0.0f;   
}

float VoxelUpdate::narrowLinearWeight(float dist)
{
    float epsilon = 0.01;
    float delta = 0.05;
    if(dist < epsilon && dist > epsilon) return 1.0f;
    else if(dist <= -epsilon && dist >= -delta) return (25*dist + 1.25);
    else if(dist >= epsilon && dist <= delta) return (-25*dist + 1.25);
    else return 0.0f;
}

float VoxelUpdate::normalDistributionWeight(float dist)
{
    float mean = 0;
    float variance = 0.05;
    float coefficient = 1.0 / (std::sqrt(2.0 * M_PI * variance));
    float exponent = -((dist - mean) * (dist - mean)) / (2.0 * variance);
    return coefficient * std::exp(exponent);
}

void VoxelUpdate::updateSDF(VoxelIndex currentIndex, float currentSDF, float weightValue)
{
    if(currentIndex.index_x <= 0 || currentIndex.index_y <= 0 || currentIndex.index_z <= 0) return;
    else
    {
        float prevSDF = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf;
        float prevWeight = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight;
        //update current sdf
        voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].sdf = 
            (prevWeight * prevSDF + weightValue*currentSDF)/(prevWeight+weightValue);
    }
}

void VoxelUpdate::updateWeight(VoxelIndex currentIndex, float weightValue)
{
    if(currentIndex.index_x <= 0 || currentIndex.index_y <= 0 || currentIndex.index_z <= 0) return;
    else
    {
        float prevWeight = voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight;
        //update voxel Weight
        voxel[currentIndex.index_x][currentIndex.index_y][currentIndex.index_z].weight =
            min(prevWeight + weightValue, weightMax);
    }
}

void VoxelUpdate::getColor(VoxelIndex centerIndex, uchar red, uchar green, uchar blue)
{
    if(centerIndex.index_x <= 0 || centerIndex.index_y <= 0 || centerIndex.index_z <= 0) return;
    else
    {
        voxel[centerIndex.index_x][centerIndex.index_y][centerIndex.index_z].red = red;
        voxel[centerIndex.index_x][centerIndex.index_y][centerIndex.index_z].blue = blue;
        voxel[centerIndex.index_x][centerIndex.index_y][centerIndex.index_z].green = green;
    }
}