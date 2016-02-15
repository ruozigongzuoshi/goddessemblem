#include "HandbookScene.h"
#include "SceneManager.h"
#include "GameWidget\GWBase.h"
#include "GameWidget\GWWinManager.h"
#include "GlobalSetting/GlobalClient.h"

CCScene* HandbookScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HandbookScene *layer = HandbookScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HandbookScene::init()
{
    bool bRet = false;
    do 
    {
		//±³¾°ÒôÀÖ
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("start.mp3",true);
		manager = new GWWinManager();
		GWBase* win = manager->createWinsFromXML("xml/handbook.xml");

		this->addChild(manager->getDesktopWin());
		
		GWScale9Button* hero1 = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero1");
		hero1->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::gotoHero1Info),
			CCControlEventTouchUpInside);

		GWScale9Button* hero2 = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero2");
		hero2->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::gotoHero2Info),
			CCControlEventTouchUpInside);

		GWScale9Button* hero3 = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero3");
		hero3->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::gotoHero3Info),
			CCControlEventTouchUpInside);

		GWScale9Button* hero4 = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero4");
		hero4->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::gotoHero4Info),
			CCControlEventTouchUpInside);

		GWScale9Button* hero5 = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero5");
		hero5->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::gotoHero5Info),
			CCControlEventTouchUpInside);

		GWScale9Button* hero6 = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero6");
		hero6->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::gotoHero6Info),
			CCControlEventTouchUpInside);

		GWScale9Button* hero7 = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero7");
		hero7->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::gotoHero7Info),
			CCControlEventTouchUpInside);

		GWScale9Button* hero8 = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero8");
		hero8->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::gotoHero8Info),
			CCControlEventTouchUpInside);

		GWScale9Button* hero9 = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero9");
		hero9->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::gotoHero9Info),
			CCControlEventTouchUpInside);

		GWScale9Button* hero10 = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero10");
		hero10->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::gotoHero10Info),
			CCControlEventTouchUpInside);

		GWScale9Button* back = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("back");
		back->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HandbookScene::back),
			CCControlEventTouchUpInside);
		
        bRet = true;
    } while (0);

    return bRet;
}
 void  HandbookScene::gotoHero1Info(CCObject* pSender, CCControlEvent event)
 {
	 
	 GlobalClient::sharedGlobalClient()->set_iCurHeroNo(1);
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HeroInfoScene);
 }

 void  HandbookScene::gotoHero2Info(CCObject* pSender, CCControlEvent event)
 {
	 
	 GlobalClient::sharedGlobalClient()->set_iCurHeroNo(2);
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HeroInfoScene);
 }

 void  HandbookScene::gotoHero3Info(CCObject* pSender, CCControlEvent event)
 {
	 
	 GlobalClient::sharedGlobalClient()->set_iCurHeroNo(3);
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HeroInfoScene);
 }

 void  HandbookScene::gotoHero4Info(CCObject* pSender, CCControlEvent event)
 {
	 
	 GlobalClient::sharedGlobalClient()->set_iCurHeroNo(4);
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HeroInfoScene);
 }

 void  HandbookScene::gotoHero5Info(CCObject* pSender, CCControlEvent event)
 {
	 
	 GlobalClient::sharedGlobalClient()->set_iCurHeroNo(5);
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HeroInfoScene);
 }

  void  HandbookScene::gotoHero6Info(CCObject* pSender, CCControlEvent event)
 {
	 
	 GlobalClient::sharedGlobalClient()->set_iCurHeroNo(6);
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HeroInfoScene);
 }

 void  HandbookScene::gotoHero7Info(CCObject* pSender, CCControlEvent event)
 {
	 
	 GlobalClient::sharedGlobalClient()->set_iCurHeroNo(7);
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HeroInfoScene);
 }

 void  HandbookScene::gotoHero8Info(CCObject* pSender, CCControlEvent event)
 {
	 
	 GlobalClient::sharedGlobalClient()->set_iCurHeroNo(8);
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HeroInfoScene);
 }

 void  HandbookScene::gotoHero9Info(CCObject* pSender, CCControlEvent event)
 {
	 
	 GlobalClient::sharedGlobalClient()->set_iCurHeroNo(9);
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HeroInfoScene);
 }

 void  HandbookScene::gotoHero10Info(CCObject* pSender, CCControlEvent event)
 {
	
	 GlobalClient::sharedGlobalClient()->set_iCurHeroNo(10);
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HeroInfoScene);
 }

 void  HandbookScene::back(CCObject* pSender, CCControlEvent event)
 {
	 manager->getDesktopWin()->removeAllWins();
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_MenuScene);
 }

void HandbookScene::close(CCObject* pSender,  CCControlEvent event)
{
    // "close" menu item clicked
	manager->getDesktopWin()->removeAllWins();
    CCDirector::sharedDirector()->end();
}

