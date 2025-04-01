#include "Game.h"
#include "DxLib.h"
#include "Road.h"
#include "Controller.h"
#include <string>

extern Controller* _controller;

Game::Game() {

	setNextScene(Scene::SceneType::TITLE);
	setChangeSceneFlag(false);

	_plus_time_count = 0;
	_time = 150;
	_end_game = false;
	_control_road_index = START_CONTROL_ROAD;
	_result_time = 0;

	for (int idx = 0; idx < CLEAR_STATE_NUM; idx++) {

		_is_clear[idx] = false;
	}

	for (int i = 0; i < MAX_ROAD_OBJ; i++) {

		if (i == ROAD_CENTER_INDEX) {
			_road_obj[i] = new Road(2);
			_road_obj[i]->setHasPower(true);
			_road_obj[i]->setIsCenter();
		}
		else {
			_road_obj[i] = new Road(GetRand(1));
		}

		double box_size = _road_obj[i]->getBoxSize();
		double box_half_size = _road_obj[i]->getBoxHalfSize();
		int row = i / ROAD_COLUMON_NUM;
		int column = i - row * ROAD_COLUMON_NUM;
		double road_obj_x = ROAD_GROUP_LEFT_END_POS + box_half_size + box_size * column;
		double road_obj_y = ROAD_GROUP_TOP_EDGE_POS + box_half_size + box_size * row;

		_road_obj[i]->create(road_obj_x, road_obj_y);


	}

	for (int idx = 0; idx < MAX_SENTER_EVERY_DIRECTION_ROAD_OBJ; idx++) {

		_senter_every_direction_road_obj_idx[idx] = 0;

		switch (idx) {
		case 0:
			_senter_every_direction_road_obj_idx[idx] = ROAD_CENTER_INDEX - ROAD_ROW_NUM;
			break;
		case 1:
			_senter_every_direction_road_obj_idx[idx] = ROAD_CENTER_INDEX + 1;
			break;
		case 2:
			_senter_every_direction_road_obj_idx[idx] = ROAD_CENTER_INDEX + ROAD_ROW_NUM;
			break;
		case 3:
			_senter_every_direction_road_obj_idx[idx] = ROAD_CENTER_INDEX - 1;
			break;
		}
	}
}

Game::~Game() {
	for (int idx = 0; idx < MAX_ROAD_OBJ; idx++) {
		delete _road_obj[idx];
		_road_obj[idx] = nullptr;
	}
}

void Game::update() {

	if (!_end_game) {

		_plus_time_count++;
		if (_plus_time_count == MAX_FRAME) {
			_time--;
			_plus_time_count = 0;
		}

		if (_time == 0) {
			_end_game = true;
		}

		if (_controller->getIsKeyBegin(Controller::W)) {
			_control_road_index -= ROAD_COLUMON_NUM;
			if (_control_road_index < 0) {
				_control_road_index += MAX_ROAD_OBJ;
			}
		}
		if (_controller->getIsKeyBegin(Controller::S)) {
			_control_road_index += ROAD_COLUMON_NUM;
			if (_control_road_index >= MAX_ROAD_OBJ) {
				_control_road_index -= MAX_ROAD_OBJ;
			}
		}
		if (_controller->getIsKeyBegin(Controller::A)) {
			_control_road_index--;
			if (_control_road_index < 0) {
				_control_road_index = ROAD_LAST_INDEX;
			}
		}
		if (_controller->getIsKeyBegin(Controller::D)) {
			_control_road_index++;
			if (_control_road_index >= MAX_ROAD_OBJ) {
				_control_road_index = 0;
			}
		}

		for (int idx = 0; idx < CLEAR_STATE_NUM; idx++) {
			_is_clear[idx] = false;
		}

		for (int idx = 0; idx < MAX_ROAD_OBJ; idx++) {

			bool can_control = false;

			if (_control_road_index == idx) {

				can_control = true;

			}
			_road_obj[idx]->update(can_control);

			if (idx == ROAD_CENTER_INDEX) {
				continue;
			}

			// �ꎟ�I�B���삵����ɂ������B�Z���^�[�������O�B
			_road_obj[idx]->setHasPower(false);

		}

	}
	else {

		if (_result_time > CAN_INPUT_DISTANCE_TIME) {
			if (_controller->getIsKeyRelease(Controller::ENTER)) {
				setChangeSceneFlag(true);
			}
		}
		else {
			_result_time++;
		}
	}

	// �p���[�������Ȃ����Ă��邩
	for (int idx = 0; idx < MAX_SENTER_EVERY_DIRECTION_ROAD_OBJ; idx++) {

		int check_road_obj_idx = _senter_every_direction_road_obj_idx[idx];
		int unchecked_direction = 0;
		bool has_power = false;

		// ���S���猩�ď㉺���E�ǂ̃��[�h��
		switch (idx) {
		case UPPER:
			for (int direction_idx = 0; direction_idx < Road::MAX_ROAD; direction_idx++) {

				int direction = _road_obj[check_road_obj_idx]->getRoadDirection(direction_idx, check_road_obj_idx);
				// ��̃��[�h�ɉ������̓������邩
				if (direction == LOWER) {
					_road_obj[check_road_obj_idx]->setHasPower(true);
				}
				else {
					unchecked_direction = direction;
				}
			}

			// �p���[����������
			has_power = _road_obj[check_road_obj_idx]->getHasPower();
			if (has_power) {
				powerConnect(check_road_obj_idx, unchecked_direction);
				break;
			}

			break;

		case RIGHT:
			for (int direction_idx = 0; direction_idx < Road::MAX_ROAD; direction_idx++) {

				int direction = _road_obj[check_road_obj_idx]->getRoadDirection(direction_idx, check_road_obj_idx);
				// �E�̃��[�h�ɍ������̓������邩
				if (direction == LEFT) {
					_road_obj[check_road_obj_idx]->setHasPower(true);
				}
				else {
					unchecked_direction = direction;
				}
			}

			// �p���[����������
			has_power = _road_obj[check_road_obj_idx]->getHasPower();
			if (has_power) {
				powerConnect(check_road_obj_idx, unchecked_direction);
				break;
			}

			break;

		case LOWER:
			for (int direction_idx = 0; direction_idx < Road::MAX_ROAD; direction_idx++) {

				int direction = _road_obj[check_road_obj_idx]->getRoadDirection(direction_idx, check_road_obj_idx);
				// ���̃��[�h�ɏ�����̓������邩
				if (direction == UPPER) {
					_road_obj[check_road_obj_idx]->setHasPower(true);
				}
				else {
					unchecked_direction = direction;
				}
			}

			// �p���[����������
			has_power = _road_obj[check_road_obj_idx]->getHasPower();
			if (has_power) {
				powerConnect(check_road_obj_idx, unchecked_direction);
				break;
			}

			break;

		case LEFT:
			for (int direction_idx = 0; direction_idx < Road::MAX_ROAD; direction_idx++) {

				int direction = _road_obj[check_road_obj_idx]->getRoadDirection(direction_idx, check_road_obj_idx);
				// ���̃��[�h�ɉE�����̓������邩
				if (direction == RIGHT) {
					_road_obj[check_road_obj_idx]->setHasPower(true);
				}
				else {
					unchecked_direction = direction;
				}
			}

			// �p���[����������
			has_power = _road_obj[check_road_obj_idx]->getHasPower();
			if (has_power) {
				powerConnect(check_road_obj_idx, unchecked_direction);
				break;
			}

			break;

		}
	}

	if (!_end_game) {
		for (int idx = 0; idx < CLEAR_STATE_NUM; idx++) {

			if (!_is_clear[idx]) {
				return;
			}
		}

		_end_game = true;
	}

}

void Game::draw() {

	// �f�o�b�O�p
	//DrawString(50, 50, "Game", GetColor(0, 255, 0), TRUE);
	//drawControlRoadParameter(_control_road_index);

	std::string time_str = std::to_string(_time);

	SetFontSize(48);
	DrawString(800, 80, time_str.c_str(), GetColor(255, 255, 255), TRUE);
	SetFontSize(24);

	if (!_end_game) {
		for (int i = 0; i < MAX_ROAD_OBJ; i++) {
			_road_obj[i]->draw();
		}
		DrawString(275, 30, "���ԓ���4�{�̐����O���ɐڑ�����I�I", GetColor(0, 255, 0),TRUE);
		DrawString(50, 400, "WASD : �ړ�", GetColor(255, 255, 255), TRUE);
		DrawString(50, 420, "Enter : �E�ɉ�]", GetColor(255, 255, 255), TRUE);
	}
	else {
		if (_time == 0) {
			DrawString(425, 270, "GAME OVER", GetColor(255, 0, 0), TRUE);
			
		}
		else {
			DrawString(420, 270, "GAME CLEAR", GetColor(255, 255, 255), TRUE);
		}
		DrawString(425, 320, "Enter�L�[�Ŗ߂�", GetColor(255, 255, 255), TRUE);
	}
}

// �Ȃ����Ă��郍�[�h�𔻒肷��B�ċN�֐��B
void Game::powerConnect(int road_idx, int check_direction) {

	// ���g�̗v�f��
	int check_road_idx = getCheckRoadIdx(road_idx, check_direction);
	// �����Ă�����p���[�������Ƃ��ł������
	int has_power_condition_road_direction = getCheckRoadDirection(check_direction);
	// �p���[���������̕����ƈႤ������ۑ��B�p���[�����Ă���g��Ȃ��B
	int unchecked_direction = 0;
	// �p���[�𓾂Ă��邩
	bool has_power = false;

	//���S��������I���
	if (check_road_idx == ROAD_CENTER_INDEX) {
		return;
	}

	if (checkEnd(road_idx, check_road_idx)) {
		for (int idx = 0; idx < CLEAR_STATE_NUM; idx++) {
			if (!_is_clear[idx]) {
				_is_clear[idx] = true;
				break;
			}
		}
		return;
	}
	if (check_road_idx >= MAX_ROAD_OBJ) {
		return;
	}
	for (int direction_idx = 0; direction_idx < Road::MAX_ROAD; direction_idx++) {

		// ���g�̌����Ă������
		int check_direction = _road_obj[check_road_idx]->getRoadDirection(direction_idx, check_road_idx);
		if (has_power_condition_road_direction == check_direction) {

			_road_obj[check_road_idx]->setHasPower(true);
			has_power = true;
		}
		else {

			unchecked_direction = check_direction;
		}
	}
	if (has_power) {
		powerConnect(check_road_idx, unchecked_direction);
		return;
	}
	else {
		return;
	}
}

void Game::drawControlRoadParameter(int road_index) {

	unsigned int str_color = GetColor(255, 255, 255);

	char idx_str[256];
	sprintf_s(idx_str, sizeof(idx_str), "%d", road_index);

	char has_power_str[256];
	bool has_power = _road_obj[road_index]->getHasPower();
	sprintf_s(has_power_str, "%s", has_power ? "true" : "false");

	char direction1_str[256];
	int direction1 = _road_obj[road_index]->getRoadDirection(0, road_index);
	sprintf_s(direction1_str, "%d", direction1);

	char direction2_str[256];
	int direction2 = _road_obj[road_index]->getRoadDirection(1, road_index);
	sprintf_s(direction2_str, "%d", direction2);


	/*DrawString(900, 50, idx_str, str_color, TRUE);
	DrawString(900, 70, has_power_str, str_color, TRUE);
	DrawString(900, 90, direction1_str, str_color, TRUE);
	DrawString(900, 110, direction2_str, str_color, TRUE);*/

}

// powerConnect()�Ŏg��
int Game::getCheckRoadIdx(int road_idx, int check_direction) {

	switch (check_direction) {
	case UPPER:
		return road_idx - ROAD_ROW_NUM;
	case RIGHT:
		return road_idx + 1;
	case LOWER:
		return road_idx + ROAD_ROW_NUM;
	case LEFT:
		return road_idx - 1;
	}
	return 0;
}

// powerConnect()�Ŏg��
int Game::getCheckRoadDirection(int check_direction) {

	switch (check_direction) {
	case UPPER:
		return LOWER;
	case RIGHT:
		return LEFT;
	case LOWER:
		return UPPER;
	case LEFT:
		return RIGHT;
	}
	return 0;
}

// powerConnect()�Ŏg���B�N���A����B
bool Game::checkEnd(int road_idx/*�p���[�𒼑O�Ɏ󂯂����[�h*/, int check_road_idx/*�p���[�𓾂����[�h�̕����̐�̃��[�h*/) {

	// �㉺�̒[�O�Ƀp���[���Ȃ��Ă��邩
	if (check_road_idx >= MAX_ROAD_OBJ || 0 > check_road_idx) {
		return true;
	}

	// �E�[�O�Ƀp���[���Ȃ��Ă��邩
	if (road_idx % ROAD_ROW_NUM == 14) {
		if (check_road_idx == road_idx + 1) {
			return true;
		}
	}

	// ���[�O�Ƀp���[���Ȃ��Ă��邩
	if (road_idx % ROAD_ROW_NUM == 0) {
		if (check_road_idx == road_idx - 1) {
			return true;
		}
	}

	return false;

}

//void Game::drawString(std::string str) {
//
//}