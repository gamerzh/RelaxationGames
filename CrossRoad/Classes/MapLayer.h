#pragma once
#include "cocos2d.h"
#include "MapNode.h"
USING_NS_CC;

class MapLayer : public Layer {
public:
	static MapLayer* create(Camera* ca);
	virtual bool init(Camera* ca);
	vector<MapNode*> getMapNodes();
private:
	vector<MapNode*> mapList;
	void createMap();
	void checkMapInScene(float dt);
//    void createDangousObject(MapNode* var);
	Camera* _camera;
	int removeNodeNum = 0;
    void update(float dt);
};
