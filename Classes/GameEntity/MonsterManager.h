/*
    �ļ�����    MonsterManager.h
    �衡����    ���������
    
*/
#ifndef _MonsterManager_H_
#define _MonsterManager_H_

#include "cocos2d.h"
USING_NS_CC;

class MonsterPos;
class MonsterManager : public CCNode {
public:
	MonsterManager();
	~MonsterManager();
	static MonsterManager* createWithLevel(int iCurLevel, int num);
	bool initWithLevel(int iCurLevel, int num);

	/* ��ȡ�����ļ��������� */
	void createMonsters(int iCurLevel, int num);

	/* ��ȡ��û�г����Ĺ������� */
	int getNotShowMonsterCount();

	/* ��ȡ����������� */
	MonsterPos* getMonsterStartPos();

	/* ��ȡ�����յ����� */
	MonsterPos* getMonsterEndPos();

	/* ��ȡ�����б� */
	CCArray* getMonsterList();
private:
	/* δ�����Ĺ����б� */
	CCArray* m_notShowMonsterList;

	/* ������й����������� */
	CCArray* m_monsterPosList;

	/* �����б� */
	CCArray* m_monsterList;

	/* ���ڼ���������ʱ�� */
	float m_fShowTimeCount;

	/* ����Ƿ����¹������ */
	void showMonster(float dt);

	/* �������߼����� */
	void logic(float dt);
};

#endif