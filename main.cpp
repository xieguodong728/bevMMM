#include "BEVMAP.h"

int main() {
	string objectJsonfile = "frame_7.json";
	string laneJsonfile = "n008-2018-08-01-15-16-36-0400__CAM_FRONT__1533151607012404.json";

	Header header;
	header.Frame = 0;
	header.ModuleID = 1;
	header.m_VersionID = { 1,1,1 };
	header.SequenceNum = 1;

	BEVMAP bevmap(header);
	bevmap.Init();

	int readObject = bevmap.GetObject3DListFromJson(objectJsonfile);
	int readLane = bevmap.GetLaneLineListListFromJson(laneJsonfile);

	if (readObject && readLane == 0) {
		cout << " readfile wrong " << endl;
		return 0;
	}

	int laneMatchobject = bevmap.LaneMatch3dObject();

	bevmap.PrintBevmapInfo();

	return 1;

}