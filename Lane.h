#include "data_common.h"



struct LaneLine
{
    // enum Type{
        
    //     WHITE_DASHED = 0,
    //     WHITE_SOLID = 1,
    //     YELLOW_DASHED = 2 ,
    //     YELLOW_SOLID = 3,
    //     UNKNOWN = 4
    // };
    int Type;
    
    float confidence;
    Point3D* linePoints;
    Eigen::VectorXd coeffs;
    int lineId;
};

struct StopLine
{
    // enum Type{

    //     STOP_LINE = 0,
    //     ZEBRA_LINE = 1,
    //     ZEBRA_STOP_LINE = 2 ,
    //     VIRTURAL_STOP_LINE = 3,
    //     UNKNOWN = 4
    // };

    int Type;
    float confidence;
    Point2D LeftStart;
    Point2D RightEnd;

};

struct Lane
{
    int LaneId;
    // enum Type{

    //     STRAIGHT = 0,
    //     TURN_RIGHT = 1,
    //     TURN_LEFT = 2 ,
    //     TURN_AROUND = 3,
    //     OPPOSTIE = 4
    // };
    int Type;
    bool isPassable;
    int LineId[2];

    float Distance = 0.0;
    //int RightLineId;

};



struct  LaneNetwork
{
    Header header;
    
    LaneLine* ListOfLaneLine;

    Lane* ListOfLane;

    StopLine* ListOfStopLine;
    
};
