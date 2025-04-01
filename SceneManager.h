#pragma once

#include "Scene.h"

class SceneManager
{
public:
	SceneManager();

	~SceneManager();

	void update();

private:
	void changeScene(Scene::SceneType next_scene);

private:

	Scene* _scene;


};

