/*
    文件名：    HeroManager.h
    描　述：    英雄管理器
   
*/
#ifndef _HeroManager_H_
#define _HeroManager_H_

#include "cocos2d.h"
USING_NS_CC;

#define TOWER_POS_LAYER_LVL 5   // 塔坐标的层次
#define TOWER_BORDER_LAYER_LVL 8  // 炮台的层次
#define TOWER_LAYER_LVL 10  // 塔的层次

class Hero;
class TowerBorder;
class HeroManager : public CCLayer {
public:
	HeroManager();
	~HeroManager();
	static HeroManager* createWithLevel(int iCurLevel);
	bool initWithLevel(int iCurLevel);


	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void registerWithTouchDispatcher( void );

private:
	/* 存放所有塔的坐标对象 */
	CCArray* m_towerPosList;

	/* 存放所有炮台对象 */
	CCArray* m_towerBorderList;

	/* 当前选中的英雄 */
	//Hero* m_curClickHero;

	/* 创建炮台 */
	void createTowerBorder(int iCurLevel);

	/* 给定坐标，生成塔坐标对象 */
	void createTowerPos(CCPoint pos);

// 	/* 给定塔坐标对象，删除塔坐标对象 */
// 	void deleteTowerPos(TowerPos* existPos);
// 
// 	/* 删除所有的塔坐标对象 */
// 	void deleteAllTowerPos();

	/* 找到被点击的炮台对象 */
	TowerBorder* findClickTowerBorder(CCPoint pos);
};

#endif