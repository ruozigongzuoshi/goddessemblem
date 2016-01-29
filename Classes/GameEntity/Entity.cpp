#include "Entity.h"

Entity::Entity() {
    m_sprite = NULL;
    m_sName = CCString::create("");
    CC_SAFE_RETAIN(m_sName);
    m_iHP = 1;
    m_iDefense = 1;
    m_isDead = false;
    m_iSpeed = 1;
    m_iLevel = 1;
}

Entity::~Entity() {
}

void Entity::bindSprite( CCSprite* sprite ) {
    if(this->m_sprite != NULL) {
        m_sprite->removeFromParentAndCleanup(true);
    }

    this->m_sprite = sprite;
    this->addChild(m_sprite);

	onBindSprite();
}

CCSprite* Entity::getSprite() {
    return this->m_sprite;
}

void Entity::hurtMe( int iHurtValue ) { 
    if(m_isDead) {
        return;
    }
    CCLOG("hurtMe iHurtValue=%d, HP=%d", iHurtValue, getiHP());
    /* ��С�˺�ֵΪ1 */
    if(iHurtValue <= getiDefense()) {
        iHurtValue = 1;
    }

    int iCurHP = getiHP();      /* ��ǰHP */
    int iAfterHP = iCurHP - iHurtValue; /* ���������HP */

	onHurt(iHurtValue);

    if(iAfterHP > 0) {
        setiHP(iAfterHP);
    }
    else {
        CCLOG("onDead");
        m_isDead = true;
        /* ���� */
        onDead();
    }

}

void Entity::onExit() {
    this->unscheduleAllSelectors();
}


CCRect Entity::boundingBox() {
    if(getSprite() == NULL) {
        return CCRectMake(0, 0, 0, 0);
    }
    CCPoint pos = getPosition();
    CCSize size = getSprite()->getContentSize();

    return CCRectMake(pos.x, pos.y, size.width, size.height);
}

bool Entity::isDead() {
    return this->m_isDead;
}

void Entity::onDead() {
}

void Entity::onBindSprite() {
}

void Entity::onHurt( int iHurtValue ) {
}
