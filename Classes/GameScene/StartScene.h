#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
class GWWinManager;

class StartScene : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    virtual bool init();  
	CREATE_FUNC(StartScene);
    void gotoMenu(CCObject* pSender, CCControlEvent event);
	void close(CCObject* pSender, CCControlEvent event);
private:
	GWWinManager* winManager;
};

#endif