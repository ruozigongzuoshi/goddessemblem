/*
    文件名：    WidgetHPSlot.h
    描　述：    控件——血量条
    
*/
#ifndef _WidgetHPSlot_H_
#define _WidgetHPSlot_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Entity;
class WidgetHPSlot : public CCNode {
public:
	WidgetHPSlot();
	~WidgetHPSlot();
    static WidgetHPSlot* create(Entity* entity);
	bool init(Entity* entity);

	CCControlSlider* getSlider();
private:
	Entity* m_entity;	// 主体
	CCControlSlider* m_slider;	// 血量条
};

#endif