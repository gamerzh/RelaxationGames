#include "GeometryUtils.h"
#include "MapNode.h"

bool GeometryUtils::intersectsRect(const Rect& rect1, const Rect& rect2)
{
	return !(rect1.getMaxX() - rect2.getMinX() <= default_tmx_width / 9 ||
		rect2.getMaxX() - rect1.getMinX() <= default_tmx_width / 9 ||
		rect1.getMaxY() - rect2.getMinY() <= default_tmx_height / 9 ||
		rect2.getMaxY() - rect1.getMinY() <= default_tmx_height / 9);
}