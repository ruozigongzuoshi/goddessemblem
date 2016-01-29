#include "BulletManager.h"
#include "BulletBase.h"
#include "BulletNormal.h"
#include "GameScene/TollgateMapLayer.h"
#include "GlobalSetting/GlobalClient.h"
#include "GameScene/TollgateScene.h"

BulletManager::BulletManager() {
    m_bulletList = NULL;
}

BulletManager::~BulletManager() {
    CC_SAFE_RELEASE(m_bulletList);
}

BulletManager* BulletManager::create() {
    BulletManager* bulletMgr = new BulletManager();

    if(bulletMgr && bulletMgr->init()) {
        bulletMgr->autorelease();
    }
    else {
        CC_SAFE_DELETE(bulletMgr);
    }

    return bulletMgr;
}

bool BulletManager::init() {
    bool bRet = false;

    do {
        CCNode* parent = GlobalClient::sharedGlobalClient()->getCurTollgateScene()->getChildByTag(TAG_MAP_LAYER);

        CC_BREAK_IF(!parent);

        /* 创建子弹对象 */
        createBullets(parent);

        /* 循环检测子弹逻辑 */
        this->schedule(schedule_selector(BulletManager::bulletLogicCheck), BULLET_LOGIC_CHECK_INTERVAL);

        bRet = true;
    } while (0);

    return bRet;
}

void BulletManager::createBullets(CCNode* parent) {
    CC_SAFE_RELEASE(m_bulletList);
    m_bulletList = CCArray::createWithCapacity(BULLET_MAX_CACHE_NUM);
    CC_SAFE_RETAIN(m_bulletList);

    BulletBase* bullet = NULL;
    for(int i = 0; i < BULLET_MAX_CACHE_NUM; i++) {
        bullet = BulletNormal::create();

        bullet->setUsed(false);
        m_bulletList->addObject(bullet);
        parent->addChild(bullet, BULLET_LAYER_LVL);
    }
}

void BulletManager::onExit() {
    this->unscheduleAllSelectors();
}

void BulletManager::bulletLogicCheck( float dt ) {
    BulletBase* bullet = NULL;
    Entity* aim = NULL;

    CCObject* obj = NULL;
    CCARRAY_FOREACH(m_bulletList, obj) {
        bullet = dynamic_cast<BulletBase*>(obj);

        if(bullet != NULL && bullet->isUsed()) {
            aim = bullet->getAim();

            if(aim != NULL) {
                /* 判断子弹是否到达了目标处，是的话，伤害目标（子弹使用CCMoveTo移动） */
                if(bullet->isArrive()) {
                    aim->hurtMe(bullet->getiAtkValue());

                    /* 子弹攻击目标后，重置为未使用状态 */
                    bullet->setUsed(false);
                }
            }
        }
    }
}

BulletBase* BulletManager::getAnyUnUsedBullet() {
    BulletBase* bullet = NULL;

    CCObject* obj = NULL;
    CCARRAY_FOREACH(m_bulletList, obj) {
        bullet = dynamic_cast<BulletBase*>(obj);

        if(bullet != NULL && bullet->isUsed() == false) {
            bullet->setUsed(true);
            return bullet;
        }
    }

    return NULL;
}