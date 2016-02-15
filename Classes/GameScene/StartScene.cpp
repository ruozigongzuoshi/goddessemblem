#include "StartScene.h"
#include "SceneManager.h"
#include "GameWidget\GWBase.h"
#include "GameWidget\GWWinManager.h"
#include "platform\CCFileUtils.h"
#include "GlobalSetting\GlobalClient.h"

CCScene* StartScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        StartScene *layer = StartScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    bool bRet = false;
    do 
    {
		//±³¾°ÒôÀÖ
		GlobalClient::sharedGlobalClient()->loadMusicSet();
		if(GlobalClient::sharedGlobalClient()->getMusicSet() > 0){
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/onj001.mp3",false);
		}
		winManager = new GWWinManager();
		GWBase* win = winManager->createWinsFromXML("xml/start.xml");

		this->addChild(winManager->getDesktopWin());

		
		GWScale9Button* gotoMenuBtn = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("startBtn");
		gotoMenuBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(StartScene::gotoMenu),
			CCControlEventTouchUpInside);

		
        bRet = true;
    } while (0);

    return bRet;
}
 void  StartScene::gotoMenu(CCObject* pSender, CCControlEvent event)
 {
	 winManager->getDesktopWin()->removeAllWins();
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_MenuScene);
 }

void StartScene::close(CCObject* pSender,  CCControlEvent event)
{
    // "close" menu item clicked
	winManager->getDesktopWin()->removeAllWins();
    CCDirector::sharedDirector()->end();
}
