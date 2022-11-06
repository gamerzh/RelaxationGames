#pragma once
#include "cocos2d.h"
#include "utill/OBB.h"
#include "fish/Fish.h"
#include "bullet/Bullet.h"
#include "net/Net.h"
USING_NS_CC;


class CollisionUtill
{
public:
	//common
	static bool isCollisionFishAAndBullet(Fish*fish,Bullet*bullet);
	static bool isCollisionFishAAndNet(Fish*fish, Net*net);
	static bool isCollisionFishAAndPos(Fish*fish, Vec2 pos);
	static bool isCollisionFishAAndRect(Fish*fish, Rect rect);


private:
	//OBB
	static bool isCollisionOBB1AndOBB2(OBBEX obb1, OBBEX obb2);
	static bool isCollisionOBBsAndOBB(std::vector<OBBEX> obbs, OBBEX obb);
	static bool isCollisionOBBsAndOBBs(std::vector<OBBEX> obbs1, std::vector<OBBEX> obbs2);
	static bool isCollisionOBBsAndPoint(std::vector<OBBEX> obbs1, Vec2 pos);
	static bool isCollisionOBBsAndRect(std::vector<OBBEX> obbs1, Rect rect);


	//AABB
	
	static bool isCollisionRectAsAndRectB(std::vector<Rect> rectAs, Rect rectB);
	static bool isCollisionRectAsAndPos(std::vector<Rect> rectAs, Vec2 pos);
public:
	static bool isCollisionNodeAAndRect(Node*nodeA, Rect rect);
};


