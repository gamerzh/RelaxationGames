#include "utill/CollisionUtill.h"
#define IsArrangeFish fish->getFishID()>=101&&fish->getFishID()<=104
#define RECTSCALE 0.7

bool CollisionUtill::isCollisionFishAAndBullet(Fish*fish, Bullet*bullet)
{
	if (IsArrangeFish)
	{
		return CollisionUtill::isCollisionOBBsAndOBBs(fish->getOBBs(), bullet->getObbs());
	}
	else
	{
		return CollisionUtill::isCollisionRectAsAndRectB(fish->getAABBBoxs(), bullet->getBoundingBox());
		/*if (CollisionUtill::isCollisionRectAsAndRectB(fish->getAABBBoxs(), bullet->getBoundingBox()))
		{
		return CollisionUtill::isCollisionOBBsAndOBBs(fish->getOBBs(), bullet->getObbs());
		}
		else
		{
		return false;
		}*/
		
	}
}
bool CollisionUtill::isCollisionFishAAndNet(Fish*fish, Net*net)
{
	if (IsArrangeFish)
	{
		return CollisionUtill::isCollisionOBBsAndOBBs(fish->getOBBs(), net->getObbs());
	}
	else
	{
		return CollisionUtill::isCollisionRectAsAndRectB(fish->getAABBBoxs(), net->getBoundingBox());
	}
}
bool CollisionUtill::isCollisionFishAAndPos(Fish*fish, Vec2 pos)
{
	if (IsArrangeFish)
	{
		return CollisionUtill::isCollisionOBBsAndPoint(fish->getOBBs(), pos);
	}
	else
	{
		return CollisionUtill::isCollisionRectAsAndPos(fish->getAABBBoxs(), pos);
	}
}
bool CollisionUtill::isCollisionFishAAndRect(Fish*fish, Rect rect)
{
	if (IsArrangeFish)
	{
		return CollisionUtill::isCollisionOBBsAndRect(fish->getOBBs(), rect);
	}
	else
	{
		return CollisionUtill::isCollisionRectAsAndRectB(fish->getAABBBoxs(), rect);
	}

}












//OBB
bool CollisionUtill::isCollisionOBB1AndOBB2(OBBEX obb1, OBBEX obb2)
{
	return obb1.isCollidWithOBB(obb2);
}

bool CollisionUtill::isCollisionOBBsAndOBB(std::vector<OBBEX> obbs, OBBEX obb)
{
	bool isconllision = false;
	for (auto var : obbs)
	{
		if (var.isCollidWithOBB(obb))
		{
			isconllision = true;
			break;
		}
	}
	return isconllision;
}

bool CollisionUtill::isCollisionOBBsAndOBBs(std::vector<OBBEX> obbs1, std::vector<OBBEX> obbs2)
{
	bool isconllision = false;
	for (auto var1 : obbs1)
	{
		if (isconllision)
		{
			break;
		}
		for (auto var2 : obbs2)
		{
			if (var1.isCollidWithOBB(var2))
			{
				isconllision = true;
				break;
			}
		}
	}
	return isconllision;

}

bool CollisionUtill::isCollisionOBBsAndPoint(std::vector<OBBEX> obbs1, Vec2 pos)
{
	bool isconllision = false;
	for (auto var1 : obbs1)
	{
		if (var1.isCollidWithPoint(pos))
		{
			isconllision = true;
			break;
		}
	}
	return isconllision;
}

bool CollisionUtill::isCollisionOBBsAndRect(std::vector<OBBEX> obbs1, Rect rect)
{
	for (auto var1 : obbs1)
	{
		if (var1.isCollidWithOBB(OBBEX(Vec2(rect.getMinX(), rect.getMinY()), Vec2(rect.getMaxX(), rect.getMinY()), Vec2(rect.getMaxX(), rect.getMaxX()), Vec2(rect.getMinX(), rect.getMaxX()))))
		{
			return true;
		}
	}
	return false;
}








//AABB
bool CollisionUtill::isCollisionNodeAAndRect(Node*nodeA, Rect rect)
{
	return nodeA->getBoundingBox().intersectsRect(rect);
}

bool CollisionUtill::isCollisionRectAsAndRectB(std::vector<Rect> rectAs, Rect rectB)
{
	rectB.setRect(rectB.origin.x + rectB.size.width*(0.5 - RECTSCALE / 2), rectB.origin.y + rectB.size.height*(0.5 - RECTSCALE / 2), rectB.size.width*RECTSCALE, rectB.size.height*RECTSCALE);
	for (auto rectA:rectAs)
	{
		rectA.setRect(rectA.origin.x + rectA.size.width*(0.5 - RECTSCALE / 2), rectA.origin.y + rectA.size.height*(0.5 - RECTSCALE / 2), rectA.size.width*RECTSCALE, rectA.size.height*RECTSCALE);
		if (rectA.intersectsRect(rectB))
		{
			return true;
		}
	}

	return false;
}

bool  CollisionUtill::isCollisionRectAsAndPos(std::vector<Rect> rectAs, Vec2 pos)
{
	for (auto var:rectAs)
	{
		if (var.containsPoint(pos))
		{
			return true;
		}
	}
	return false;
}