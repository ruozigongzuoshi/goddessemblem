/*
    �ļ�����    Hero.h
    �衡����    Ӣ�ۣ����£�
   
*/
#ifndef _Hero_H_
#define _Hero_H_

#include "Entity.h"
#include "EnumHeroType.h"

class Monster;
class BulletManager;
class Hero : public Entity {
public:
	Hero();
	~Hero();

	static Hero* create(CCSprite* sprite);
	bool init(CCSprite* sprite);

	/* ����Ӣ��ID���������ļ��ж�ȡӢ������ */
	static Hero* createFromCsvFileByID(int iHeroID);
	bool initFromCsvFileByID(int iHeroID);

	//virtual void draw();

	CC_SYNTHESIZE(EnumHeroType, m_heroType, HeroType);		// Ӣ������
	CC_SYNTHESIZE(int, m_iBaseAtk, iBaseAtk);				// ����������
	CC_SYNTHESIZE(int, m_iCurAtk, iCurAtk);					// ��ǰ������
	CC_SYNTHESIZE(int, m_iAtkSpeed, iAtkSpeed);				// �����������λ�����룩
	CC_SYNTHESIZE(int, m_iAtkRange, iAtkRange);				// ������Χ���뾶��
	CC_SYNTHESIZE(int, m_iUpgradeCostBase, iUpgradeCostBase);				// �������Ļ���ֵ
	CC_SYNTHESIZE(float, m_fUpgradeAtkBase, fUpgradeAtkBase);	// ���������ӳ�ϵ��

    //void setShowRange(bool isShowRange);

    /* ����Ӣ�� */
    void upgrade();
protected:
private:
    /* �����Ƿ���ȴ */
    bool m_isAtkCoolDown;

//     /* �Ƿ���ʾ������Χ */
//     bool m_isShowRange;

	/* ��ǰ�����Ĺ��� */
	Monster* m_atkMonster;

	/* �ӵ������� */
	BulletManager* m_bulletMgr;

	/* ����Ҫ�����Ĺ��� */
	void chooseAtkMonster(Monster* monster);

	/* �����뿪������Χ */
	void missAtkMonster();

	/* ��Ⲣѡ����빥����Χ�Ĺ�����߹����ѽ��뷶Χ�Ĺ��� */
	void checkAtkMonster(float ft);

	/* �ж������Ƿ��ڹ�����Χ�� */
	bool isInAtkRange(CCPoint pos);

    /* ������ȴ���� */
    void atkCoolDownEnd(float dt);

	/* ����Ŀ�� */
	void atk();

	/* ���Ŀ���Ƿ��뿪������Χ */
	void checkAimIsOutOfRange(CCArray* monsterList);

	/* ѡ��һ������Ŀ�� */
	void chooseAim(CCArray* monsterList);
};

#endif