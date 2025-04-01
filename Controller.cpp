#include "Controller.h"
#include "DxLib.h"

Controller::Controller() {
	for (int i = 0; i < MAX_GET_KEY; i++) {

		_key_state[i]._begin = false;
		_key_state[i]._now = false;
		_key_state[i]._old = false;
		_key_state[i]._release = false;
	}
}

Controller::~Controller() {

}

void Controller::update() {
	for (int i = 0; i < MAX_GET_KEY; i++) {

		if (getCheckHitKey(i)) {
			_key_state[i]._now = true;
		}
		else {
			_key_state[i]._now = false;
		}


		// 前フレームに押しているか
		if (_key_state[i]._old) {
			// 現フレームで押しているか
			if (_key_state[i]._now) {
				_key_state[i]._begin = false;
			}
			else {
				_key_state[i]._release = true;
			}
		}
		else {
			if (_key_state[i]._now) {
				_key_state[i]._begin = true;
			}
			_key_state[i]._release = false;
		}

		if (_key_state[i]._now) {
			_key_state[i]._old = true;
		}
		else {
			_key_state[i]._old = false;
		}

	}


}

bool Controller::getIsKeyRelease(int keycode) {
	return _key_state[keycode]._release;
}

bool Controller::getIsKeyBegin(int keycode) {
	return _key_state[keycode]._begin;
}

int Controller::getCheckHitKey(int keycode) {
	switch (keycode) {
	case ENTER:
		return CheckHitKey(KEY_INPUT_RETURN);
	case W:
		return CheckHitKey(KEY_INPUT_W);
	case A:
		return CheckHitKey(KEY_INPUT_A);
	case S:
		return CheckHitKey(KEY_INPUT_S);
	case D:
		return CheckHitKey(KEY_INPUT_D);
	case BACK_SPACE:
		return CheckHitKey(KEY_INPUT_BACK);
	}
}