#include "GeneratePointCloud.h"

int main(int argc, char* argv[])
{
    string rgb_list_file = argv[1];
    string depth_list_file = argv[2];
    string trajectory_file = argv[3];
    GeneratePointCloud generatePointCloud;

    map<double, vector<string> >  rgb_list = generatePointCloud.read_file_list(rgb_list_file);
    map<double, vector<string> >  depth_list = generatePointCloud.read_file_list(depth_list_file);
    map<double, vector<string> >  pose_list = generatePointCloud.read_file_list(trajectory_file);

    vector<pair<double, double> > rgb_depth_list = generatePointCloud.associate_two(rgb_list, depth_list);
    vector<pair<double, double> > depth_pose_list = generatePointCloud.associate_two(pose_list, depth_list);
    vector<tuple<double, double, double> > rgb_pose_depth_list = generatePointCloud.associate_three(rgb_depth_list, depth_pose_list);

    int sizeNum = 0;
    for (const auto& t : rgb_pose_depth_list) 
    {
        cout << fixed;
        cout << setprecision(6);
        cout << "[" << sizeNum << "] : " << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << endl;
        sizeNum += 1;
    }
    
    return 0;
}