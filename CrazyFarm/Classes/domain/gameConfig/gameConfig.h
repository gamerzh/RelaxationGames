#pragma once
#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
using namespace cocos2d;

struct ShootData
{
	float shootInterval;
	int shootSpeed;
};


class GameConfig {

public:
	static GameConfig* getInstance();
	bool loadConfig();
	void loadConfigFromServer();
	void onHttpRequestCompletedForLoadConfig(HttpClient *sender, HttpResponse *response);
private:
	void WriteConfigToLocal();
	GameConfig();
	static GameConfig* _instance;
	//�ӵ�������
	CC_SYNTHESIZE(ShootData, shootData, ShootData);
	//��Ĳ������ϵ��
	CC_SYNTHESIZE(float, catch_fish_per_coef, catchFishPerCoef);
	//�汾��
	int configVersion;
};


