#pragma once
#include "Scene.h"
#include "Road.h"

class Game :public Scene
{
public:

	enum Direction {
		UPPER,
		RIGHT,
		LOWER,
		LEFT
	};
public:
	Game();
	~Game();

	virtual void update()override;
	virtual void draw()override;

private:

	void powerConnect(int road_idx, int check_direction);
	void drawControlRoadParameter(int road_index);
	int getCheckRoadIdx(int road_idx, int check_direction);
	int getCheckRoadDirection(int check_direction);
	bool checkEnd(int road_idx, int check_road_idx);

private:

	static const int ROAD_ROW_NUM = 15;
	static const int ROAD_COLUMON_NUM = 15;
	static const int MAX_ROAD_OBJ = ROAD_ROW_NUM * ROAD_COLUMON_NUM;
	static const int ROAD_LAST_INDEX = MAX_ROAD_OBJ - 1;
	static const int ROAD_CENTER_INDEX = ROAD_LAST_INDEX / 2;
	static const int MAX_SENTER_EVERY_DIRECTION_ROAD_OBJ = 4;
	static const int CLEAR_STATE_NUM = 4;

	const int START_CONTROL_ROAD = ROAD_CENTER_INDEX-ROAD_ROW_NUM;
	const int ROAD_GROUP_LEFT_END_POS = 960 / 2 - ROAD_ROW_NUM / 2 * Road::BOX_SIZE;
	const int ROAD_GROUP_TOP_EDGE_POS = 540 / 2 - ROAD_COLUMON_NUM / 2 * Road::BOX_SIZE;
	const int MAX_FRAME = 60;
	const int CAN_INPUT_DISTANCE_TIME = 150;

	int _control_road_index;
	int _plus_time_count;
	int _time;
	bool _end_game;
	int _result_time;
	bool _is_clear[CLEAR_STATE_NUM];

	Road* _road_obj[MAX_ROAD_OBJ];
	int _senter_every_direction_road_obj_idx[MAX_SENTER_EVERY_DIRECTION_ROAD_OBJ];
};

