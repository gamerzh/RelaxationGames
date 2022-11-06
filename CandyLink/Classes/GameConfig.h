#pragma once
#include "cocos2d.h"
USING_NS_CC;
struct SceneChange
{
	int style;
	float ChangeTime;
	bool state;
	SceneChange(int t, int c) :style(t), ChangeTime(c), state(0){};
	SceneChange(int t, int c, int s) :style(t), ChangeTime(c), state(s){};
	SceneChange(){};
};
class GameConfig
{
public:
	~GameConfig();
	static GameConfig* getInstance();
	bool LoadConfig();
	Scene* getSceneOfChangeStyleByName(Scene* scene,std::string SceneAtoSceneB);
private:
	GameConfig();
	static GameConfig* _instance;
	std::map<std::string,SceneChange>  m_SceneChange;
};

