#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "GameScene/TowerPosEditorScene.h"
#include "GameEntity/PosLoadUtil.h"
#include "GameScene/SceneManager.h"
#include "FileLoad/CsvUtil.h"
#include "FileLoad/I18N.h"
#include "GlobalSetting/GlobalParam.h"
#include "GlobalSetting/GlobalClient.h"
#include "GameWidget/GWWinManager.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate() {
	CC_SAFE_RETAIN(PosLoadUtil::sharedPosLoadUtil());
	CC_SAFE_RETAIN(SceneManager::sharedSceneManager());
	CC_SAFE_RETAIN(CsvUtil::sharedCsvUtil());
	CC_SAFE_RETAIN(I18N::shareI18N());
	CC_SAFE_RETAIN(GlobalClient::sharedGlobalClient());
	//CC_SAFE_RETAIN(GWWinManager::sharedWinManager());
}

AppDelegate::~AppDelegate() {
	CC_SAFE_RELEASE(PosLoadUtil::sharedPosLoadUtil());
	CC_SAFE_RELEASE(SceneManager::sharedSceneManager());
	CC_SAFE_RELEASE(CsvUtil::sharedCsvUtil());
	CC_SAFE_RELEASE(I18N::shareI18N());
	CC_SAFE_RELEASE(GlobalClient::sharedGlobalClient());
	//CC_SAFE_RELEASE(GWWinManager::sharedWinManager());

    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching() {
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(
		GlobalParam::DEFAULT_SCREEN_WIDTH,
		GlobalParam::DEFAULT_SCREEN_HEIGHT,
		kResolutionFixedHeight);

    pDirector->setDisplayStats(true);

    pDirector->setAnimationInterval(1.0 / 60);

	/* 调用场景管理器切换场景 */
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_StartScene);
	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
