/*
    �ļ�����    Entity.h
    �衡����    ʵ�����
    
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

    /* ������ */
    void hurtMe(int iHurtValue);

	/* �Ƿ����� */
    bool isDead();

	/* ��ȡ��ײ��Χ */
    CCRect boundingBox();

    virtual void onExit();
protected:
    /* ʵ������ʱ���� */
    virtual void onDead();

	/* �󶨾������ʱ���� */
	virtual void onBindSprite();

	/* ���˺�ʱ���� */
	virtual void onHurt(int iHurtValue);
private:
    CCSprite* m_sprite;

	CC_SYNTHESIZE(int, m_ID, ID);	// ʵ��ID
	CC_SYNTHESIZE(int, m_iModelID, iModelID);	// ģ��ID����ԴID��
	CC_SYNTHESIZE_RETAIN(CCString*, m_sName, sName);	// ����
    CC_SYNTHESIZE(int, m_iHP, iHP);             // HP
    CC_SYNTHESIZE(int, m_iDefense, iDefense);   // ����
    CC_SYNTHESIZE(int, m_iSpeed, iSpeed);       // �ƶ��ٶ�
    CC_SYNTHESIZE(int, m_iLevel, iLevel);   // �ȼ�
	bool m_isDead;      // ����Ƿ�����
};

#endif