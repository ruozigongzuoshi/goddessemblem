/*
    文件名：    TollgateDataLayer.h
    描　述：    关卡数据图层
    
*/
#ifndef _TollgateDataLayer_H_
#define _TollgateDataLayer_H_


#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GWLabel;
class TollgateDataLayer : public CCLayer {
public:
	TollgateDataLayer();
	~TollgateDataLayer();

	CREATE_FUNC(TollgateDataLayer);
	virtual bool init();

	virtual void onExit();

	int getiMagicNum();
	int getiTowerSoulNum();
private:
	void endGame(CCObject* pSender, CCControlEvent event);
	void recvRefreshTowerSoulNum(CCObject* pData);
	void recvRefreshMonsterNum(CCObject* pData);
	void recvRefreshMagicNum(CCObject* pData);
	void recvGameIsWin(CCObject* pData);
	void recvRefreshLevelNum(CCObject* pData);
	void recvRefreshATKNum(CCObject* pData);
	void recvRefreshSpeedNum(CCObject* pData);
	void recvRefreshRangeNum(CCObject* pData);
	void setHero(CCObject* pSender, CCControlEvent event);
	void loadGold();

	/* 接收怪物死亡消息 */
	void recvMonsterDead(CCObject* pData);

	int m_iTowerSoulNum;    /* 塔魂数量 */
	int m_iMonsterNum;      /* 怪物数量 */
	int m_iMagicNum;        /* 魔力数量 */

	/* 塔魂标签 */
	GWLabel* m_towerSoulLab;

	/* 怪物标签 */
	GWLabel* m_monsterLab;

	/* 魔力标签 */
	GWLabel* m_magicLab;

	/* 等级标签 */
	GWLabel* mLVLab;

	/* 攻击标签 */
	GWLabel* mATKLab;

	/* 速度标签 */
	GWLabel* mSPLab;

	/* 范围标签 */
	GWLabel* mSQLab;
};

#endif