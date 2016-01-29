#include "SceneManager.h"
#include "GameScene/TowerPosEditorScene.h"
#include "TollgateScene.h"
#include "GameWidget\GWWinManager.h"
#include "GlobalSetting/GlobalClient.h"
#include "TollgateSelectScene.h"
#include "WinScene.h"
#include "GameOverScene.h"
#include "StartScene.h"
#include "MenuScene.h"
#include "HandbookScene.h"
#include "HeroInfoScene.h"
#include "ShopScene.h"
#include "SetScene.h"

SceneManager* SceneManager::mSceneManager = NULL;

SceneManager* SceneManager::sharedSceneManager() {
    if(mSceneManager == NULL) {
        mSceneManager = new SceneManager();
        if(mSceneManager && mSceneManager->init()) {
            mSceneManager->autorelease();
        }
        else {
            CC_SAFE_DELETE(mSceneManager);
            mSceneManager = NULL;
        }
    }

    return mSceneManager;
}

bool SceneManager::init() {

    return true;
}

void SceneManager::changeScene( EnumSceneType enScenType ) {
    CCScene* pScene = NULL;
	
    switch (enScenType) {
    case en_TollgateScene: /* 关卡场景 */
        pScene = TollgateScene::scene();
		GlobalClient::sharedGlobalClient()->setCurTollgateScene((TollgateScene*)pScene);
        break;
    case en_TollgateEditorScene:    /* 关卡编辑器场景 */
        pScene = TowerPosEditorScene::scene();
        break;
	case en_TollgateSelectScene:	/* 关卡选择场景 */
		pScene = TollgateSelectScene::scene();
		break;
	case en_WinScene:		/* 胜利场景 */
		pScene = WinScene::scene();
		break;
	case en_GameOverScene:	/* 游戏结束场景 */
		pScene = GameOverScene::scene();
		break;
	case en_StartScene:	/* 游戏开始场景 */
		pScene = StartScene::scene();
		break;
	case en_MenuScene:	/* 菜单场景 */
		pScene = MenuScene::scene();
		break;
	case en_HandbookScene:	/* 图鉴场景 */
		pScene = HandbookScene::scene();
		break;
	case en_HeroInfoScene:	/* 信息场景 */
		pScene = HeroInfoScene::scene();
		break;
	case en_ShopScene:	/* 商店场景 */
		pScene = ShopScene::scene();
		break;
	case en_SetScene:	/* 设置场景 */
		pScene = SetScene::scene();
		break;
    }

    if(pScene == NULL) {
        return;
    }

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* curScene = pDirector->getRunningScene();
    if(curScene == NULL) {
        pDirector->runWithScene(pScene);
    }
    else {
        pDirector->replaceScene(pScene);
    }
}
