#include "GeneratePointCloud.h"

GeneratePointCloud::GeneratePointCloud()
{
    offset = 0.0;
    max_difference = 0.02;
    //default ROS
    scalingFactor = 5000;
    centerX = 319.5;
    centerY = 239.5;
    focalLength_x = 525;
    focalLength_y = 525;
}

map<double, vector<string> > GeneratePointCloud::read_file_list(string filename)
{
    map<double, vector<string> > lst;
    ifstream file(filename.c_str());
    if (!file) {
        cerr << "Cannot open " << filename << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        stringstream ss(line);
        vector<string> parts;
        string part;
        while (ss >> part) parts.push_back(part);
    
        if (parts.size() < 2) continue;

        double timestamp;
        stringstream(parts[0]) >> timestamp;
        lst[timestamp] = vector<string>(parts.begin() + 1, parts.end());
    }
    return lst;
}

vector<pair<double, double> > GeneratePointCloud::associate_two(map<double, vector<string> > first_list,
                                             map<double, vector<string> > second_list)
{
    vector<double> first_keys, second_keys;
    for (auto it = first_list.begin(); it != first_list.end(); it++) first_keys.push_back(it->first);
    for (auto it = second_list.begin(); it != second_list.end(); it++) second_keys.push_back(it->first);

    sort(first_keys.begin(), first_keys.end());
    sort(second_keys.begin(), second_keys.end());
    vector<pair<double, double> > matches;
    for (double a : first_keys) {
        vector<double>::iterator lower_it = lower_bound(second_keys.begin(), second_keys.end(), a - max_difference - offset);
        vector<double>::iterator upper_it = upper_bound(second_keys.begin(), second_keys.end(), a + max_difference - offset);
        for (vector<double>::iterator b_it = lower_it; b_it != upper_it; b_it++) {
            double b = *b_it;
            double time_diff = abs(a - (b + offset));
            if (time_diff < max_difference) {
                matches.push_back(make_pair(a, b));
                second_keys.erase(b_it);
                break;
            }
        }
    }
    return matches;
}

vector<tuple<double, double, double> > GeneratePointCloud::associate_three(vector<pair<double, double> > rgb_depth, 
                                                        vector<pair<double, double> > pose_depth)
{
    vector<tuple<double, double, double>> rgb_pose_depth;
    for (const auto& rgbdepth : rgb_depth) 
    {
        for(const auto& posedepth : pose_depth)
        {
            if(rgbdepth.second == posedepth.second) rgb_pose_depth.push_back(make_tuple(rgbdepth.first, rgbdepth.second,posedepth.first));
        }
    }

    return rgb_pose_depth;
}

Matrix4d GeneratePointCloud::toHomogeneousMatrix(const Vector3d& v)
{
    Matrix4d m = Matrix4d::Identity();
    m.block<3,1>(0,3) = v;
    return m;
}

vector<string> GeneratePointCloud::generate_pointcloud(const string& rgb_file, const string& depth_file, const Matrix4d& transforms)
{
    Mat rgb = imread(rgb_file);
    Mat depth = imread(depth_file, cv::IMREAD_UNCHANGED);

    std::vector<std::string> points;
    for (int v = 0; v < rgb.rows; v += 1) {
        for (int u = 0; u < rgb.cols; u += 1) {
            Vec3b color = rgb.at<Vec3b>(v, u);
            ushort depth_value = depth.at<ushort>(v, u);
            double Z = static_cast<double>(depth_value) / scalingFactor;
            if (Z == 0)
                continue;
            double X = (u - centerX) * Z / focalLength_x;
            double Y = (v - centerY) * Z / focalLength_y;
            Vector4d vec_org(X, Y, Z, 1);
            Vector4d vec_transf = transforms * vec_org;
            points.push_back(to_string(vec_transf[0]) + " " + to_string(vec_transf[1]) + " " + 
                to_string(vec_transf[2]) + " " + to_string(color[0]) + " " + to_string(color[1]) 
                + " " + to_string(color[2]) + " 1\n");
        }
    }

    return points;
}

void GeneratePointCloud::write_ply(string ply_file, vector<string> points)
{
    std::ofstream file(ply_file);
    file << "ply\n";
    file << "format ascii 1.0\n";
    file << "element vertex " << points.size() << "\n";
    file << "property float x\n";
    file << "property float y\n";
    file << "property float z\n";
    file << "property uchar red\n";
    file << "property uchar green\n";
    file << "property uchar blue\n";
    file << "property uchar alpha\n";
    file << "end_header\n";
    for (auto point : points) {
        file << point << "\n";
    }
    file.close();
}