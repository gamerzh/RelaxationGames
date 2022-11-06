#include "AppDelegate.h"
#include "lobby/LobbyScene.h"
#include "config/ConfigDebugTest.h"
#include "domain/user/User.h"
#include "server/HttpMannger.h"
#include "domain/loading/LoadingScene.h"
#include "domain/globalschedule/GlobalSchedule.h"
#include "domain/logevent/LogEventMannger.h"
#include "utill/Audio.h"
#include "domain/pay/Pay.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	ConfigDebugTest::getInstance()->LoadConfig();
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("CrazyFarm");
		director->setOpenGLView(glview);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	glview->setFrameSize(960, 540);
	glview->setDesignResolutionSize(960, 540, ResolutionPolicy::EXACT_FIT);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (visibleSize.width / visibleSize.height > 960.0 / 540.0){

		glview->setDesignResolutionSize(960, 540, ResolutionPolicy::EXACT_FIT);
	}
	else{
		glview->setDesignResolutionSize(960, 540, ResolutionPolicy::EXACT_FIT);
	}
#endif
    
	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);


	std::vector<std::string> paths;
	paths.push_back("game");
	paths.push_back("config");
	paths.push_back("game/ui");
	paths.push_back("game/ui/gamelayer");
	paths.push_back("game/ui/ani");
	paths.push_back("game/ui/num");
	paths.push_back("game/config");
	paths.push_back("game/ui/lobbylayer");
	paths.push_back("game/ui/bagLayer");
	paths.push_back("game/ui/fish");
	paths.push_back("game/ui/showfish");
	paths.push_back("game/ui/signLayer");
	paths.push_back("game/ui/payShop");
	paths.push_back("game/ui/showVIP");
	paths.push_back("game/ui/turret");
	paths.push_back("game/ui/NobilityLayer");
	paths.push_back("game/ui/dialog");
	paths.push_back("game/ui/gamelayer/turntable");
	paths.push_back("game/ui/gamelayer/mermaid");
	paths.push_back("game/ui/ranklist");
	paths.push_back("game/ui/NewBie");
	paths.push_back("game/ui/txt");
	paths.push_back("game/ui/gamelayer/playerturret");
	paths.push_back("game/ui/loading");
	paths.push_back("game/ui/payShop");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);
	srand(time(NULL));
	auto timenode = GlobalSchedule::getInstance();
	// create a scene. it's an autorelease object
	auto scene = LoadingScene::createScene();
	
	// run
	director->runWithScene(scene);

	//LoadingScene* node = (LoadingScene*)(scene->getChildByTag(888));
	//node->load();
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	Audio::getInstance()->pauseBGM();
	LogEventMannger::getInstance()->sendMsg();
	log("come to backgroud");

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	Audio::getInstance()->resumeBGM();
	
	if (Pay::getInstance()->getIsPaying())
	{
		Pay::getInstance()->CancelTheOrder();
	}

	log("come to game");

}


