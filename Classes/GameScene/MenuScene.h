#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GWWinManager;

class MenuScene : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    virtual bool init();  
	CREATE_FUNC(MenuScene);
    void storyMode(CCObject* pSender, CCControlEvent event);
	void freedomMode(CCObject* pSender, CCControlEvent event);
	void handbook(CCObject* pSender, CCControlEvent event);
	void shop(CCObject* pSender, CCControlEvent event);
	void close(CCObject* pSender, CCControlEvent event);
	void set(CCObject* pSender, CCControlEvent event);
private:
	GWWinManager* manager;
};

#endif