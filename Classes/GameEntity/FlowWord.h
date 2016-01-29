/*
    文件名：    FlowWorld.h
    描　述：    漂浮字体
    
*/

#ifndef _FlowWord_H_
#define _FlowWord_H_

#include "cocos2d.h"
USING_NS_CC;

class FlowWord : public CCNode {
public:
	static FlowWord* create();
	bool init();

public:
	void showWord(const char* text, CCPoint pos);
private:
	CCLabelTTF* m_textLab;

	void flowEnd();
};

#endif