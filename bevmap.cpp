#include "BEVMAP.h"
//#include "Lane.h"

int BEVMAP::GetObject3DListFromJson(string Jsonfile) {

	ifstream fs;
	fs.open(Jsonfile, ios::in);

	Json::Reader reader;
	Json::Value value;

	if (!fs.is_open()) {
		cout << " open jsonfile fail " << endl;
		return 0;
	}

	if (!reader.parse(fs, value, true)) {
		cout << "read error " << endl;
		return 0;
	}

	//gt_boxes
	Json::Value gt_boxes = value["gt_boxes"];
	Json::Value gt_names = value["gt_names"];

	int size = gt_boxes.size();

	//Object3D* object3d = new Object3D[size];

	Object3D object3d;
	for (int i = 0; i < size; i++) {
		std::string ss = gt_names[i].toStyledString();

		string car = "car";

		// only test car now 
		/*  to do */

		if (ss.find(car) == string::npos) {
			//cout << "find car" << endl;
			continue;
		}

		object3d.TypeStringName = ss;

		if (gt_boxes[i].size() != 7) {
			cout << "gt_boxes.size wrong " << endl;
			return 0;
		}

		object3d.referencePoint.x = gt_boxes[i][0].asFloat();
		object3d.referencePoint.y = gt_boxes[i][1].asFloat();
		object3d.referencePoint.z = gt_boxes[i][2].asFloat();

		printf("%d,  %.3f,  %.3f,  %.3f\n", i, object3d.referencePoint.x, object3d.referencePoint.y, object3d.referencePoint.z);

		object3d.objectDimension.length = gt_boxes[i][3].asFloat();
		object3d.objectDimension.width = gt_boxes[i][4].asFloat();
		object3d.objectDimension.height = gt_boxes[i][5].asFloat();

		object3d.yawAngle = gt_boxes[i][6].asFloat();

		Object3DList.push_back(object3d);
	}


	fs.close();

	return 1;
}


int BEVMAP::GetLaneLineListListFromJson(string Jsonfile) {

	ifstream fs;
	fs.open(Jsonfile, ios::in);

	Json::Reader reader;
	Json::Value value;

	if (!fs.is_open()) {
		cout << " open jsonfile fail " << endl;
		return 0;
	}

	if (!reader.parse(fs, value, true)) {
		cout << "read error " << endl;
		return 0;
	}

	Json::Value lanes = value["lane_lines"];

	int size = lanes.size();
	
	LaneLine laneline;

	int count = 0;

	for (int i = 0; i < lanes.size(); i++) {

		Json::Value category = lanes[i]["category"];

		laneline.Type = category.asInt();

		laneline.lineId = i;

		Json::Value xyz = lanes[i]["xyz"];

		int pointSize = xyz.size();

		laneline.linePoints = new Point3D[pointSize];

		Eigen::VectorXd vec_x(pointSize);
		Eigen::VectorXd vec_y(pointSize);

		for (int p = 0; p < pointSize; p++) {

			laneline.linePoints[p].x = xyz[p][0].asFloat();
			laneline.linePoints[p].y = xyz[p][1].asFloat();
			laneline.linePoints[p].z = xyz[p][2].asFloat();

			//printf("%.3f,  %.3f,  %.3f\n",  laneline.linePoints[p].x, laneline.linePoints[p].y, laneline.linePoints[p].z);

			count++;
			/* to do  */
	// just for test 

			vec_x[p] = laneline.linePoints[p].x;
			vec_y[p] = laneline.linePoints[p].y;

			// 沿着y轴去切 可以省去排序

		}

		laneline.coeffs = polyfit(vec_y, vec_x, 3);

		LaneLineList.push_back(laneline);
	}
	fs.close();
}


int BEVMAP::LaneMatch3dObject() {

	//sizeof(object3d)
	int objectnumber = Object3DList.size();
	int lanelinenumber = LaneLineList.size();

	for (int i = 0; i < objectnumber; i++) {

		Object3D obj = Object3DList[i];

		if (fabs(obj.referencePoint.x) > 100 || fabs(obj.referencePoint.y) > 100)
			continue;

		Point2D left_up_point, left_down_point, right_up_point, right_down_point;

		left_up_point = AddTwoPoint2d(obj.referencePoint, GetYawRotationCord(obj.yawAngle, -obj.objectDimension.width / 2, obj.objectDimension.length / 2));
		left_down_point = AddTwoPoint2d(obj.referencePoint, GetYawRotationCord(obj.yawAngle, -obj.objectDimension.width / 2, -obj.objectDimension.length / 2));
		right_up_point = AddTwoPoint2d(obj.referencePoint, GetYawRotationCord(obj.yawAngle, obj.objectDimension.width / 2, obj.objectDimension.length / 2));
		right_down_point = AddTwoPoint2d(obj.referencePoint, GetYawRotationCord(obj.yawAngle, obj.objectDimension.width / 2, -obj.objectDimension.length / 2));


		//printf("ref_point: %.3f,%.3f, lu point: %.3f,%.3f,  ld point: %.3f,%.3f, ru point: %.3f,%.3f, rd point: %.3f,%.3f,\n", 
		//	obj.referencePoint.x, obj.referencePoint.y, 
		//	left_up_point.x, left_up_point.y,
		//	left_down_point.x, left_down_point.y,
		//	right_up_point.x, right_up_point.y,
		//	right_down_point.x, right_down_point.y
		//	);

		double inteplotX, gap, x_leftgap, x_right_gap;

		double maxgap = 9999999.0;
		double mingap = -9999999.0;

		int leftid = -1;
		int rightid = -1;

		for (int j = 0; j < lanelinenumber; j++) {

			//LaneLine line = LaneLineList[j];
			inteplotX = polyeval(LaneLineList[j].coeffs, obj.referencePoint.y);

			gap = obj.referencePoint.x - inteplotX;

			if (gap < 0) {
				x_leftgap = gap;
				if (mingap < x_leftgap) {
					mingap = x_leftgap;
					leftid = j;
				}
			}
			else {
				x_right_gap = gap;
				if (maxgap > x_right_gap) {
					maxgap = x_right_gap;
					rightid = j;
				}
			}
		}

		if (rightid == -1) rightid = leftid;
		if (leftid == -1)  leftid = rightid;

		// set the laneline id of 3d object
		Object3DList[i].laneLeftId = LaneLineList[leftid].lineId;
		Object3DList[i].laneRightId = LaneLineList[rightid].lineId;


		/* to do

		// 3d object not in lane

		*/

		//  Calculate the distance from the edge point to the laneline
		Object3DList[i].laneOffsetLeft[0] = GetVerticalDistance(left_up_point.x, left_up_point.y, LaneLineList[leftid].coeffs);
		Object3DList[i].laneOffsetLeft[1] = GetVerticalDistance(left_down_point.x, left_down_point.y, LaneLineList[leftid].coeffs);
		Object3DList[i].laneOffsetRight[0] = GetVerticalDistance(right_up_point.x, right_up_point.y, LaneLineList[rightid].coeffs);
		Object3DList[i].laneOffsetRight[1] = GetVerticalDistance(right_down_point.x, right_down_point.y, LaneLineList[rightid].coeffs);
	}
}


BEVMAP::~BEVMAP()
{
}

BEVMAP::BEVMAP(Header inputHeader)
{
	header = inputHeader;
}
void BEVMAP::PrintBevmapInfo() {

	int size = Object3DList.size();
	cout << "total size: " << size << endl;

	for (int i = 0; i < size; i++) {
		Object3D obj = Object3DList[i];

		printf("i is %d, leftid: %d, rightid: %d\n", i, obj.laneLeftId, obj.laneRightId);

		printf("left_up offset: %.3f, right_up offset: %.3f\n", obj.laneOffsetLeft[0], obj.laneOffsetRight[0]);
		printf("left_down offset: %.3f, right_down offset: %.3f\n\n", obj.laneOffsetLeft[1], obj.laneOffsetRight[1]);
	}
}

void BEVMAP::Init() {

	Object3DList.clear();
	LaneLineList.clear();
	LaneList.clear();
	StopLineList.clear();
	ListOfTrafficLight.clear();
	obj_predict_list.clear();

}
double GetVerticalDistance(double x, double y, Eigen::VectorXd coeffs) {

	double threshold = 0.01;
	double point1_x = polyeval(coeffs, y);
	double point2_x = polyeval(coeffs, y + threshold);

	double theta = atan(threshold / (point2_x - point1_x));
	double res = fabs((point1_x - x) * sin(theta));

	return res;
}

Point2D GetYawRotationCord(double yawAngle, double x, double y) {

	Point2D p;

	// yawAngle [-pi,pi]

	p.x = cos(yawAngle) * x - sin(yawAngle) * y;
	p.y = sin(yawAngle) * x + cos(yawAngle) * y;

	return p;
}

Point2D AddTwoPoint2d(Point3D a, Point2D b) {
	Point2D res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}


double polyeval(Eigen::VectorXd coeffs, double x)
{
	double result = 0.0;
	for (int i = 0; i < coeffs.size(); i++)
	{
		result += coeffs[i] * pow(x, i);
	}
	return result;
}



Eigen::VectorXd polyfit(Eigen::VectorXd xvals, Eigen::VectorXd yvals, int order)
{
	assert(xvals.size() == yvals.size());
	assert(order >= 1 && order <= xvals.size() - 1);
	Eigen::MatrixXd A(xvals.size(), order + 1);

	for (int i = 0; i < xvals.size(); i++)
		A(i, 0) = 1.0;

	for (int j = 0; j < xvals.size(); j++)
	{
		for (int i = 0; i < order; i++)
			A(j, i + 1) = A(j, i) * xvals(j);
	}

	auto Q = A.householderQr();
	auto result = Q.solve(yvals);
	return result;
}


