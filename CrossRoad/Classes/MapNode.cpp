#include "MapNode.h"

MapNode* MapNode::create(MapNodeType type) {
	auto mapnode = new MapNode();
	if (mapnode && mapnode->init(type)) {
		mapnode->autorelease();
		return mapnode;
	}
	else {
		CC_SAFE_DELETE(mapnode);
		return NULL;
	}
}

bool MapNode::init(MapNodeType type) {
	if (!Node::init()) {
		return false;
	}
	setMapNodeType(type);
	_tileMap = CCTMXTiledMap::create(getFileNameByType(type));
	_tileMap->setPosition(0, 0);
	addChild(_tileMap);
	Vector<Node*> nodeVector= _tileMap->getChildren();
	for (auto var : nodeVector) {
		if (NULL != var) {
			((SpriteBatchNode*)var)->getTexture()->setAntiAliasTexParameters();
		}
	}
	//background = _tileMap->layerNamed("main");
	block = _tileMap->layerNamed("water");
	setContentSize(_tileMap->getContentSize());
	return true;
}

int MapNode::getTMXPerGradutaionLength() {
	return default_tmx_width;
}

string  MapNode::getFileNameByType(MapNodeType type) {
	switch (type)
	{

	case MapNodeType::type1:
		return "001.tmx";
	case MapNodeType::type2:
		return "001.tmx";
	case MapNodeType::type3:
		return "001.tmx";
	default:
		return "001.tmx";
	}
}

TMXLayer* MapNode::getTMXBackground() {
	if (NULL != background) {
		return background;
	}
	else {
		return NULL;
	}
}


TMXLayer* MapNode::getTMXWater() {
	if (NULL != block) {
		return block;
	}
	else {
		return NULL;
	}
}

Point MapNode::getHeroStartPos() {
	//TMXObjectGroup *objects = _tileMap->getObjectGroup("player");//获取对象层  
	//ValueMap  playerPoint = objects->getObject("hero");//获取对象 
	//return (Vec2(playerPoint["x"].asFloat(), playerPoint["y"].asFloat()));
	return Vec2(default_tmx_width*9, 0);
}


vector<TMCarInfo> MapNode::getEnemyInfoList() {
	vector<TMCarInfo> tmCarList;
	TMXObjectGroup *objects = _tileMap->getObjectGroup("car");
	ValueVector nodes = objects->getObjects();//获取对象列表
	for (auto var : nodes) {
		ValueMap tm = var.asValueMap();
		TMCarInfo info;
		info.type = tm["type"].asInt();
		info.direction = tm["direction"].asInt();
		info.interval = tm["interval"].asFloat();
		info.speed = tm["speed"].asFloat();
		info.position = Vec2(tm["x"].asFloat(), tm["y"].asFloat());
		tmCarList.push_back(info);
	}
	
	return tmCarList;
}

vector<TMBlockInfo> MapNode::getBlockInfoList() {
	vector<TMBlockInfo> pointList;
	TMXObjectGroup *objects = _tileMap->getObjectGroup("tree");
	ValueVector nodes = objects->getObjects();//获取对象列表
	for (auto var : nodes) {
		TMBlockInfo info;
		ValueMap tmin = var.asValueMap();
		info.position = Vec2(tmin["x"].asFloat(), tmin["y"].asFloat());
		//log("Tree x = %f,y = %f",info.position.x,info.position.y);
		info.type = 1;
		info.width = tmin["width"].asFloat();
		info.height = tmin["height"].asFloat();
		pointList.push_back(info);
	}
	return pointList;
}

vector<TMWoodInfo> MapNode::getWoodInfoList() {
	vector<TMWoodInfo> pointList;
	TMXObjectGroup *objects = _tileMap->getObjectGroup("block");
	ValueVector nodes = objects->getObjects();//获取对象列表
	for (auto var : nodes) {
		TMWoodInfo info;
		ValueMap tmin = var.asValueMap();
		info.position = Vec2(tmin["x"].asFloat(), tmin["y"].asFloat());
		info.type = 1;
		//info.width = tmin["width"].asFloat();
		//info.height = tmin["height"].asFloat();
		pointList.push_back(info);
	}
	return pointList;
}