/*
    �ļ�����    Monster.h
    �衡����    �������
    
*/
#ifndef _Monster_H_
#define _Monster_H_

#include "Entity.h"

#define MONSTER_SPEED_INIT 1

class ControllerSimpleMove;
class WidgetHPSlot;
class Monster : public Entity {
public:
    Monster();
    ~Monster();
    CREATE_FUNC(Monster);
    virtual bool init();

    /* ��������ID���������ļ��ж�ȡ�������� */
    static Monster* createFromCsvFileByID(int iMonsterID);
    bool initFromCsvFileByID(int iMonsterID);
public:
    /* ���ո�����������ƶ� */
    void moveByPosList(CCArray* posList);

protected:
	virtual void onDead();
	virtual void onBindSprite();
	virtual void onHurt(int iHurtValue);
private:
	ControllerSimpleMove* m_moveController;	    // �ƶ�������
	WidgetHPSlot* m_hpSlot;	// Ѫ����
 
    CC_SYNTHESIZE(int, m_iLevel, iLevel);       // �ȼ�
    CC_SYNTHESIZE(float, m_fShowTime, fShowTime);   // �����������

    void moveEnd(CCObject* pSender);

	CC_SYNTHESIZE(bool, m_isMoveEnd, isMoveEnd);       // �Ƿ�ﵽĿ�ĵ�
};

#endif