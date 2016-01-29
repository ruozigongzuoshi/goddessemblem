#ifndef __HEROINFO_SCENE_H__
#define __HEROINFO_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HeroInfoScene : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    virtual bool init();  
	CREATE_FUNC(HeroInfoScene);
    void back(CCObject* pSender, CCControlEvent event);
	void close(CCObject* pSender, CCControlEvent event);
	
};

#endif