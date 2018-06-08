#include "FootManTeam.h"
USING_NS_CC;
using namespace std;

FootManTeam* FootManTeam::create()
{
	FootManTeam *ret = new FootManTeam();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool FootManTeam::init() {
	
	return true;
}