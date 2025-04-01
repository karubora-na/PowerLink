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

	// �f�o�b�O�p
	//DrawString(50, 50, "Title", GetColor(0, 255, 0), TRUE);

	SetFontSize(80);
	DrawString(280, 170, "Power Link", GetColor(255, 0, 0), TRUE);
	SetFontSize(24);
	DrawString(275, 270, "���ԓ���4�{�̐����O���ɐڑ�����I�I", GetColor(0, 255, 0), TRUE);
	DrawString(365, 360, "Enter�L�[�ŃX�^�[�g", GetColor(255, 255, 255), TRUE);
	DrawString(50, 400, "WASD : �ړ�", GetColor(255, 255, 255), TRUE);
	DrawString(50, 420, "Enter : �E�ɉ�]", GetColor(255, 255, 255), TRUE);
}