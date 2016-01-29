#include "TollgateScene.h"
#include "TollgateMapLayer.h"
#include "GameWidget/GWWinManager.h"
#include "GlobalSetting/GlobalParam.h"
#include "GameWidget/GWBase.h"
#include "TollgateDataLayer.h"

CCScene* TollgateScene::scene() {
    CCScene* scene = NULL;

    do {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        TollgateScene* thisLayer = TollgateScene::create();
        CC_BREAK_IF(! thisLayer);

        TollgateDataLayer* dataLayer = TollgateDataLayer::create();
        CC_BREAK_IF(! dataLayer);

        TollgateMapLayer* layer = TollgateMapLayer::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer, 1, TAG_MAP_LAYER);
		scene->addChild(dataLayer, 2, TAG_DATA_LAYER);
        scene->addChild(thisLayer, 3);
    } while (0);

    return scene;
}

bool TollgateScene::init() {
    CCLayer::init();
	
	/* 将控件添加到当前图层 */
    //this->addChild(GWWinManager::sharedWinManager()->getDesktopWin(), GlobalParam::LayerOrder_LvL1);
	//GWWinManager* winManager = new GWWinManager();
	//this->addChild(winManager->getDesktopWin());
    return true;
}

void TollgateScene::close(CCObject* pSender,  CCControlEvent event)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

