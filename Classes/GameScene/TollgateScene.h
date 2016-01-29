/*
    �ļ�����    TollgateScene.h
    �衡����    �ؿ�����
   
*/
#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define TAG_MAP_LAYER 1	// �ؿ���ͼͼ��TAG
#define TAG_DATA_LAYER 2	// �ؿ�����ͼ��TAG

class TollgateMapLayer;
class TollgateScene : public CCLayer {
public:
    static CCScene* scene();
    virtual bool init();
	void close(CCObject* pSender,  CCControlEvent event);

    CREATE_FUNC(TollgateScene);
};

#endif