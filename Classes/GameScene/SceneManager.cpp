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
    case en_TollgateScene: /* �ؿ����� */
        pScene = TollgateScene::scene();
		GlobalClient::sharedGlobalClient()->setCurTollgateScene((TollgateScene*)pScene);
        break;
    case en_TollgateEditorScene:    /* �ؿ��༭������ */
        pScene = TowerPosEditorScene::scene();
        break;
	case en_TollgateSelectScene:	/* �ؿ�ѡ�񳡾� */
		pScene = TollgateSelectScene::scene();
		break;
	case en_WinScene:		/* ʤ������ */
		pScene = WinScene::scene();
		break;
	case en_GameOverScene:	/* ��Ϸ�������� */
		pScene = GameOverScene::scene();
		break;
	case en_StartScene:	/* ��Ϸ��ʼ���� */
		pScene = StartScene::scene();
		break;
	case en_MenuScene:	/* �˵����� */
		pScene = MenuScene::scene();
		break;
	case en_HandbookScene:	/* ͼ������ */
		pScene = HandbookScene::scene();
		break;
	case en_HeroInfoScene:	/* ��Ϣ���� */
		pScene = HeroInfoScene::scene();
		break;
	case en_ShopScene:	/* �̵곡�� */
		pScene = ShopScene::scene();
		break;
	case en_SetScene:	/* ���ó��� */
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
