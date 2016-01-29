#include "TowerOprBtns.h"
#include "Hero.h"
#include "cocos-ext.h"
#include "GlobalSetting/GlobalPath.h"
#include "GlobalSetting/GlobalParam.h"
#include "GameWidget/GWRoundOprBtn.h"
#include "TowerPos.h"
#include "TowerBorder.h"
#include "FileLoad\I18N.h"

TowerOprBtns::TowerOprBtns() {
    m_hero = NULL;
}

TowerOprBtns::~TowerOprBtns() {
    CC_SAFE_RELEASE(m_hero);
}

TowerOprBtns* TowerOprBtns::create( TowerBorder* towerBorder, Hero* hero ) {
    TowerOprBtns* oprBtns = new TowerOprBtns();

    if(oprBtns && oprBtns->init(towerBorder, hero)) {
        oprBtns->autorelease();
    }
    else {
        CC_SAFE_DELETE(oprBtns);
    }

    return oprBtns;
}

bool TowerOprBtns::init( TowerBorder* towerBorder, Hero* hero ) {
    bool bRet = false;

    do {
        CC_SAFE_RETAIN(hero);
        this->m_hero = hero;

		CC_SAFE_RETAIN(towerBorder);
		this->m_towerBorder = towerBorder;

        /* 创建操作按钮 */
        createOprBtns();
        bRet = true;
    } while (0);

    return bRet;
}

const char* TowerOprBtns::replaceWithI18N(CCString* src)
{
	CCString* dst = CCString::create("");
	/* 判断是否要从配置文件中获取字符串 */
	dst->m_sString = src->m_sString.substr(0, 1);
	if(dst->m_sString.compare("@") == 0) {
		src->m_sString = src->m_sString.substr(1, src->length());
		
		int strKey = src->intValue();

		return I18N::shareI18N()->getcStringByKey(strKey);
	}
	else {
		return src->getCString();
	}
}

void TowerOprBtns::createOprBtns() {
	CCSize btnSize = CCSize(100, 50);

	

	CCLabelTTF* title = CCLabelTTF::create(replaceWithI18N(CCString::create("@51")), PATH_FONT_PUBLIC, GlobalParam::PublicFontSize);

    CCControlButton* closeBtn = CCControlButton::create(title, CCScale9Sprite::create("tollgate/opr_btn_nor.png"));
    closeBtn->setBackgroundSpriteForState(CCScale9Sprite::create("tollgate/opr_btn_light.png"), CCControlStateHighlighted);
	closeBtn->setPreferredSize(btnSize);
	closeBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(TowerOprBtns::closeEvent), CCControlEventTouchUpInside);

    title = CCLabelTTF::create(replaceWithI18N(CCString::create("@52")), PATH_FONT_PUBLIC, GlobalParam::PublicFontSize);
    CCControlButton* deleteBtn = CCControlButton::create(title, CCScale9Sprite::create("tollgate/opr_btn_nor.png"));
    deleteBtn->setBackgroundSpriteForState(CCScale9Sprite::create("tollgate/opr_btn_light.png"), CCControlStateHighlighted);
	deleteBtn->setPreferredSize(btnSize);
	deleteBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(TowerOprBtns::deleteEvent), CCControlEventTouchUpInside);

    title = CCLabelTTF::create(replaceWithI18N(CCString::create("@53")), PATH_FONT_PUBLIC, GlobalParam::PublicFontSize);
    CCControlButton* upgradeBtn = CCControlButton::create(title, CCScale9Sprite::create("tollgate/opr_btn_nor.png"));
    upgradeBtn->setBackgroundSpriteForState(CCScale9Sprite::create("tollgate/opr_btn_light.png"), CCControlStateHighlighted);
	upgradeBtn->setPreferredSize(btnSize);
	upgradeBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(TowerOprBtns::upgradeEvent), CCControlEventTouchUpInside);

    title = CCLabelTTF::create(replaceWithI18N(CCString::create("@54")), PATH_FONT_PUBLIC, GlobalParam::PublicFontSize);
    CCControlButton* detailBtn = CCControlButton::create(title, CCScale9Sprite::create("tollgate/opr_btn_nor.png"));
    detailBtn->setBackgroundSpriteForState(CCScale9Sprite::create("tollgate/opr_btn_light.png"), CCControlStateHighlighted);
	detailBtn->setPreferredSize(btnSize);
	detailBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(TowerOprBtns::detailEvent), CCControlEventTouchUpInside);

    m_roundOprBtn = GWRoundOprBtn::createWithControlButtons(upgradeBtn, detailBtn, deleteBtn, closeBtn);
    this->addChild(m_roundOprBtn);
}

void TowerOprBtns::closeEvent( CCObject* pSender, CCControlEvent event ) {
	m_towerBorder->deleteOprBtns();
}

void TowerOprBtns::upgradeEvent( CCObject* pSender, CCControlEvent event ) {
	m_hero->upgrade();
    m_towerBorder->deleteOprBtns();
}

void TowerOprBtns::detailEvent( CCObject* pSender, CCControlEvent event ) {

	
    CCString* s1 = CCString::createWithFormat("%d",m_hero->getiLevel());
    NOTIFY->postNotification("curLevelShow", s1);
	
	CCString* s2 = CCString::createWithFormat("%d",m_hero->getiCurAtk());
    NOTIFY->postNotification("curATKShow", s2);
	
	CCString* s3 = CCString::createWithFormat("%d",m_hero->getiAtkSpeed());
    NOTIFY->postNotification("curSpeedShow", s3);
	
	CCString* s4 = CCString::createWithFormat("%d",m_hero->getiAtkRange());
    NOTIFY->postNotification("curRangeShow", s4);

	m_towerBorder->deleteOprBtns();
}

void TowerOprBtns::deleteEvent( CCObject* pSender, CCControlEvent event ) {
	m_towerBorder->deleteHero();
    m_towerBorder->deleteOprBtns();
}

void TowerOprBtns::deleteMe() {
	m_roundOprBtn->deleteMe();
	this->removeAllChildrenWithCleanup(true);
}
