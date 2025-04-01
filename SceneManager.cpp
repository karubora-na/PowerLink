#include "SceneManager.h"
#include "Scene.h"
#include "Title.h"
#include "Game.h"

SceneManager::SceneManager() {
	_scene = new Title;
}

SceneManager::~SceneManager() {
	delete _scene;
	_scene = nullptr;
}

void SceneManager::update() {
	_scene->update();
	_scene->draw();

	if (_scene->getChangeSceneFlag()) {
		changeScene(_scene->getNextScene());
	}
}

void SceneManager::changeScene(Scene::SceneType next_scene) {

	delete _scene;

	switch (next_scene) {
	case Scene::SceneType::TITLE:
		_scene = new Title;
		break;
	case Scene::SceneType::GAME:
		_scene = new Game;
		break;
	}
}