#include "Scene.h"

Scene::Scene() {

	_change_scene_flag = false;
	_next_scene = Scene::SceneType::TITLE;
}

Scene::~Scene() {

}

bool Scene::getChangeSceneFlag() {

	return _change_scene_flag;
}

void Scene::setChangeSceneFlag(bool value) {

	_change_scene_flag = value;
}

Scene::SceneType Scene::getNextScene() {

	return _next_scene;
}

void Scene::setNextScene(Scene::SceneType next_scene) {

	_next_scene = next_scene;
}