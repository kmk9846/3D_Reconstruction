#include "./include/GeneratePointCloud.h"

bool comparePointsX(const PointsData& p1, const PointsData& p2)
{
    if(p1.x == p2.x)
    {
        if(p1.y == p2.y) return p1.z < p2.z;   
        else return p1.y < p2.y;
    }
    else return p1.x > p2.x;
}

bool comparePointsY(const PointsData& p1, const PointsData& p2)
{
    if(p1.y == p2.y) return p1.z < p2.z;
    else return p1.y > p2.y;
}

int main(int argc, char* argv[])
{
    string filePath = argv[1];
    int startFile = atoi(argv[2]);
    int fileNum = atoi(argv[3]);
    int size = atoi(argv[4]);
    string rgbfile = "/rgb/";
    string depthfile = "/depth/";

    //GeneratePointCloud class 의 객체 선언
    GeneratePointCloud generatePointCloud;

    //rgb.txt, depth.txt, ground.txt 를 가져와서 비슷한 timestamp 대의 <rgb, depth, pose> tuple 을 만든다.
    map<double, vector<string> >  rgb_list = generatePointCloud.read_file_list(filePath + "/rgb.txt");
    map<double, vector<string> >  depth_list = generatePointCloud.read_file_list(filePath + "/depth.txt");
    map<double, vector<string> >  pose_list = generatePointCloud.read_file_list(filePath + "/groundtruth.txt");
    vector<pair<double, double> > rgb_depth_list = generatePointCloud.associate_two(rgb_list, depth_list);
    vector<pair<double, double> > depth_pose_list = generatePointCloud.associate_two(pose_list, depth_list);
    vector<tuple<double, double, double> > rgb_pose_depth_list = generatePointCloud.associate_three(rgb_depth_list, depth_pose_list);
    
    // groundtruth.txt 파일의 pose 를 모두 4x4 matrix 로 변경하여 poseMatrix 에 저장
    generatePointCloud.poseMatrix = generatePointCloud.read_trajectory(filePath + "/groundtruth.txt");
    

    //size 만큼의 timestamp를 건너뛰면서 gernerate_pointcloud 함수를 실행
    printf("size : %lu\n", rgb_pose_depth_list.size());
    for (int i = startFile; i < fileNum; i += size) 
    {
        string rgbPNG = filePath + rgbfile + to_string(get<0>(rgb_pose_depth_list[i])) + ".png";
        string depthPNG = filePath + depthfile + to_string(get<1>(rgb_pose_depth_list[i])) + ".png";
        Eigen::Matrix4f matrixPose = generatePointCloud.poseMatrix[get<2>(rgb_pose_depth_list[i])].cast<float>();
        generatePointCloud.generate_pointcloud(rgbPNG, depthPNG, matrixPose);
        //
        Eigen::Vector3f cameraOrigin(matrixPose(0, 3), matrixPose(1, 3), matrixPose(2, 3));
        cout << "camera : " << cameraOrigin(0) << " , " << cameraOrigin(1) << " , " << cameraOrigin(2) << endl;
    }

    //generate_pointcloud 함수가 끝난 후에 맴버변수인 points 를 .ply 파일을 result 라는 이름으로 생성
    //build 파일에 result.ply 파일이 생성된다.
    generatePointCloud.write_ply("result_test.ply", generatePointCloud.points);
    return 0;
}
