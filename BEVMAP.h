#include "data_common.h"
#include "3DObject.h"
#include "Lane.h"
#include "TrafficLight.h"
#include <json/json.h>


class BEVMAP
{
private:
	/* data */
	Header header;

	vector <Object3D> Object3DList;

	vector<LaneLine> LaneLineList;
	vector<Lane> LaneList;
	vector<StopLine> StopLineList;

	vector<TrafficLight> ListOfTrafficLight;

	vector<obj_predict> obj_predict_list;

public:
	BEVMAP(Header inputHeader);
	~BEVMAP();

	void Init();
	int GetObject3DListFromJson(string json);
	int GetLaneLineListListFromJson(string json);

	/* to do */
	int GetObject3DList(vector <Object3D> VecObject3D);
	int GetLaneLineListList(vector<LaneLine> VecLaneLine);

	int GetObjPredictList(vector<obj_predict> VecObjPredict);


	int LaneMatch3dObject();
	void PrintBevmapInfo();



};


double GetVerticalDistance(double x, double y, Eigen::VectorXd coeffs);
Point2D GetYawRotationCord(double yawAngle, double x, double y);
Eigen::VectorXd polyfit(Eigen::VectorXd xvals, Eigen::VectorXd yvals, int order);
double polyeval(Eigen::VectorXd coeffs, double x);
Point2D AddTwoPoint2d(Point3D a, Point2D b);