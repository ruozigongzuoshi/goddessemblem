#include "TollgateSelectScene.h"
#include "SceneManager.h"
#include "GameWidget/GWWinManager.h"
#include "GlobalSetting/GlobalParam.h"
#include "GameWidget/GWBase.h"
#include "GameWidget/GWRoundOprBtn.h"
#include "GlobalSetting/GlobalClient.h"
#include "GlobalSetting/GlobalPath.h"


CCScene* TollgateSelectScene::scene() {
    CCScene* scene = NULL;

    do {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        TollgateSelectScene* layer = TollgateSelectScene::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    return scene;
}

bool TollgateSelectScene::init() {
    bool bRet = false;

    do {
        CC_BREAK_IF(! CCLayer::init());

        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		
        /* 创建关卡选则菜单 */
		winManager = new GWWinManager();

		GWBase* win = winManager->createWinsFromXML("xml/TollgateSelectScene.xml");

		this->addChild(winManager->getDesktopWin());

		
		GWScale9Button* level_1_Item = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("level_1_Item");
		level_1_Item->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::level_1),
			CCControlEventTouchUpInside);

		GWScale9Button* level_2_Item = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("level_2_Item");
		level_2_Item->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::level_2),
			CCControlEventTouchUpInside);

		GWScale9Button* level_3_Item = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("level_3_Item");
		level_3_Item->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::level_3),
			CCControlEventTouchUpInside);

		GWScale9Button* level_4_Item = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("level_4_Item");
		level_4_Item->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::level_4),
			CCControlEventTouchUpInside);
		
		GWScale9Button* level_5_Item = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("level_5_Item");
		level_5_Item->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::level_5),
			CCControlEventTouchUpInside);

		GWScale9Button* level_6_Item = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("level_6_Item");
		level_6_Item->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::level_6),
			CCControlEventTouchUpInside);

		GWScale9Button* level_7_Item = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("level_7_Item");
		level_7_Item->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::level_7),
			CCControlEventTouchUpInside);

		GWScale9Button* level_8_Item = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("level_8_Item");
		level_8_Item->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::level_8),
			CCControlEventTouchUpInside);

		GWScale9Button* level_9_Item = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("level_9_Item");
		level_9_Item->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::level_9),
			CCControlEventTouchUpInside);

		GWScale9Button* level_10_Item = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("level_10_Item");
		level_10_Item->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::level_10),
			CCControlEventTouchUpInside);

		GWScale9Button* gotoMenuBtn = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("back");
		gotoMenuBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateSelectScene::gotoMenu),
			CCControlEventTouchUpInside);
		

	/*
        const char* norImg = "tollgate/choose_btn_nor.png";
        const char* lightImg = "tollgate/choose_btn_light.png";
        const char* disableImg = "tollgate/choose_btn_light.png";

        CCMenuItemImage* level_1_Item = CCMenuItemImage::create(norImg, lightImg, disableImg, this,
            menu_selector(TollgateSelectScene::level_1));
		level_1_Item->addChild(createLevelLab("1"));

        CCMenuItemImage* level_2_Item = CCMenuItemImage::create(norImg, lightImg, disableImg, this,
            menu_selector(TollgateSelectScene::level_2));
		level_2_Item->addChild(createLevelLab("2"));

//         CCMenuItemImage* level_3_Item = CCMenuItemImage::create(norImg, lightImg, disableImg, this,
//             menu_selector(TollgateSelectScene::level_3));
// 		level_3_Item->addChild(createLevelLab("3"));
// 
//         CCMenuItemImage* level_4_Item = CCMenuItemImage::create(norImg, lightImg, disableImg, this,
//             menu_selector(TollgateSelectScene::level_4));
// 		level_4_Item->addChild(createLevelLab("4"));
// 
//         CCMenuItemImage* level_5_Item = CCMenuItemImage::create(norImg, lightImg, disableImg, this,
//             menu_selector(TollgateSelectScene::level_5));
// 		level_5_Item->addChild(createLevelLab("5"));

        CCMenu* menu = CCMenu::create(level_1_Item, level_2_Item, NULL);
        menu->alignItemsHorizontallyWithPadding(20);
        menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(menu);
		*/

        bRet = true;
    } while (0);

    return bRet;
}

 void  TollgateSelectScene::gotoMenu(CCObject* pSender, CCControlEvent event)
 {
	 //saveGold();
	 winManager->getDesktopWin()->removeAllWins();
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_MenuScene);
 }

CCLabelTTF* TollgateSelectScene::createLevelLab( const char* sLvl) {
	CCLabelTTF* level_lab = CCLabelTTF::create(sLvl, PATH_FONT_PUBLIC, GlobalParam::PublicFontSizeLargest);
	level_lab->setColor(ccRED);
	level_lab->setPosition(ccp(60, 60));

	return level_lab;
}

void TollgateSelectScene::level_1(CCObject* pSender, CCControlEvent event) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(1);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

void TollgateSelectScene::level_2(CCObject* pSender, CCControlEvent event) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(2);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

void TollgateSelectScene::level_3(CCObject* pSender, CCControlEvent event) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(3);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

void TollgateSelectScene::level_4(CCObject* pSender, CCControlEvent event) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(4);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

void TollgateSelectScene::level_5(CCObject* pSender, CCControlEvent event) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(5);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

void TollgateSelectScene::level_6(CCObject* pSender, CCControlEvent event) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(6);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

void TollgateSelectScene::level_7(CCObject* pSender, CCControlEvent event) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(7);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

void TollgateSelectScene::level_8(CCObject* pSender, CCControlEvent event) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(8);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

void TollgateSelectScene::level_9(CCObject* pSender, CCControlEvent event) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(9);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}

void TollgateSelectScene::level_10(CCObject* pSender, CCControlEvent event) {
    GlobalClient::sharedGlobalClient()->setiCurTollgateLevel(10);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene);
}


