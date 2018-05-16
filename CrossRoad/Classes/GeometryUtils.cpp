#include "GeometryUtils.h"
#include "MapNode.h"
#include "Player.h"

bool GeometryUtils::intersectsRect(const Rect& rect1, const Rect& rect2)
{
	return !(rect1.getMaxX() - rect2.getMinX() <= default_tmx_width / 8 ||
		rect2.getMaxX() - rect1.getMinX() <= default_tmx_width / 8 ||
		rect1.getMaxY() - rect2.getMinY() <= default_tmx_height / 8 ||
		rect2.getMaxY() - rect1.getMinY() <= default_tmx_height / 8);
}

Vec2 GeometryUtils::transitionPlayerVec2(Vec2 vec, int index) {
	float x = floor(vec.x / default_tmx_width)*default_tmx_width
		+ (PLAYER_JUMP_OFFSET * (int)floor(vec.y / default_tmx_height)) % default_tmx_width;
	float y = floor(vec.y / default_tmx_height)*default_tmx_height + (index-1)*default_tmx_height*defult_tmx_y_num;
	return Vec2(x, y);
}


Vec2 GeometryUtils::transitionObjectVec2(Vec2 vec, int index) {
	float x = round(vec.x / default_tmx_width)*default_tmx_width 
		+ ((int)round(vec.y / default_tmx_height)*PLAYER_JUMP_OFFSET) % default_tmx_width;
	float y = round(vec.y / default_tmx_height)*default_tmx_height + (index - 1)*default_tmx_height*defult_tmx_y_num;
	return Vec2(x,y);
}

Size GeometryUtils::transitionObjectSize(Size checkSize) {
	float width = round(checkSize.width / default_tmx_width)*default_tmx_width;
	float height = round(checkSize.height / default_tmx_height)*default_tmx_height;
	return Size(width,height);
}

float GeometryUtils::randomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}