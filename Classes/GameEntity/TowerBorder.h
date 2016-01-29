/*
    �ļ�����    TowerBorder.h
    �衡����    ��̨
    
*/
#ifndef _TowerBorder_H_
#define _TowerBorder_H_

#include "Entity.h"

class Hero;
class TowerOprBtns;
class TowerBorder : public Entity {
public:
    TowerBorder();
    ~TowerBorder();

    CREATE_FUNC(TowerBorder);
    virtual bool init();

    /* ���� */
    void upgrade();

	/* �ж������Ƿ���뷶Χ */
	bool isClickMe(CCPoint pos);

	/* ��Ӣ�۶��� */
	void bindHero(Hero* hero);

	/* ��ȡӢ�۶��� */
	Hero* getHero();

	/* ɾ��Ӣ�۶��� */
	void deleteHero();

	/* ��ʾ������ť */
	void showTowerOprBtns();

	/* ɾ��������ť */
	void deleteOprBtns();
private:
	/* �󶨵��� */
	Hero* m_hero;

	/* ������ť */
	TowerOprBtns* m_towerOprBtns;
};

#endif