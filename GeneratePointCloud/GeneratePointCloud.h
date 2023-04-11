#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <tuple>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace cv;
using namespace Eigen;

typedef Matrix<double, 4, 4> Matrix4d;
struct Points{
    float x;
    float y;
    float z;
    uchar red;
    uchar green;
    uchar blue;
};

class GeneratePointCloud{
public :
    GeneratePointCloud();
    vector<Points> points;
    map<double, vector<string> > read_file_list(string filename);
    vector<pair<double, double> > associate_two(map<double, vector<string> > first_list, map<double, vector<string> > second_list);
    vector<tuple<double, double, double> > associate_three(vector<pair<double, double> > rgb_depth, 
                                                        vector<pair<double, double> > pose_depth);
    Matrix4f createTransformMatrix(const Vector3f& position, const Vector3f& eulerAngles);
    Vector3f quaternionToEuler(Quaternionf q);
    void generate_pointcloud(const string& rgb_file, const string& depth_file, const Matrix4f& transforms);
    void write_ply(string ply_file, vector<Points> points);

private:
    double offset;
    float max_difference;
    int scalingFactor;
    float centerX;
    float centerY;
    int focalLength_x;
    int focalLength_y;
};