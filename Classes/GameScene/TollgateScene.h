/*
    文件名：    TollgateScene.h
    描　述：    关卡场景
   
*/
#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define TAG_MAP_LAYER 1	// 关卡地图图层TAG
#define TAG_DATA_LAYER 2	// 关卡数据图层TAG

class TollgateMapLayer;
class TollgateScene : public CCLayer {
public:
    static CCScene* scene();
    virtual bool init();
	void close(CCObject* pSender,  CCControlEvent event);

    CREATE_FUNC(TollgateScene);
};

#endif