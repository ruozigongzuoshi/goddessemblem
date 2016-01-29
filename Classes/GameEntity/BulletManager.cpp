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

        /* �����ӵ����� */
        createBullets(parent);

        /* ѭ������ӵ��߼� */
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
                /* �ж��ӵ��Ƿ񵽴���Ŀ�괦���ǵĻ����˺�Ŀ�꣨�ӵ�ʹ��CCMoveTo�ƶ��� */
                if(bullet->isArrive()) {
                    aim->hurtMe(bullet->getiAtkValue());

                    /* �ӵ�����Ŀ�������Ϊδʹ��״̬ */
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