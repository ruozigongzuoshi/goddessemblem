/*
    文件名：    TollgateMapLayer.h
    描　述：    关卡地图图层
    
*/
#ifndef _TollgateMapLayer_H_
#define _TollgateMapLayer_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define HOME_LAYER_LVL 3  // 堡垒的层次
#define HERO_LAYER_LVL 10    // 英雄的层次
#define MONSTER_LAYER_LVL 15    // 怪物的层次
#define BULLET_LAYER_LVL 20  // 子弹的层次


class TowerPos;
class Home;
class Hero;
class MonsterManager;
class HeroManager;
class TollgateMapLayer : public CCLayer {
public:
    TollgateMapLayer();
    ~TollgateMapLayer();

    CREATE_FUNC(TollgateMapLayer);
    virtual bool init();

	/* 获取所有怪物对象 */
	CCArray* getMonsterList();

    virtual void onExit();
private:
	void removeMonsterList(CCObject* pData);
	/* 怪物管理器 */
	//MonsterManager* m_monsterMgr;

	CCArray* m_monsterMgrList;

	/* 英雄管理器 */
	HeroManager* m_heroMgr;

    /* 当前关卡 */
    int m_iCurLevel;

	/*怪物波数*/
	int m_monsterListNum;

    /* 读取关卡配置 */
    void loadConfig();

    /*创建堡垒  */
    void createHome();

    /* 创建起始点 */
    void createStartPoint();
};

#endif