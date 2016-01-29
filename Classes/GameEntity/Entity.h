/*
    文件名：    Entity.h
    描　述：    实体基类
    
*/

#ifndef _Entity_H_
#define _Entity_H_

#include "cocos2d.h"
USING_NS_CC;

class Entity : public CCNode {
public:
    Entity();
    ~Entity();

    void bindSprite(CCSprite* sprite);
    CCSprite* getSprite();

    /* 被攻击 */
    void hurtMe(int iHurtValue);

	/* 是否死亡 */
    bool isDead();

	/* 获取碰撞范围 */
    CCRect boundingBox();

    virtual void onExit();
protected:
    /* 实体死亡时调用 */
    virtual void onDead();

	/* 绑定精灵对象时调用 */
	virtual void onBindSprite();

	/* 受伤害时调用 */
	virtual void onHurt(int iHurtValue);
private:
    CCSprite* m_sprite;

	CC_SYNTHESIZE(int, m_ID, ID);	// 实体ID
	CC_SYNTHESIZE(int, m_iModelID, iModelID);	// 模型ID（资源ID）
	CC_SYNTHESIZE_RETAIN(CCString*, m_sName, sName);	// 名字
    CC_SYNTHESIZE(int, m_iHP, iHP);             // HP
    CC_SYNTHESIZE(int, m_iDefense, iDefense);   // 防御
    CC_SYNTHESIZE(int, m_iSpeed, iSpeed);       // 移动速度
    CC_SYNTHESIZE(int, m_iLevel, iLevel);   // 等级
	bool m_isDead;      // 标记是否死亡
};

#endif