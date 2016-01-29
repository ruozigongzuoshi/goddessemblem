#include "TowerBorder.h"
#include "Hero.h"
#include "TowerOprBtns.h"

TowerBorder::TowerBorder() {
    m_iLevel = 1;

	m_hero = NULL;
	m_towerOprBtns = NULL;
}

TowerBorder::~TowerBorder() {
	CC_SAFE_RELEASE(m_hero);
	CC_SAFE_RELEASE(m_towerOprBtns);
}

bool TowerBorder::init() {
    return true;
}

void TowerBorder::upgrade() {
    if(getSprite() != NULL) {
        getSprite()->stopAllActions();
    }

    CCString* sFilePath = CCString::createWithFormat("sprite/hero/border_%d.png", m_iLevel);
    CCSprite* sprite = CCSprite::create(sFilePath->getCString());

    bindSprite(sprite);

    m_iLevel++;

    if(m_iLevel == 2) {
        CCActionInterval* rotateBy = CCRotateBy::create(25.0f, 360, 360);
        CCActionInterval* repeat = CCRepeatForever::create(rotateBy);

        sFilePath = CCString::createWithFormat("sprite/hero/magic_border_%d.png", m_iLevel);
        sprite = CCSprite::create(sFilePath->getCString());
        sprite->setOpacity(80);
        sprite->runAction(repeat);
        this->addChild(sprite, 10);

    }
}
bool TowerBorder::isClickMe( CCPoint pos ) {
	CCSize size = getSprite()->getContentSize();
	CCPoint borderPos = getPosition();

	CCPoint srcPos = CCPoint(borderPos.x - size.width, borderPos.y + size.height);
	CCPoint destPos = CCPoint(borderPos.x + size.width, borderPos.y - size.height);

	if(pos.x >= srcPos.x && pos.x <= destPos.x && pos.y <= srcPos.y && pos.y >= destPos.y) {
		return true;
	}

	return false;
}

void TowerBorder::bindHero( Hero* hero ) {
	CC_SAFE_RELEASE(m_hero);
	CC_SAFE_RETAIN(hero);

	m_hero = hero;
}

Hero* TowerBorder::getHero() {
	return m_hero;
}

void TowerBorder::deleteHero() {
	m_hero->removeFromParentAndCleanup(true);
	CC_SAFE_RELEASE_NULL(m_hero);
}

void TowerBorder::showTowerOprBtns() {
	deleteOprBtns();

	TowerOprBtns* operBtns = TowerOprBtns::create(this, m_hero);
	operBtns->setPosition(ccp(0, 0));
	this->addChild(operBtns);

	CC_SAFE_RETAIN(operBtns);
	this->m_towerOprBtns = operBtns;
}

void TowerBorder::deleteOprBtns() {
	if(m_towerOprBtns != NULL) {
		m_towerOprBtns->deleteMe();
		CC_SAFE_RELEASE_NULL(m_towerOprBtns);
	}
}
