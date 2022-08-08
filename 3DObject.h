#include "data_common.h"

struct Velocity3D
{
    float mx;
    float my;
    float mz;
};

struct Object3D
{
    //Header header;
    int objectId;

    // enum objectType {
    //     Car = 0,
    //     Truck = 1,
    //     Bus = 2,
    //     Trailer = 3,
    //     Construction_vehicle = 4,
    //     Motorcycle = 5,
    //     Bicycle = 6,
    //     Pedestrian = 7,
    //     Traffic_cone = 8,
    //     Barrier = 9,
    //     Logistics_car = 10,
    //     Tricycle = 11,
    //     Unknow_static = 12,
    //     Unknow_movable = 13
    // };

    int type;
    string TypeStringName;

    float classConfidence;
    bool isMoveable;
    Point3D referencePoint;
    CovarianceMatrix PoistionCovarianceMatrix;
    Dimension objectDimension;
    Velocity3D ObjectVelocity;
    CovarianceMatrix MoveableObjectPoistionCovarianceMatrix;
    int laneLeftId;
    int laneRightId;
    float laneOffsetLeft[2];
    float laneOffsetRight[2];
    float yawAngle;

    // enum LightStatus{
    //      NA = 0,
    //      TurnLeft = 1,
    //      TurnRight = 2,
    //      DoubleFlash = 3,
    //      Brake = 4
    //  };
    int LightStatus;
};
//
//class 3DObject
//{
//private:
//    Header header;
//    int objectId;
//
//    // enum objectType {
//    //     Car = 0,
//    //     Truck = 1,
//    //     Bus = 2,
//    //     Trailer = 3,
//    //     Construction_vehicle = 4,
//    //     Motorcycle = 5,
//    //     Bicycle = 6,
//    //     Pedestrian = 7,
//    //     Traffic_cone = 8,
//    //     Barrier = 9,
//    //     Logistics_car = 10,
//    //     Tricycle = 11,
//    //     Unknow_static = 12,
//    //     Unknow_movable = 13
//    // };
//
//    int type;
//    string TypeStringName;
//
//    float classConfidence;
//    bool isMoveable;
//    Point3D referencePoint;
//    CovarianceMatrix PoistionCovarianceMatrix;
//    Dimension objectDimension;
//    Velocity3D ObjectVelocity;
//    CovarianceMatrix MoveableObjectPoistionCovarianceMatrix;
//    int laneLeftId;
//    int laneRightId;
//    float laneOffsetLeft[2];
//    float laneOffsetRight[2];
//    float yawAngle;
//
//    // enum LightStatus{
//    //      NA = 0,
//    //      TurnLeft = 1,
//    //      TurnRight = 2,
//    //      DoubleFlash = 3,
//    //      Brake = 4
//    //  };
//    int LightStatus;
//    //
//
//public:
//    3DObject(Box box);
//    ~3DObject();
//
//    setLeftLaneID(int id);
//    setRightLaneID(int id);
//    setLeftLaneOffset(float UpPoint, float DownPoint);
//    setRightLaneOffset(float UpPoint, float DownPoint);
//    setIsMoveable(bool MoveableFlag);
//
//    3DObject::ReadDataFromJson(string jsonfile);
//};
//
//3DObject ::3DObject(Box box)
//{
//
//    objectId = box.id;
//    type = box.category;
//    classConfidence = box.classConfidence;
//
//    referencePoint.x = box.x;
//    referencePoint.y = box.y;
//    referencePoint.z = box.z;
//
//    objectDimension.width = box.width;
//    objectDimension.height = box.height;
//    objectDimension.length = box.length;
//
//    ObjectVelocity.mx = box.vx;
//    ObjectVelocity.my = box.vy;
//    ObjectVelocity.mz = box.vz;
//
//    yawAngle = box.yawAngle;
//}
//
//3DObject ::~3DObject()
//{
//}
//
//3DObject::setLeftLaneID(int id)
//{
//    laneLeftId = id;
//}
//
//3DObject::setRightLaneID(int id)
//{
//    laneRightId = id;
//}
//3DObject::setLeftLaneOffset(float UpPoint, float DownPoint)
//{
//    laneOffsetLeft[0] = UpPoint;
//    laneOffsetLeft[1] = DownPoint;
//}
//3DObject::setRightLaneOffset(float UpPoint, float DownPoint)
//{
//    laneOffsetRight[0] = UpPoint;
//    laneOffsetRight[1] = DownPoint;
//}
//
//3DObject::setIsMoveable(bool MoveableFlag)
//{
//    isMoveable = MoveableFlag;
//}