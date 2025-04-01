#include "Road.h"
#include "DxLib.h"
#include "Controller.h"

extern Controller* _controller;

Road::Road(int road_state) {
	_pos_x = 0;
	_pos_y = 0;

	_draw_frame_pos.left_upper_x = 0;
	_draw_frame_pos.left_upper_y = 0;
	_draw_frame_pos.right_lower_x = 0;
	_draw_frame_pos.right_lower_y = 0;
	for (int i = 0; i < MAX_ROAD; i++) {
		_draw_road_pos[i].left_upper_x = 0;
		_draw_road_pos[i].left_upper_y = 0;
		_draw_road_pos[i].right_lower_x = 0;
		_draw_road_pos[i].right_lower_y = 0;
	}
	for (int i = 0; i < MAX_ROAD_TMP; i++) {
		_draw_road_pos_tmp[i].left_upper_x = 0;
		_draw_road_pos_tmp[i].left_upper_y = 0;
		_draw_road_pos_tmp[i].right_lower_x = 0;
		_draw_road_pos_tmp[i].right_lower_y = 0;
	}

	_frame_color = GetColor(255, 255, 255);
	_road_color = GetColor(255, 255, 255);

	_road_form = road_state;
	_road_rotate = GetRand(3);
	_has_power = false;
	_is_center = false;
	_is_control = false;
	for (int idx = 0; idx < MAX_ROAD; idx++) {
		_road_direction[idx] = 0;
	}
}

Road::~Road() {

}

void Road::update(bool can_control) {
	if (can_control) {

		_frame_color = GetColor(0,0,255);

		// 道を回転
		if (_controller->getIsKeyRelease(Controller::ENTER)) {

			_road_rotate++;
			if (_road_rotate >= MAX_ROAD_ROTATE_TYPE) {
				_road_rotate = 0;
			}

			for (int idx = 0; idx < MAX_ROAD; idx++) {
				_road_direction[idx]++;
				if (_road_direction[idx] >= 4) {
					_road_direction[idx] = 0;
				}
			}

			setRoadDrawPos();

		}
	}
	else {
		_frame_color = GetColor(255, 255, 255);
	}

	if (_road_form == SENTER_ROAD) {
		setCenterRoadFrameColor();
	}
}

void Road::draw() {

	// 外枠
	DrawBox((int)_draw_frame_pos.left_upper_x, (int)_draw_frame_pos.left_upper_y, (int)_draw_frame_pos.right_lower_x, (int)_draw_frame_pos.right_lower_y, _frame_color, _is_center);

	// 内部の線
	drawRoad();
}

void Road::create(double x, double y) {
	_pos_x = x;
	_pos_y = y;

	_draw_frame_pos.left_upper_x = _pos_x - BOX_SIZE / 2 + BOX_DISTANCE / 2;
	_draw_frame_pos.left_upper_y = _pos_y - BOX_SIZE / 2 + BOX_DISTANCE / 2;
	_draw_frame_pos.right_lower_x = _draw_frame_pos.left_upper_x + BOX_SIZE - BOX_DISTANCE / 2;
	_draw_frame_pos.right_lower_y = _draw_frame_pos.left_upper_y + BOX_SIZE - BOX_DISTANCE / 2;

	for (int i = 0; i < MAX_ROAD_TMP; i++) {
		switch (i) {
		case TOP:
			_draw_road_pos_tmp[i].left_upper_x = _pos_x - ROAD_SMALL_RANGE;
			_draw_road_pos_tmp[i].left_upper_y = _pos_y - ROAD_WIDE_RANGE;
			_draw_road_pos_tmp[i].right_lower_x = _pos_x + ROAD_SMALL_RANGE;
			_draw_road_pos_tmp[i].right_lower_y = _pos_y + ROAD_SMALL_RANGE;
			break;
		case BOTTOM:
			_draw_road_pos_tmp[i].left_upper_x = _pos_x - ROAD_SMALL_RANGE;
			_draw_road_pos_tmp[i].left_upper_y = _pos_y - ROAD_SMALL_RANGE;
			_draw_road_pos_tmp[i].right_lower_x = _pos_x + ROAD_SMALL_RANGE;
			_draw_road_pos_tmp[i].right_lower_y = _pos_y + ROAD_WIDE_RANGE;
			break;
		case LEFT:
			_draw_road_pos_tmp[i].left_upper_x = _pos_x - ROAD_WIDE_RANGE;
			_draw_road_pos_tmp[i].left_upper_y = _pos_y - ROAD_SMALL_RANGE;
			_draw_road_pos_tmp[i].right_lower_x = _pos_x + ROAD_SMALL_RANGE;
			_draw_road_pos_tmp[i].right_lower_y = _pos_y + ROAD_SMALL_RANGE;
			break;
		case RIGHT:
			_draw_road_pos_tmp[i].left_upper_x = _pos_x - ROAD_SMALL_RANGE;
			_draw_road_pos_tmp[i].left_upper_y = _pos_y - ROAD_SMALL_RANGE;
			_draw_road_pos_tmp[i].right_lower_x = _pos_x + ROAD_WIDE_RANGE;
			_draw_road_pos_tmp[i].right_lower_y = _pos_y + ROAD_SMALL_RANGE;
			break;
		}
	}

	setRoadDrawPos();
	setRoadDirection();
}

double Road::getBoxSize() {
	return BOX_SIZE;
}

double Road::getBoxHalfSize() {
	return BOX_HALF_SIZE;
}

void Road::drawRoad() {
	for (int i = 0; i < MAX_ROAD; i++) {
		DrawBox(_draw_road_pos[i].left_upper_x, _draw_road_pos[i].left_upper_y, _draw_road_pos[i].right_lower_x, _draw_road_pos[i].right_lower_y, _road_color, TRUE);
	}

}

void Road::setRoadDrawPos() {
	switch (_road_form) {
	case CORNER:
		switch (_road_rotate) {
		case 0:
			_draw_road_pos[0] = getDrawRoadPosTmp(TOP);		// 上
			_draw_road_pos[1] = getDrawRoadPosTmp(RIGHT);	// 右
			break;
		case 1:
			_draw_road_pos[0] = getDrawRoadPosTmp(RIGHT);	// 右
			_draw_road_pos[1] = getDrawRoadPosTmp(BOTTOM);	// 下
			break;
		case 2:
			_draw_road_pos[0] = getDrawRoadPosTmp(BOTTOM);	// 下
			_draw_road_pos[1] = getDrawRoadPosTmp(LEFT);	// 左
			break;
		case 3:
			_draw_road_pos[0] = getDrawRoadPosTmp(LEFT);	// 左
			_draw_road_pos[1] = getDrawRoadPosTmp(TOP);		// 上
			break;
		}
		break;
	case STRAIGHT_LINE:
		switch (_road_rotate) {
		case 0:
			_draw_road_pos[0] = getDrawRoadPosTmp(TOP);		// 上
			_draw_road_pos[1] = getDrawRoadPosTmp(BOTTOM);	// 下
			break;
		case 1:
			_draw_road_pos[0] = getDrawRoadPosTmp(RIGHT);	// 右
			_draw_road_pos[1] = getDrawRoadPosTmp(LEFT);	// 左
			break;
		case 2:
			_draw_road_pos[0] = getDrawRoadPosTmp(BOTTOM);	// 下
			_draw_road_pos[1] = getDrawRoadPosTmp(TOP);		// 上
			break;
		case 3:
			_draw_road_pos[0] = getDrawRoadPosTmp(LEFT);	// 左
			_draw_road_pos[1] = getDrawRoadPosTmp(RIGHT);	// 右
			break;
		}
	case SENTER_ROAD:
		break;
	}
}

Road::DrawBoxPos Road::getDrawRoadPosTmp(int road_rotate_state) {
	switch (road_rotate_state) {
	case TOP:
		return _draw_road_pos_tmp[TOP];
	case BOTTOM:
		return _draw_road_pos_tmp[BOTTOM];
	case LEFT:
		return _draw_road_pos_tmp[LEFT];
	case RIGHT:
		return _draw_road_pos_tmp[RIGHT];
	}
	return _draw_road_pos_tmp[TOP];
}

void Road::setHasPower(bool set_value) {
	_has_power = set_value;
	setRoadColor(_has_power);
}

bool Road::getHasPower() {
	return _has_power;
}

void Road::setRoadColor(bool has_power) {
	if (has_power) {
		_road_color = GetColor(255, 0, 0);
	}
	else {
		_road_color = GetColor(255, 255, 255);
	}
}

void Road::setCenterRoadFrameColor() {
	_frame_color = GetColor(255, 0, 0);
}

int Road::getForm() {
	return _road_form;
}

int Road::getRotate() {
	return _road_rotate;
}

void Road::setRoadDirection() {

	switch (_road_form) {
	case CORNER:
		switch (_road_rotate) {
		case 0:
			_road_direction[0] = 0;	// 上
			_road_direction[1] = 1;	// 右
			break;
		case 1:
			_road_direction[0] = 1;	// 右
			_road_direction[1] = 2;	// 下
			break;
		case 2:
			_road_direction[0] = 2;	// 下
			_road_direction[1] = 3;	// 左
			break;
		case 3:
			_road_direction[0] = 3;	// 左
			_road_direction[1] = 0;	// 上
			break;
		}
		break;
	case STRAIGHT_LINE:
		switch (_road_rotate) {
		case 0:
			_road_direction[0] = 0;	// 上
			_road_direction[1] = 2;	// 下
			break;
		case 1:
			_road_direction[0] = 1;	// 右
			_road_direction[1] = 3;	// 左
			break;
		case 2:
			_road_direction[0] = 2;	// 下
			_road_direction[1] = 0;	// 上
			break;
		case 3:
			_road_direction[0] = 3;	// 左
			_road_direction[1] = 1;	// 右
			break;
		}
	case SENTER_ROAD:
		break;
	}
}

int Road::getRoadDirection(int idx,int road_idx) {
	return _road_direction[idx];
}

void Road::setIsCenter() {
	_is_center = true;
}

bool Road::getIsControl() {
	return _is_control;
}

void Road::setIsControl(bool set_value) {
	_is_control = set_value;
}