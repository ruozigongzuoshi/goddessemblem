/*
    文件名：    Hero.h
    描　述：    英雄（徽章）
   
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

	/* 给定英雄ID，从配置文件中读取英雄数据 */
	static Hero* createFromCsvFileByID(int iHeroID);
	bool initFromCsvFileByID(int iHeroID);

	//virtual void draw();

	CC_SYNTHESIZE(EnumHeroType, m_heroType, HeroType);		// 英雄类型
	CC_SYNTHESIZE(int, m_iBaseAtk, iBaseAtk);				// 基础攻击力
	CC_SYNTHESIZE(int, m_iCurAtk, iCurAtk);					// 当前攻击力
	CC_SYNTHESIZE(int, m_iAtkSpeed, iAtkSpeed);				// 攻击间隔（单位：毫秒）
	CC_SYNTHESIZE(int, m_iAtkRange, iAtkRange);				// 攻击范围（半径）
	CC_SYNTHESIZE(int, m_iUpgradeCostBase, iUpgradeCostBase);				// 升级消耗基础值
	CC_SYNTHESIZE(float, m_fUpgradeAtkBase, fUpgradeAtkBase);	// 升级攻击加成系数

    //void setShowRange(bool isShowRange);

    /* 升级英雄 */
    void upgrade();
protected:
private:
    /* 攻击是否冷却 */
    bool m_isAtkCoolDown;

//     /* 是否显示攻击范围 */
//     bool m_isShowRange;

	/* 当前锁定的怪物 */
	Monster* m_atkMonster;

	/* 子弹管理类 */
	BulletManager* m_bulletMgr;

	/* 锁定要攻击的怪物 */
	void chooseAtkMonster(Monster* monster);

	/* 怪物离开攻击范围 */
	void missAtkMonster();

	/* 检测并选择进入攻击范围的怪物，或者攻击已进入范围的怪物 */
	void checkAtkMonster(float ft);

	/* 判断坐标是否在攻击范围内 */
	bool isInAtkRange(CCPoint pos);

    /* 攻击冷却结束 */
    void atkCoolDownEnd(float dt);

	/* 攻击目标 */
	void atk();

	/* 检测目标是否离开攻击范围 */
	void checkAimIsOutOfRange(CCArray* monsterList);

	/* 选择一个攻击目标 */
	void chooseAim(CCArray* monsterList);
};

#endif