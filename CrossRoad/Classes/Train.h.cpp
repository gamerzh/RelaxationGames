#include "Train.h"


bool Train::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}