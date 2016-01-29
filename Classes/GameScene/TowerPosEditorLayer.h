/*
    �ļ�����    TowerPosEditorLayer.h
    �衡����    ������༭�����༭��
   
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

    /* ����������������ɵ�plist�����ļ� */
    void outputPosToPlistFile();

    /* �л�����һ�� */
    int nextLvl();

    /* �л�����һ�� */
    int preLvl();

	/* �л�ģʽ��������༭/��������༭�� */
	int changeMode();
	
    /* �л�����һ�� */
    int nextList();

    /* �л�����һ�� */
    int preList();

	/*ɾ���������߶���*/
	void deleteNowMonsterList();

	void addNewMonsterList();//�������ﲨ��

	CCString* startMonsterMgr();//���ù������

	CCArray* getMonsterMgrPosList();
	
	void addNowMonster();

	void deleteLastMonster();

	int preMonster();

	int nextMonster();

private:

	int m_monsterListNum; //�����������

    /* ������������������ */
    CCArray* m_towerPosList;

    /* ��ǰ�ؿ� */
    int m_iCurLevel;

    /* ��ǰ���� */
    int m_iCurList;

	/* ��ǰ���� */
    int m_iCurMonster;

	/* ��ָ������������ɵ�plist�����ļ� */
	void outputPosToPlistFile(CCArray* posList, const char* sFilePath);
	void outputPosToPlistFile2(CCArray* posList, const char* sFilePath);

	/* ��ָ������������ɵ�plist�����ļ� */
	void outputPosToPlistFile(int m_monsterListNum, const char* sFilePath);

    /* ��ȡ�ؿ���Ӧ�����ļ�������������� */
    void loadConfigFile();

	/* �༭������ */
	void editTowerPos(CCPoint pos);

	/* ���������ҵ��Ѿ����ڵ���������� */
	TowerPos* findExistTowerPos(CCPoint pos);

    /* �������꣬������������� */
    void createTowerPos(CCPoint pos);

    /* �������������ɾ����������� */
    void deleteTowerPos(TowerPos* existPos);

    /* ɾ�����е�������� */
    void deleteAllPos();

	/* ��ǰģʽ */
	EnumPosType m_enMode;

	/* �༭�������� */
	//void editMonsterPos(CCPoint pos);
	void editMonsterPos(CCArray* m_monsterPosList, CCPoint pos);

	/* ������й����������� */
	CCArray* m_monsterMgrPosList;

	/* ������й�������б� */
	CCArray* m_monsterMgrList;

	/* ���������ҵ��Ѿ����ڵĹ���������� */
	//MonsterPos* findExistMonsterPos(CCPoint pos);
	MonsterPos* findExistMonsterPos(CCArray*  m_monsterPosList, CCPoint pos);

	/* �������꣬���ɹ���������� */
	//void createMonsterPos(CCPoint pos);
	void createMonsterPos(CCArray*  m_monsterPosList, CCPoint pos);

	/* ���������������ɾ������������� */
	//void deleteMonsterPos(MonsterPos* existPos);
	void deleteMonsterPos(CCArray*  m_monsterPosList, MonsterPos* existPos);
};

#endif