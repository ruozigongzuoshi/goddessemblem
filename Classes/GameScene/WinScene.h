/*
    文件名：    WinScene.h
    描　述：    胜利场景
  
*/
#ifndef _WinScene_H_
#define _WinScene_H_

#include "cocos2d.h"
USING_NS_CC;

class WinScene : public CCLayer {
public:
	static CCScene* scene();
	CREATE_FUNC(WinScene);
	virtual bool init();

private:
	void backToTollgateSelectScene(float dt);
};

#endif