/*
    文件名：    TowerOprBtns.h
    描　述：    英雄操作按钮
    
*/
#ifndef _TowerOprBtns_H_
#define _TowerOprBtns_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Hero;
class GWRoundOprBtn;
class TowerBorder;
class TowerOprBtns : public CCNode {
public:
    TowerOprBtns();
    ~TowerOprBtns();

    static TowerOprBtns* create(TowerBorder* towerBorder, Hero* hero);
    bool init(TowerBorder* towerBorder,Hero* hero);

	void deleteMe();
private:
    Hero* m_hero;
	TowerBorder* m_towerBorder;
	GWRoundOprBtn* m_roundOprBtn;

    void createOprBtns();

	const char* replaceWithI18N(CCString* src);

	void closeEvent(CCObject* pSender, CCControlEvent event);
	void upgradeEvent(CCObject* pSender, CCControlEvent event);
	void detailEvent(CCObject* pSender, CCControlEvent event);
	void deleteEvent(CCObject* pSender, CCControlEvent event);
};

#endif