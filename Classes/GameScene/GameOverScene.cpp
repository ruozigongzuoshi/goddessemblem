#include "GameOverScene.h"
#include "GlobalSetting/GlobalPath.h"
#include "GlobalSetting/GlobalParam.h"
#include "SceneManager.h"

CCScene* GameOverScene::scene() {
	CCScene* scene = NULL;

	do {
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		GameOverScene* layer = GameOverScene::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool GameOverScene::init() {
	bool bRet = false;

	do {
		CC_BREAK_IF(! CCLayer::init());

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

		CCLabelTTF* winLab = CCLabelTTF::create("GameOver!", PATH_FONT_PUBLIC, GlobalParam::PublicFontSizeLarge);
		winLab->setPosition(ccp(visibleSize.width / 2, visibleSize.height - 100));
		this->addChild(winLab);

		/* 3秒后返回关卡选择场景 */
		this->schedule(schedule_selector(GameOverScene::backToTollgateSelectScene), 3.0f);

		bRet = true;
	} while (0);

	return bRet;
}

void GameOverScene::backToTollgateSelectScene( float dt ) {
	SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateSelectScene);
}
