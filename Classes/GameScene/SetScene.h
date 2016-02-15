#ifndef __SET_SCENE_H__
#define __SET_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "AssetsManager/AssetsManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GWWinManager;
class GWLabel;

class SetScene : public cocos2d::CCLayer, public cocos2d::extension::AssetsManagerDelegateProtocol
{
public:
	SetScene();
	~SetScene();
    static cocos2d::CCScene* scene();
    virtual bool init();  
	CREATE_FUNC(SetScene);
    void gotoMenu(CCObject* pSender, CCControlEvent event);
	void close(CCObject* pSender, CCControlEvent event);
	//AssetsManager* SetScene::getAssetsManager();
	void updateBtn(CCObject* pSender, CCControlEvent event);
	void btnMusicON(CCObject * obj);
	void btnMusicOFF(CCObject * obj);
	void changeToChinese(CCObject * obj);
	void changeToEnglish(CCObject * obj);
	virtual void onError(cocos2d::extension::AssetsManager::ErrorCode errorCode);
    virtual void onProgress(int percent);
    virtual void onSuccess();
private:
	void createDownloadedDir();
	GWLabel* pProgressLabel;
    std::string pathToSave;
	bool isUpdateItemClicked;
	CCMenuItemImage* musicON;
	CCMenuItemImage* musicOFF;
	CCMenuItemImage* chinese;
	CCMenuItemImage* english;
	AssetsManager* pAssetsManager;
	GWWinManager* winManager;
};

#endif