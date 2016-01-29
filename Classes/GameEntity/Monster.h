/*
    文件名：    Monster.h
    描　述：    怪物基类
    
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

    /* 给定怪物ID，从配置文件中读取怪物数据 */
    static Monster* createFromCsvFileByID(int iMonsterID);
    bool initFromCsvFileByID(int iMonsterID);
public:
    /* 按照给定的坐标点移动 */
    void moveByPosList(CCArray* posList);

protected:
	virtual void onDead();
	virtual void onBindSprite();
	virtual void onHurt(int iHurtValue);
private:
	ControllerSimpleMove* m_moveController;	    // 移动控制器
	WidgetHPSlot* m_hpSlot;	// 血量条
 
    CC_SYNTHESIZE(int, m_iLevel, iLevel);       // 等级
    CC_SYNTHESIZE(float, m_fShowTime, fShowTime);   // 出场间隔：秒

    void moveEnd(CCObject* pSender);

	CC_SYNTHESIZE(bool, m_isMoveEnd, isMoveEnd);       // 是否达到目的地
};

#endif