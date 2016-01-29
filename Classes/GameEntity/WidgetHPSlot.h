/*
    �ļ�����    WidgetHPSlot.h
    �衡����    �ؼ�����Ѫ����
    
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
	Entity* m_entity;	// ����
	CCControlSlider* m_slider;	// Ѫ����
};

#endif