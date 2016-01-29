/*
    文件名：    BulletBase.h
    描　述：    子弹基类
    
*/
#ifndef _BulletBase_H_
#define _BulletBase_H_

#include "Entity.h"

/* 子弹速度 */
#define SPEED_DEFAULT 10
#define SPEED_NORMAL 5

class BulletBase : public Entity {
public:
    BulletBase();
    ~BulletBase();

    /* 锁定攻击目标 */
    void lockAim(Entity* entity);

    /* 获取攻击目标 */
    Entity* getAim();

	/* 是否正在使用 */
    void setUsed(bool isUsed);
    bool isUsed();

	/* 是否到达目标 */
    bool isArrive();

protected:
    /* 锁定攻击目标时调用，留给子类做处理 */
    virtual void onLockAim(Entity* aim) = 0;   

    bool m_isArrive;  // 是否达到了攻击目标（是否攻击了目标）
private:
    bool m_isUsed;    // 标记是否已经在使用中
    Entity* m_aim;	// 攻击目标

    CC_SYNTHESIZE(int, m_iAtkValue, iAtkValue); // 攻击力
    CC_SYNTHESIZE(int, m_iSpeed, iSpeed);       // 速度
};

#endif