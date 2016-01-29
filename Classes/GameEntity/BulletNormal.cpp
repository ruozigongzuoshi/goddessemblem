#include "BulletNormal.h"
#include "ControllerSimpleMove.h"
#include "GlobalSetting/GlobalPath.h"

BulletNormal::BulletNormal() {
	m_iSpeed = SPEED_NORMAL;
}

BulletNormal::~BulletNormal() {
	
}

BulletNormal* BulletNormal::create( CCSprite* sprite ) {
	BulletNormal* bulletNor = new BulletNormal();

	if(bulletNor && bulletNor->init(sprite)) {
		bulletNor->autorelease();
	}
	else {
		CC_SAFE_DELETE(bulletNor);
	}

	return bulletNor;
}

bool BulletNormal::init( CCSprite* sprite ) {
	bool bRet = false;

	do {
		bindSprite(sprite);
		bRet = true;
	} while (0);

	return bRet;
}

bool BulletNormal::init() {
	bool bRet = false;

	do {
		CCSprite* sprite = CCSprite::create(PATH_BULLET_NOR);
		CC_BREAK_IF(!sprite);

		CC_BREAK_IF(!init(sprite));

		bRet = true;
	} while (0);

	return bRet;
}

void BulletNormal::onLockAim( Entity* aim ) {
	CCLOG("onLockAim");
    m_isArrive = false;
    CCActionInterval* moveTo = CCMoveTo::create(0.5f, aim->getPosition());
    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(BulletNormal::moveEnd));

    CCActionInterval* actions = CCSequence::create(moveTo, callFunc, NULL);
    this->runAction(actions);
}

void BulletNormal::moveEnd() {
    m_isArrive = true;
}
