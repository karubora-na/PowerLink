#include "Title.h"
#include "DxLib.h"
#include "Controller.h"

extern Controller* _controller;

Title::Title() {

	setNextScene(Scene::SceneType::GAME);
	setChangeSceneFlag(false);
}

Title::~Title() {

}

void Title::update() {

	if (_controller->getIsKeyRelease(Controller::ENTER)) {
		setChangeSceneFlag(true);
	}


}

void Title::draw() {

	// デバッグ用
	//DrawString(50, 50, "Title", GetColor(0, 255, 0), TRUE);

	SetFontSize(80);
	DrawString(280, 170, "Power Link", GetColor(255, 0, 0), TRUE);
	SetFontSize(24);
	DrawString(275, 270, "時間内に4本の線を外周に接続しろ！！", GetColor(0, 255, 0), TRUE);
	DrawString(365, 360, "Enterキーでスタート", GetColor(255, 255, 255), TRUE);
	DrawString(50, 400, "WASD : 移動", GetColor(255, 255, 255), TRUE);
	DrawString(50, 420, "Enter : 右に回転", GetColor(255, 255, 255), TRUE);
}