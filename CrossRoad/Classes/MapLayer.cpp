#include "MapLayer.h"


MapLayer* MapLayer::create(Camera* ca) {
	auto mapLayer = new MapLayer();
	if (mapLayer && mapLayer->init(ca)) {
		mapLayer->autorelease();
		return mapLayer;
	}
	else {
		CC_SAFE_DELETE(mapLayer);
		return NULL;
	}
}

bool MapLayer::init(Camera* ca) {
	if (!Layer::init()) {
		return false;
	}
	_camera = ca;
	for (int i = 0; i< 6; i++) {
		createMap();
	}
	schedule(schedule_selector(MapLayer::checkMapInScene), 0.1f);
	return true;
}

void MapLayer::createMap() {
	Size win = Director::getInstance()->getWinSize();
	//生成安全区
	auto node1 = MapNode::create(MapNodeType::type2);
	if (mapList.size() == 0) {
		node1->setPosition(Vec2(0, 0));
	}
	else {
		//auto no = *(mapList.end());
		//vector<MapNode*>::iterator it;
		node1->setPosition(Vec2(0, mapList.at(mapList.size()-1)->getPositionY()+ mapList.at(mapList.size() - 1)->getContentSize().height));
		//log("GGGGGGG %f", mapList.at(mapList.size() - 1)->getPositionY());
	}
	node1->setCameraMask(2);
	addChild(node1); 
	mapList.push_back(node1);
	//生成危险区
	auto node2 = MapNode::create(MapNodeType::type1);
	node2->setPosition(Vec2(0, node1->getPositionY()+node1->getContentSize().height));
	node2->setCameraMask(2);
	addChild(node2);
	mapList.push_back(node2);
}

void MapLayer::checkMapInScene(float dt) {
	if (mapList.size() == 0) {
		return;
	}

	vector<MapNode*>::iterator it;
	for (it = mapList.begin(); it != mapList.end(); it++)
	{
		auto node = *it;
		if (_camera->getPositionY()  > node->getPositionY()+ node->getContentSize().height) {
			it = mapList.erase(it);
			node->removeFromParent();
			removeNodeNum++;
		}
	}

	if (removeNodeNum == 2) {
		auto test = Sprite::create("player_1.png");
		createMap();
		removeNodeNum = 0;
	}
}

vector<MapNode*> MapLayer::getMapNodes() {
	return mapList;
}

void MapLayer::createDangousObject() {
	for (auto var : mapList) {
		if (var->getMapNodeType() == MapNodeType::type2) {
			auto car = Sprite::create();
			car->setPosition(0,var->getPositionY());
			addChild(car);
		}
	}
}