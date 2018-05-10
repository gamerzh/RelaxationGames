#include "GoldIcon.h"


bool GoldIcon::init() {
	if (!Sprite::init()) {
		return false;
	}
	initWithFile("gold_icon.png");
	setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	return true;
}