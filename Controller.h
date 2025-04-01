#pragma once

// ‘½•ªŽg‚í‚È‚¢

class Controller
{
public:

	enum Key {
		ENTER,
		W,
		A,
		S,
		D,
		BACK_SPACE
	};

private:

	struct InputKeyState {
		bool _old;
		bool _now;
		bool _begin;
		bool _release;
	};

public:

	Controller();
	~Controller();

	void update();

	bool getIsKeyRelease(int keycode);
	bool getIsKeyBegin(int keycode);
private:

	int getCheckHitKey(int keycode);

private:

	static const int MAX_GET_KEY = 5;

	InputKeyState _key_state[MAX_GET_KEY];
};

