/*
    �ļ�����    BulletManager.h
    �衡����    �ӵ�������
    
*/
#ifndef _BulletManager_H_
#define _BulletManager_H_

#include "cocos2d.h"
USING_NS_CC;

#define BULLET_MAX_CACHE_NUM 10   // �ӵ������������
#define BULLET_LOGIC_CHECK_INTERVAL 0.07f    // �ӵ��߼������

class BulletBase;
class BulletManager : public CCNode {
public:
    BulletManager();
    ~BulletManager();
    static BulletManager* create();
    bool init();

    virtual void onExit();

    /* �ӻ����л�ȡһ��δ��ʹ�õ��ӵ� */
    BulletBase* getAnyUnUsedBullet();
private:
    /* �ӵ��б� */
    CCArray* m_bulletList;

    /* ���������ӵ� */
    void createBullets(CCNode* parent);

    /* �ӵ��߼� */
    void bulletLogicCheck(float dt);
};

#endif