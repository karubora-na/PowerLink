#pragma once

#include <array>
class Road
{
private:

	enum RoadRotateState {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};
	struct DrawBoxPos {
		int left_upper_x;
		int left_upper_y;
		int right_lower_x;
		int right_lower_y;
	};

public:

	Road(int road_state);
	~Road();

	void update(bool can_control);
	void draw();
	void create(double x, double y);

	double getBoxSize();
	double getBoxHalfSize();
	bool getHasPower();
	int getForm();
	int getRotate();
	int getRoadDirection(int idx, int road_idx);
	bool getIsControl();

	void setHasPower(bool set_value);
	void setIsCenter();
	void setIsControl(bool set_value);

private:

	void setRoadDrawPos();
	void setRoadColor(bool has_power);
	void setCenterRoadFrameColor();
	void setRoadDirection();

	void drawRoad();

	DrawBoxPos getDrawRoadPosTmp(int road_rotate_state);

public:

	static const int  BOX_SIZE = 30;
	static const int BOX_HALF_SIZE = BOX_SIZE / 2;
	static const int BOX_DISTANCE = 1;

	static const int CORNER = 0;
	static const int STRAIGHT_LINE = 1;
	static const int SENTER_ROAD = 2;

	static const int MAX_ROAD_TMP = 4;
	static const int MAX_ROAD = 2;
	static const int MAX_ROAD_ROTATE_TYPE = 4;

	static const int ROAD_WIDE_RANGE = BOX_HALF_SIZE;
	static const int ROAD_SMALL_RANGE = 2;

private:


	int _road_form;
	int _road_rotate;
	bool _has_power;
	int _pos_x;
	int _pos_y;
	bool _is_center;
	bool _is_control;

	std::array<int,MAX_ROAD> _road_direction;

	DrawBoxPos _draw_road_pos_tmp[MAX_ROAD_TMP];
	DrawBoxPos _draw_frame_pos;
	DrawBoxPos _draw_road_pos[MAX_ROAD];
	unsigned int _frame_color;
	unsigned int _road_color;
};

