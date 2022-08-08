#ifndef DATA_COMMON_H
#define DATA_COMMON_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <Eigen/Core>
#include <Eigen/QR>

using namespace std;
using namespace Eigen;

// 模块版本号 
struct VersionID
{
    int Major; 
    int Minor;
    int Patch;
};

// 时间戳
struct TimeStamp
{
    int TimeStampS;  // 整秒
    int TimeStampNs;  // 纳秒
};


struct Header{
    int ModuleID;  // 算法组件名称
    VersionID m_VersionID; 
    
    int SequenceNum;

    // enum Frame{
    //      NA = 0,
    //      VCS = 1,
    //      WGS84 = 2,
    //      UTM = 3
    // };

    int Frame;

};

struct Point2D
{
    float x;
    float y;
};

struct Point3D
{
    float x;
    float y;
    float z;
};

struct Polygon2d
{
    Point2D* Point2DList;
    int MaxNoPolygon2DPoint;
};

struct Polygon3D
{
    Point3D* Point3DList;
    int MaxNoPolygon3DPoint;
};

struct Dimension
{
    float height;
    float width;
    float length;
};

struct Quaternion
{
    float qx;
    float qy;
    float qz;
    float qw;
};

struct CovarianceMatrix
{
    /* TODO */
};

struct Box{
 
    int category;
    int id;
    float classConfidence;
    float x,y,z;
    float width,height,length;
    float vx,vy,vz;
    float yawAngle;

};

struct TrifficLightBox{
    int category;
    int id;
    int colour;
    float classConfidence;
    float x,y,z;
};

struct obj_predict
{
    /* data */
    string id;
    int type;
    string name;
    Point3D position;
    uint16_t distance;

};


#endif DATA_COMMON_H