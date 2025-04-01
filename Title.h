#pragma once
#include "Scene.h"
class Title : public Scene
{
public:
	Title();

	~Title();

	virtual void update()override;

	virtual void draw()override;

private:
	
};

