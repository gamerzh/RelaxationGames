#include "FootMan.h"

bool FootMan::init() {
	if (Node::init()) {
		return false;
	}
	return true;
}