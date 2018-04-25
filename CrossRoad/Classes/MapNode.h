#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

//��ͼģ��,���ݿ����滻

enum MapNodeType
{
	type1,
	type2,
	type3
};

class MapNode : public Node {
 
public:
	static MapNode* create(MapNodeType type);
	virtual bool init(MapNodeType type);
	CC_SYNTHESIZE(MapNodeType, mapNodeType, MapNodeType);
private:
	string  getFileNameByType(MapNodeType type);
	void update(float dt);
	vector<Sprite*> dangerList;
 
};