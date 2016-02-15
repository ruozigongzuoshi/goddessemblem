/*
    文件名：    TollgateSelectScene.h
    描　述：    关卡选择场景
    
*/
#ifndef _TollgateSelectScene_H_
#define _TollgateSelectScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GWWinManager;
class TollgateSelectScene : public CCLayer {
public:
    static CCScene* scene();
    virtual bool init();

    CREATE_FUNC(TollgateSelectScene);

private:
	CCLabelTTF* createLevelLab(const char* sLvl);
	void  gotoMenu(CCObject* pSender, CCControlEvent event);
    void level_1(CCObject* pSender, CCControlEvent event);
    void level_2(CCObject* pSender, CCControlEvent event);
    void level_3(CCObject* pSender, CCControlEvent event);
    void level_4(CCObject* pSender, CCControlEvent event);
    void level_5(CCObject* pSender, CCControlEvent event);
	void level_6(CCObject* pSender, CCControlEvent event);
    void level_7(CCObject* pSender, CCControlEvent event);
    void level_8(CCObject* pSender, CCControlEvent event);
    void level_9(CCObject* pSender, CCControlEvent event);
    void level_10(CCObject* pSender, CCControlEvent event);
	GWWinManager* winManager;
};

#endif