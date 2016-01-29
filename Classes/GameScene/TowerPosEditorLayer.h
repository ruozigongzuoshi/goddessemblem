/*
    文件名：    TowerPosEditorLayer.h
    描　述：    塔坐标编辑器，编辑层
   
*/
#ifndef _TowerPosEditorLayer_H_
#define _TowerPosEditorLayer_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameEntity/EnumPosType.h"
#include "GameEntity/TowerPos.h"
#include "GameEntity/MonsterPos.h"
#include "GameEntity/PosLoadUtil.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define MAX_LEVEL = 5;

class TowerPosEditorLayer : public CCLayer {
public:
    TowerPosEditorLayer();
    ~TowerPosEditorLayer();

    CREATE_FUNC(TowerPosEditorLayer);
    virtual bool init();

    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

    virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

    virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

    virtual void registerWithTouchDispatcher( void );

    /* 把所有坐标对象生成到plist配置文件 */
    void outputPosToPlistFile();

    /* 切换到下一关 */
    int nextLvl();

    /* 切换到上一关 */
    int preLvl();

	/* 切换模式（塔坐标编辑/怪物坐标编辑） */
	int changeMode();
	
    /* 切换到下一波 */
    int nextList();

    /* 切换到上一波 */
    int preList();

	/*删除怪物行走队列*/
	void deleteNowMonsterList();

	void addNewMonsterList();//新增怪物波数

	CCString* startMonsterMgr();//设置怪物队列

	CCArray* getMonsterMgrPosList();
	
	void addNowMonster();

	void deleteLastMonster();

	int preMonster();

	int nextMonster();

private:

	int m_monsterListNum; //怪物队列数量

    /* 存放所有塔的坐标对象 */
    CCArray* m_towerPosList;

    /* 当前关卡 */
    int m_iCurLevel;

    /* 当前波数 */
    int m_iCurList;

	/* 当前怪物 */
    int m_iCurMonster;

	/* 把指定坐标对象生成到plist配置文件 */
	void outputPosToPlistFile(CCArray* posList, const char* sFilePath);
	void outputPosToPlistFile2(CCArray* posList, const char* sFilePath);

	/* 把指定坐标对象生成到plist配置文件 */
	void outputPosToPlistFile(int m_monsterListNum, const char* sFilePath);

    /* 读取关卡对应配置文件，生成坐标对象 */
    void loadConfigFile();

	/* 编辑塔坐标 */
	void editTowerPos(CCPoint pos);

	/* 根据坐标找到已经存在的塔坐标对象 */
	TowerPos* findExistTowerPos(CCPoint pos);

    /* 给定坐标，生成塔坐标对象 */
    void createTowerPos(CCPoint pos);

    /* 给定塔坐标对象，删除塔坐标对象 */
    void deleteTowerPos(TowerPos* existPos);

    /* 删除所有的坐标对象 */
    void deleteAllPos();

	/* 当前模式 */
	EnumPosType m_enMode;

	/* 编辑怪物坐标 */
	//void editMonsterPos(CCPoint pos);
	void editMonsterPos(CCArray* m_monsterPosList, CCPoint pos);

	/* 存放所有怪物的坐标对象 */
	CCArray* m_monsterMgrPosList;

	/* 存放所有怪物对象列表 */
	CCArray* m_monsterMgrList;

	/* 根据坐标找到已经存在的怪物坐标对象 */
	//MonsterPos* findExistMonsterPos(CCPoint pos);
	MonsterPos* findExistMonsterPos(CCArray*  m_monsterPosList, CCPoint pos);

	/* 给定坐标，生成怪物坐标对象 */
	//void createMonsterPos(CCPoint pos);
	void createMonsterPos(CCArray*  m_monsterPosList, CCPoint pos);

	/* 给定怪物坐标对象，删除怪物坐标对象 */
	//void deleteMonsterPos(MonsterPos* existPos);
	void deleteMonsterPos(CCArray*  m_monsterPosList, MonsterPos* existPos);
};

#endif