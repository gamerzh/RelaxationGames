#pragma once
#include "cocos2d.h"
#include "domain/mermaid/MermaidTask.h"
USING_NS_CC;
class maridTaskPlane : public Sprite
{
public:
	CREATE_FUNC(maridTaskPlane);
private:
	virtual bool init();
	void update(float delta);
	float nNowtime = 0;
	LabelTTF* labelNum;
};

