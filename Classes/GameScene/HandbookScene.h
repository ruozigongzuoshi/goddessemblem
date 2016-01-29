#ifndef __HANDBOOK_SCENE_H__
#define __HANDBOOK_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HandbookScene : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    virtual bool init();  
	CREATE_FUNC(HandbookScene);
    void gotoHero1Info(CCObject* pSender, CCControlEvent event);
	void gotoHero2Info(CCObject* pSender, CCControlEvent event);
	void gotoHero3Info(CCObject* pSender, CCControlEvent event);
	void gotoHero4Info(CCObject* pSender, CCControlEvent event);
	void gotoHero5Info(CCObject* pSender, CCControlEvent event);
	void gotoHero6Info(CCObject* pSender, CCControlEvent event);
	void gotoHero7Info(CCObject* pSender, CCControlEvent event);
	void gotoHero8Info(CCObject* pSender, CCControlEvent event);
	void gotoHero9Info(CCObject* pSender, CCControlEvent event);
	void gotoHero10Info(CCObject* pSender, CCControlEvent event);
	void back(CCObject* pSender, CCControlEvent event);
	void close(CCObject* pSender, CCControlEvent event);
	
};

#endif