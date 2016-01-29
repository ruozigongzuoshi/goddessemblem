#include "BulletBase.h"

BulletBase::BulletBase() {
    m_isUsed = false;
    m_aim = NULL;
    m_iSpeed = SPEED_DEFAULT;
    m_iAtkValue = 1;
}

BulletBase::~BulletBase() {
    CC_SAFE_RELEASE(m_aim);
}

void BulletBase::setUsed( bool isUsed ) {
    this->m_isUsed = isUsed;

    setVisible(isUsed);
}

bool BulletBase::isUsed() {
    return this->m_isUsed;
}

void BulletBase::lockAim( Entity* entity ) {
    if(entity != NULL) {
        CC_SAFE_RETAIN(entity);
        CC_SAFE_RELEASE(m_aim);

        m_aim = entity;

		CCLOG("lockAim");
        onLockAim(m_aim);
    }
}

Entity* BulletBase::getAim() {
    return this->m_aim;
}

bool BulletBase::isArrive() {
    return m_isArrive;
}