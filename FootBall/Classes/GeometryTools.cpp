#include "GeometryTools.h"
USING_NS_CC;

DrawNode* GeometryTools::drawCollisionBox(Rect rect) {
	//log("Rect Point(%f,%f,%f,%f)",
	//	rect.getMinX(),
	//	rect.getMinY(),
	//	rect.getMaxX(),
	//	rect.getMaxY());
	DrawNode* drawNode = DrawNode::create();
	Vec2 point[4];
	point[0] = Vec2(rect.getMinX(), rect.getMinY());
	point[1] = Vec2(rect.getMaxX(), rect.getMinY());
	point[2] = Vec2(rect.getMaxX(), rect.getMaxY());
	point[3] = Vec2(rect.getMinX(), rect.getMaxY());

	//drawNode->drawRect(point[0], point[1], point[2], point[3], Color4F(1, 0, 0, 1));
	drawNode->drawPolygon(point, 4, Color4F(1, 0, 0, 1), 1, Color4F(0, 1, 0, 1));
	return drawNode;
}

DrawNode* GeometryTools::drawCollisionCircle(cocos2d::Vec2 point, float radius) {
	float scaleX = 1.0;
	float scaleY = 0.6;
	DrawNode* drawNode = DrawNode::create();
	drawNode->drawCircle(Vec2(point.x/ scaleX, point.y/scaleY), radius, 360, 10 ,false, Color4F(1, 0, 0, 1));
	drawNode->setScale(scaleX, scaleY);
	return drawNode;
}

float GeometryTools::calculateDistance(cocos2d::Vec2 p1, cocos2d::Vec2 p2){
    return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}
