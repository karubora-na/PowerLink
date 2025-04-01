#pragma once
class Scene
{
public:

	enum class SceneType {
		TITLE,
		GAME
	};

private:

	bool _change_scene_flag;

	SceneType _next_scene;

public:
	Scene();

	~Scene();

	virtual void update() = 0;

	virtual void draw() = 0;

	bool getChangeSceneFlag();

	SceneType getNextScene();

protected:

	void setNextScene(Scene::SceneType next_scene);

	void setChangeSceneFlag(bool value);
};

