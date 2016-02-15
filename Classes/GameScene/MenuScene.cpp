#include "MenuScene.h"
#include "GameWidget\GWBase.h"
#include "GameWidget\GWWinManager.h"
#include "GameScene\SceneManager.h"
#include "GlobalSetting\GlobalClient.h"


CCScene* MenuScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MenuScene *layer = MenuScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    bool bRet = false;
    do 
    {
		//背景音乐
		GlobalClient::sharedGlobalClient()->loadMusicSet();
		if(GlobalClient::sharedGlobalClient()->getMusicSet() > 0){
			CCString* music = CCString::createWithFormat("music/tollgate_%d.mp3",(int)(CCRANDOM_0_1()*10)+1);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(music->getCString(),true);
		}
		manager = new GWWinManager();
		GWBase* win = manager->createWinsFromXML("xml/menu.xml");

		this->addChild(manager->getDesktopWin());

		
		GWScale9Button* storyBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("storyBtn");
		storyBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(MenuScene::storyMode),
			CCControlEventTouchUpInside);

		GWScale9Button* freedomBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("freedomBtn");
		freedomBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(MenuScene::freedomMode),
			CCControlEventTouchUpInside);

		GWScale9Button* handbookBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("handbookBtn");
		handbookBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(MenuScene::handbook),
			CCControlEventTouchUpInside);

		GWScale9Button* shopBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("shopBtn");
		shopBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(MenuScene::shop),
			CCControlEventTouchUpInside);
		GWScale9Button* setBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("setBtn");
		setBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(MenuScene::set),
			CCControlEventTouchUpInside);
		GWScale9Button* closeBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("closeBtn");
		closeBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(MenuScene::close),
			CCControlEventTouchUpInside);
        bRet = true;
    } while (0);

    return bRet;
}
void  MenuScene::storyMode(CCObject* pSender, CCControlEvent event)
 {
	 manager->getDesktopWin()->removeAllWins();
	 /* 调用场景管理器切换场景 */
     SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateSelectScene);
 }

void  MenuScene::set(CCObject* pSender, CCControlEvent event)
 {
	 manager->getDesktopWin()->removeAllWins();
	 /* 调用场景管理器切换场景 */
     SceneManager::sharedSceneManager()->changeScene(SceneManager::en_SetScene);
 }

void  MenuScene::freedomMode(CCObject* pSender, CCControlEvent event)
 {
	 manager->getDesktopWin()->removeAllWins();
	 /* 调用场景管理器切换场景 */
     SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateEditorScene);
 }

void  MenuScene::handbook(CCObject* pSender, CCControlEvent event)
 {
	 manager->getDesktopWin()->removeAllWins();
	 /* 调用场景管理器切换场景 */
     SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HandbookScene);
 }

void  MenuScene::shop(CCObject* pSender, CCControlEvent event)
 {
	 manager->getDesktopWin()->removeAllWins();
	 /* 调用场景管理器切换场景 */
     SceneManager::sharedSceneManager()->changeScene(SceneManager::en_ShopScene);
 }

void MenuScene::close(CCObject* pSender,  CCControlEvent event)
{
	manager->getDesktopWin()->removeAllWins();
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}



