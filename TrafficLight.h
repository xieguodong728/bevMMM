#include "data_common.h"

struct TrafficLight
{
    int Id;
    int Type;
    int Colour;

    // enum Type{
    //     STRAIGHT = 0,
    //     LEFT = 1,
    //     RIGHT = 2,
    //     U_TURN = 3,
    //     TURN_RIGHT_STRAIGHT = 4,
    //     TURN_LEFT_STRAIGHT = 5,
    //     CIRCULAR = 6
    // }; 

    // enum Colour{
    //     RED = 0,
    //     YELLOW = 1,
    //     GREEN = 2,
    //     BLACK = 3,
    //     YELLOW_FLASH = 4,
    //     UNKNOWN = 5
    // };

    Point3D Poistion;
    float RemainingTime;
};

/*
   to do

*/
struct ObjectTypeStruct
{
    // type1: 信号灯 指示牌
    int type1;

    // type2: 红绿灯 闪光灯 指路牌 指示牌 警告指示牌 禁止指示牌
    int type2;

    // type3: 
    int type3;

};
struct TrafficPredict
{
    string objectId;
    string name;
    Point3D position;
    uint16_t distance;
};


//
//class TrafficLightNetwork
//{
//private:
//    Header header;
//
//    std::vector<TrafficLight> ListOfTrafficLight;
//
//    int MaxNoTrafficLight;
//
//    /* data */
//public:
//    TrafficLightNetwork(std::vector<TrifficLightBox> TrafficLightVec);
//    ~TrafficLightNetwork();
//};
//
//TrafficLightNetwork::TrafficLightNetwork(std::vector<TrifficLightBox> TrafficLightVec)
//{
//    ListOfTrafficLight.clear();
//    MaxNoTrafficLight = TrafficLightVec.size();
//    for (auto light : TrafficLightVec)
//    {
//        ListOfTrafficLight.push_back(light);
//    }
//}
//
//TrafficLightNetwork::~TrafficLightNetwork()
//{
//}
