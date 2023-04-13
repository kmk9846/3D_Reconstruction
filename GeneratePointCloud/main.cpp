#include "GeneratePointCloud.h"

int main(int argc, char* argv[])
{
    string filePath = argv[1];
    int size = atoi(argv[2]);
    string rgbfile = "/rgb/";
    string depthfile = "/depth/";
    GeneratePointCloud generatePointCloud;
    map<double, vector<string> >  rgb_list = generatePointCloud.read_file_list(filePath + "/rgb.txt");
    map<double, vector<string> >  depth_list = generatePointCloud.read_file_list(filePath + "/depth.txt");
    map<double, vector<string> >  pose_list = generatePointCloud.read_file_list(filePath + "/groundtruth.txt");
    
    vector<pair<double, double> > rgb_depth_list = generatePointCloud.associate_two(rgb_list, depth_list);
    vector<pair<double, double> > depth_pose_list = generatePointCloud.associate_two(pose_list, depth_list);
    vector<tuple<double, double, double> > rgb_pose_depth_list = generatePointCloud.associate_three(rgb_depth_list, depth_pose_list);
    generatePointCloud.poseMatrix = generatePointCloud.read_trajectory(filePath + "/groundtruth.txt");
    
    for (int i = 0; i < rgb_pose_depth_list.size(); i += size) 
    {
        string rgbPNG = filePath + rgbfile + to_string(get<0>(rgb_pose_depth_list[i])) + ".png";
        string depthPNG = filePath + depthfile + to_string(get<1>(rgb_pose_depth_list[i])) + ".png";
        Matrix4f matrixPose = generatePointCloud.poseMatrix[get<2>(rgb_pose_depth_list[i])].cast<float>();
        generatePointCloud.generate_pointcloud(rgbPNG, depthPNG, matrixPose);
        // get<0>(rgb_pose_depth_list[i])
        // cout << "Element " << i << ": " << get<0>(myVector[i]) << " " << get<1>(myVector[i]) << " " << get<2>(myVector[i]) << endl;
    }

    generatePointCloud.write_ply("result.ply", generatePointCloud.points);

    // int sizeNum = 0;
    // for (const auto& t : rgb_pose_depth_list) 
    // {
    //     cout << fixed;
    //     cout << setprecision(6);
    //     cout << "[" << sizeNum << "] : " << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << endl;
    //     sizeNum += 1;
    // }
    return 0;
}