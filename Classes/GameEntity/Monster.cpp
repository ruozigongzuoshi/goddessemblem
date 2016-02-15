#include "Monster.h"
#include "ControllerSimpleMove.h"
#include "FileLoad/CsvUtil.h"
#include "GlobalSetting/GlobalPath.h"
#include "EnumMonsterPropConfType.h"
#include "GlobalSetting/GlobalDefine.h"
#include "GameScene/TollgateScene.h"
#include "GameScene/TollgateMapLayer.h"
#include "WidgetHPSlot.h"
#include "EnumMsgDataKey.h"
#include "GameEntity/FlowWord.h"

Monster::Monster() {
	m_moveController = NULL;
    m_iSpeed = MONSTER_SPEED_INIT;
	m_hpSlot = NULL;
	m_isMoveEnd = false;
}

Monster::~Monster() {
	CC_SAFE_RELEASE(m_hpSlot);
}

bool Monster::init() {
    bool bRet = false;

    do {
		m_moveController = ControllerSimpleMove::create(this, SEL_CallFuncM(&Monster::moveEnd));
		//m_moveController = ControllerSimpleMove::create(this);

		/* 节点必须添加到场景中才能被调用update函数（怪物对象会被添加到场景中，其子对象也能被调用update函数） */
		this->addChild(m_moveController);
        bRet = true;
    } while (0);

    return bRet;
}

Monster* Monster::createFromCsvFileByID( int iMonsterID ) {
    Monster* monster = new Monster();

    if(monster && monster->initFromCsvFileByID(iMonsterID)) {
        monster->autorelease();
    }
    else {
        CC_SAFE_DELETE(monster);
    }

    return monster;
}

bool Monster::initFromCsvFileByID( int iMonsterID ) {
    bool bRet = false;

    do {
        CsvUtil* csvUtil = CsvUtil::sharedCsvUtil();
        CCSize csvSize = csvUtil->getFileRowColNum(PATH_CSV_MONSTER_CONF);

        const char* chMonsterID = CCString::createWithFormat("%d", iMonsterID)->getCString();

        /* 寻找ID所在的行 */
        int iLine = csvUtil->findValueInWithLine(chMonsterID, enMonsterPropConf_ID, PATH_CSV_MONSTER_CONF);

        CC_BREAK_IF(iLine < 0);

        setID(iMonsterID);
        setiLevel(csvUtil->getInt(iLine, enMonsterPropConf_Level, PATH_CSV_MONSTER_CONF));
        setiModelID(csvUtil->getInt(iLine, enMonsterPropConf_ModelID, PATH_CSV_MONSTER_CONF));
        setiDefense(csvUtil->getInt(iLine, enMonsterPropConf_Defense, PATH_CSV_MONSTER_CONF));
        setiHP(csvUtil->getInt(iLine, enMonsterPropConf_Hp, PATH_CSV_MONSTER_CONF));
        setiSpeed(csvUtil->getInt(iLine, enMonsterPropConf_Speed, PATH_CSV_MONSTER_CONF));

        CC_BREAK_IF(!init());

        bRet = true;
    } while (0);

    return bRet;
}

void Monster::moveByPosList( CCArray* posList ) {
    if(posList == NULL || posList->count() < 1) {
        return;
    }
	m_moveController->moveByPosList(posList, 2, getiSpeed());
}

void Monster::onDead() {
    CCLOG("Monster::onDead");
    this->removeFromParentAndCleanup(true);

    /* 发布怪物死亡消息 */
    NOTIFY->postNotification("MonsterDead");
}

void Monster::onBindSprite() {
	if(m_hpSlot == NULL) {
		CCPoint pos = getPosition();
		m_hpSlot = WidgetHPSlot::create(this);
		m_hpSlot->setPosition(pos.x, pos.y + getSprite()->getContentSize().height / 2);
		m_hpSlot->getSlider()->setMaximumValue(getiHP());
		m_hpSlot->getSlider()->setMinimumValue(0);
		m_hpSlot->getSlider()->setValue(getiHP());
		this->addChild(m_hpSlot);
	}
}

void Monster::onHurt( int iHurtValue ) {
	if(m_hpSlot != NULL) {
		/* 扣血飘字特效 */
		FlowWord* flowWord = FlowWord::create();
		this->addChild(flowWord);
		const char* sHurtValue = CCString::createWithFormat("-%d",iHurtValue)->getCString();
		flowWord->showWord(sHurtValue, getSprite()->getPosition());

		int iCurValue = m_hpSlot->getSlider()->getValue();

		iCurValue -= iHurtValue;
		if(iCurValue < 0) {
			iCurValue = 0;
		}
		m_hpSlot->getSlider()->setValue(iCurValue);
	}
}

void Monster::moveEnd(CCObject* pSender) {
    removeFromParentAndCleanup(true);

	/* 发布扣除魔力消息 */
	CCDictionary* dict = CCDictionary::create();
		 
	dict->setObject(CCInteger::create(-10), enMsgDataKey_MagicAltNum);
	NOTIFY->postNotification("MagicChange", dict);

	/* 设置状态为达到目的地 */
	m_isMoveEnd = true;
	m_isDead = true;
}
