#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GWLabel;
class GWWinManager;

class ShopScene : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    virtual bool init();  
	virtual void goldUpdate(float dt);
	CREATE_FUNC(ShopScene);
    void  gotoMenu(CCObject* pSender, CCControlEvent event);
	void close(CCObject* pSender, CCControlEvent event);
	void loadGold();
	void saveGold();
	void setLockLabel();
private:
	GWLabel* goldLabel;
	CCArray* heroLabel;
	
	GWWinManager* manager;
};

#endif