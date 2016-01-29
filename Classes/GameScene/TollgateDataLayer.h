/*
    �ļ�����    TollgateDataLayer.h
    �衡����    �ؿ�����ͼ��
    
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

	/* ���չ���������Ϣ */
	void recvMonsterDead(CCObject* pData);

	int m_iTowerSoulNum;    /* �������� */
	int m_iMonsterNum;      /* �������� */
	int m_iMagicNum;        /* ħ������ */

	/* �����ǩ */
	GWLabel* m_towerSoulLab;

	/* �����ǩ */
	GWLabel* m_monsterLab;

	/* ħ����ǩ */
	GWLabel* m_magicLab;

	/* �ȼ���ǩ */
	GWLabel* mLVLab;

	/* ������ǩ */
	GWLabel* mATKLab;

	/* �ٶȱ�ǩ */
	GWLabel* mSPLab;

	/* ��Χ��ǩ */
	GWLabel* mSQLab;
};

#endif