/*
    �ļ�����    HeroManager.h
    �衡����    Ӣ�۹�����
   
*/
#ifndef _HeroManager_H_
#define _HeroManager_H_

#include "cocos2d.h"
USING_NS_CC;

#define TOWER_POS_LAYER_LVL 5   // ������Ĳ��
#define TOWER_BORDER_LAYER_LVL 8  // ��̨�Ĳ��
#define TOWER_LAYER_LVL 10  // ���Ĳ��

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
	/* ������������������ */
	CCArray* m_towerPosList;

	/* ���������̨���� */
	CCArray* m_towerBorderList;

	/* ��ǰѡ�е�Ӣ�� */
	//Hero* m_curClickHero;

	/* ������̨ */
	void createTowerBorder(int iCurLevel);

	/* �������꣬������������� */
	void createTowerPos(CCPoint pos);

// 	/* �������������ɾ����������� */
// 	void deleteTowerPos(TowerPos* existPos);
// 
// 	/* ɾ�����е���������� */
// 	void deleteAllTowerPos();

	/* �ҵ����������̨���� */
	TowerBorder* findClickTowerBorder(CCPoint pos);
};

#endif