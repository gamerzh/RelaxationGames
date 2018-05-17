#include "MapNode.h"



MapNode* MapNode::create(int type) {
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

bool MapNode::init(int type) {
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
	setContentSize(_tileMap->getContentSize());
	return true;
}

int MapNode::getTMXPerGradutaionLength() {
	return default_tmx_width;
}

string  MapNode::getFileNameByType(int type) {
	return  String::createWithFormat("game_%d.tmx", type)->_string;
}


Point MapNode::getHeroStartPos() {
	TMXObjectGroup *objects = _tileMap->getObjectGroup("man");
	ValueMap objMap = objects->getObject("");
	float x = objMap["x"].asFloat();
	float y = objMap["y"].asFloat();
	return Vec2(x, y);
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
		info.width = tmin["width"].asFloat();
		info.height = tmin["height"].asFloat();
		info.type = tmin["type"].asInt();
		pointList.push_back(info);
	}
	return pointList;
}

vector<TMWoodInfo> MapNode::getWoodInfoList() {
	vector<TMWoodInfo> woodList;
	TMXObjectGroup *objects = _tileMap->getObjectGroup("items");
	ValueVector nodes = objects->getObjects();//获取对象列表
	for (auto var : nodes) {
		TMWoodInfo info;
		ValueMap tmin = var.asValueMap();
		info.type = tmin["type"].asInt();
		info.position = Vec2(tmin["x"].asFloat(), tmin["y"].asFloat());
		if (tmin["type"].asInt() == ObjectType::wood_short || tmin["type"].asInt() == ObjectType::wood_long || tmin["type"].asInt() == ObjectType::leaf) {
			if (tmin["type"].asInt() == ObjectType::leaf) {
				info.direction = 0;
				info.time = 0;
			}
			else
			{
				info.direction = tmin["direction"].asInt();
				info.time = tmin["time"].asFloat();
			}
			woodList.push_back(info);
		}
	}
	return woodList;
}


vector<TMGoldInfo> MapNode::getGoldInfoList() {
	vector<TMGoldInfo> goldList;
	TMXObjectGroup *objects = _tileMap->getObjectGroup("items");
	ValueVector nodes = objects->getObjects();//获取对象列表
	for (auto var : nodes) {
		TMGoldInfo info;
		ValueMap tmin = var.asValueMap();
		if (tmin["type"].asInt() == ObjectType::gold ) {
			info.pos = Vec2(tmin["x"].asFloat(), tmin["y"].asFloat());
			goldList.push_back(info);
		}
	}
	return goldList;
}

vector<TMLightInfo> MapNode::getLightInfoList() {
	vector<TMLightInfo> lightList;
	TMXObjectGroup *objects = _tileMap->getObjectGroup("items");
	ValueVector nodes = objects->getObjects();//获取对象列表
	for (auto var : nodes) {
		TMLightInfo info;
		ValueMap tmin = var.asValueMap();
		if ( tmin["type"].asInt() == ObjectType::light) {
			info.pos = Vec2(tmin["x"].asFloat(), tmin["y"].asFloat());
			lightList.push_back(info);
		}
	}
	return lightList;
}


//返回水面在地图上的逻辑行数
vector<int> MapNode::getWaterLineNumber() {
	vector<int> waterList;
	TMXObjectGroup *objects = _tileMap->getObjectGroup("items");
	ValueVector nodes = objects->getObjects();//获取对象列表
	for (auto var : nodes) {
		TMGoldInfo info;
		ValueMap tmin = var.asValueMap();
		if (tmin["type"].asInt() == ObjectType::water) {
			float line = floor(tmin["y"].asFloat()/default_tmx_height)+floor(getPositionY() / default_tmx_height);
			waterList.push_back(line);
		}
	}
	return waterList;
}


bool MapNode::getPrepareToRecycle() {
	return prepareToRecycle;
}


void MapNode::setPrepareToRecycle(bool pre) {
	this->prepareToRecycle = pre;
}