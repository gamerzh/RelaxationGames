#include "GameConfig.h"
#include "CallAndroidMethod.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#define  JSONPATH "/Android/data/com.tallbigup.LLK/Config.json"



GameConfig* GameConfig::_instance = 0;
GameConfig::GameConfig(){
}
GameConfig* GameConfig::getInstance(){
	if (_instance == 0){
		_instance = new GameConfig();
	}
	return _instance;
}

bool GameConfig::LoadConfig()
{
	bool bRet = false;
	while (!bRet)
	{

		std::string filename = "Config.json";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && COCOS2D_DEBUG == 1&&0)		
		filename = CallAndroidMethod::getInstance()->JniUtils_SDcardpath();
		filename += JSONPATH;	
#endif
		if (filename == JSONPATH)
		{
			filename = "Config.json";
		}
		log("read json =%s",filename.c_str());
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("get json data err!");
			break;
		}
		//////º”‘ÿ≥°æ∞«–ªª
		rapidjson::Value& scenechange = doc["GameSceneChange"];
		if (!scenechange.IsArray())
		{
			log("The data is not json");
				break;
		}
		for (unsigned int i = 0; i < scenechange.Size(); ++i) {

			const rapidjson::Value &val = scenechange[i];
			SceneChange SC;
			SC.style	  =  val["style"].GetInt();
			SC.ChangeTime =  val["time"].GetDouble();
			SC.state      =  val["state"].GetInt();
			m_SceneChange[val["SceneAToSceneB"].GetString()] = SC;
			log("loadSceneChange: %s style=%d,time=%f,state=%d", val["SceneAToSceneB"].GetString(), SC.style, SC.ChangeTime, SC.state);
		}

		return true;
	}
}
Scene* GameConfig::getSceneOfChangeStyleByName(Scene* scene, std::string SceneAtoSceneB)
{
	SceneChange SC = m_SceneChange[SceneAtoSceneB];
	Scene* CurScene;
	log("SceneChange: %s style=%d,time=%f,state=%d",SceneAtoSceneB.c_str(), SC.style, SC.ChangeTime, SC.state);
	switch (SC.style)
	{
	case 1:
		CurScene = TransitionCrossFade::create(SC.ChangeTime, scene);
		break;
	case 2:
		CurScene = TransitionFade::create(SC.ChangeTime, scene);
		break;
	case 3:
		CurScene = TransitionFadeBL::create(SC.ChangeTime, scene);
		break;
	case 4:
		CurScene = TransitionFadeDown::create(SC.ChangeTime, scene);
		break;
	case 5:
		CurScene = TransitionFadeTR::create(SC.ChangeTime, scene);
		break;
	case 6:
		CurScene = TransitionFadeUp::create(SC.ChangeTime, scene);
		break;
	case 7:
		if (SC.state)
		{
			CurScene = TransitionFlipAngular::create(SC.ChangeTime, scene, TransitionScene::Orientation::LEFT_OVER);
		}
		else
		{
			CurScene = TransitionFlipAngular::create(SC.ChangeTime, scene, TransitionScene::Orientation::RIGHT_OVER);
		}
		break;
	case 8:
		if (SC.state)
		{
			CurScene = TransitionFlipX::create(SC.ChangeTime, scene, TransitionScene::Orientation::LEFT_OVER);
		}
		else
		{
			CurScene = TransitionFlipX::create(SC.ChangeTime, scene, TransitionScene::Orientation::RIGHT_OVER);
		}
		break;
	case 9:
		if (SC.state)
		{
			CurScene = TransitionFlipY::create(SC.ChangeTime, scene, TransitionScene::Orientation::UP_OVER);
		}
		else
		{
			CurScene = TransitionFlipY::create(SC.ChangeTime, scene, TransitionScene::Orientation::DOWN_OVER);
		}
		break;
	case 10:
		CurScene = TransitionJumpZoom::create(SC.ChangeTime, scene);
		break;
	case 11:
		CurScene = TransitionMoveInB::create(SC.ChangeTime, scene);
		break;
	case 12:
		CurScene = TransitionMoveInL::create(SC.ChangeTime, scene);
		break;
	case 13:
		CurScene = TransitionMoveInT::create(SC.ChangeTime, scene);
		break;
	case 14:
		CurScene = TransitionMoveInR::create(SC.ChangeTime, scene);
		break;
	case 15:
		CurScene = TransitionPageTurn::create(SC.ChangeTime, scene, SC.state);
		break;
	case 16:
		CurScene = TransitionProgressHorizontal::create(SC.ChangeTime, scene);
		break;
	case 17:
		CurScene = TransitionProgressInOut::create(SC.ChangeTime, scene);
		break;
	case 18:
		CurScene = TransitionProgressOutIn::create(SC.ChangeTime, scene);
		break;
	case 19:
		CurScene = TransitionProgressRadialCCW::create(SC.ChangeTime, scene);
		break;
	case 20:
		CurScene = TransitionProgressRadialCW::create(SC.ChangeTime, scene);
		break;
	case 21:
		CurScene = TransitionProgressVertical::create(SC.ChangeTime, scene);
		break;
	case 22:
		CurScene = TransitionRotoZoom::create(SC.ChangeTime, scene);
		break;
	case 23:
		CurScene = TransitionShrinkGrow::create(SC.ChangeTime, scene);
		break;
	case 24:
		CurScene = TransitionSlideInB::create(SC.ChangeTime, scene);
		break;
	case 25:
		CurScene = TransitionSlideInL::create(SC.ChangeTime, scene);
		break;
	case 26:
		CurScene = TransitionSlideInR::create(SC.ChangeTime, scene);
		break;
	case 27:
		CurScene = TransitionSlideInT::create(SC.ChangeTime, scene);
		break;
	case 28:
		CurScene = TransitionSplitCols::create(SC.ChangeTime, scene);
		break;
	case 29:
		CurScene = TransitionSplitRows::create(SC.ChangeTime, scene);
		break;
	case 30:
		CurScene = TransitionTurnOffTiles::create(SC.ChangeTime, scene);
		break;
	case 31:
		if (SC.state)
		{
			CurScene = TransitionZoomFlipAngular::create(SC.ChangeTime, scene, TransitionScene::Orientation::LEFT_OVER);
		}
		else
		{
			CurScene = TransitionZoomFlipAngular::create(SC.ChangeTime, scene, TransitionScene::Orientation::RIGHT_OVER);
		}
		break;
	case 32:
		if (SC.state)
		{
			CurScene = TransitionZoomFlipX::create(SC.ChangeTime, scene, TransitionScene::Orientation::LEFT_OVER);
		}
		else
		{
			CurScene = TransitionZoomFlipX::create(SC.ChangeTime, scene, TransitionScene::Orientation::RIGHT_OVER);
		}
		break;
	case 33:
		if (SC.state)
		{
			CurScene = TransitionZoomFlipY::create(SC.ChangeTime, scene, TransitionScene::Orientation::UP_OVER);
		}
		else
		{
			CurScene = TransitionZoomFlipY::create(SC.ChangeTime, scene, TransitionScene::Orientation::DOWN_OVER);
		}
		break;
	}
	return CurScene;
}
