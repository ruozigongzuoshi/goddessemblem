/*
    文件名：    BulletManager.h
    描　述：    子弹管理器
    
*/
#ifndef _BulletManager_H_
#define _BulletManager_H_

#include "cocos2d.h"
USING_NS_CC;

#define BULLET_MAX_CACHE_NUM 10   // 子弹缓存最大数量
#define BULLET_LOGIC_CHECK_INTERVAL 0.07f    // 子弹逻辑检测间隔

class BulletBase;
class BulletManager : public CCNode {
public:
    BulletManager();
    ~BulletManager();
    static BulletManager* create();
    bool init();

    virtual void onExit();

    /* 从缓存中获取一个未被使用的子弹 */
    BulletBase* getAnyUnUsedBullet();
private:
    /* 子弹列表 */
    CCArray* m_bulletList;

    /* 创建缓存子弹 */
    void createBullets(CCNode* parent);

    /* 子弹逻辑 */
    void bulletLogicCheck(float dt);
};

#endif