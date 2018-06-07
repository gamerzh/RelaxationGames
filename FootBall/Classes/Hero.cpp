#include "Hero.h"

bool Hero::init() {
	if (!FootMan::init()) {
		return false;
	}
	return true;
}