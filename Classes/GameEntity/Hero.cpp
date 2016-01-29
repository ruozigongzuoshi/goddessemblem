#include "Hero.h"
#include "FileLoad/CsvUtil.h"
#include "GlobalSetting/GlobalPath.h"
#include "GameScene/TollgateScene.h"
#include "GameScene/TollgateMapLayer.h"
#include "GlobalSetting/GlobalDefine.h"
#include "EnumHeroPropConfType.h"
#include "GlobalSetting/GlobalClient.h"
#include "Monster.h"
#include "BulletBase.h"
#include "BulletManager.h"
#include "GameScene/TollgateDataLayer.h"
#include "EnumMsgDataKey.h"
#include "GameScene/TollgateDataLayer.h"

Hero::Hero() {
 	m_atkMonster = NULL;
 	m_bulletMgr = NULL;
     m_isAtkCoolDown = false;
//     m_isShowRange = false;
}

Hero::~Hero() {
	CC_SAFE_RELEASE(m_atkMonster);
}

Hero* Hero::create( CCSprite* sprite ) {
	Hero* hero = new Hero();

	if(hero && hero->init(sprite)) {
		hero->autorelease();
	}
	else {
		CC_SAFE_DELETE(hero);
	}

	return hero;
}

bool Hero::init( CCSprite* sprite ) {
	bool bRet = false;

	do {
		CC_BREAK_IF(!sprite);

		bindSprite(sprite);

		/* 创建子弹管理器 */
        m_bulletMgr = BulletManager::create();
        CC_BREAK_IF(!m_bulletMgr);

        this->addChild(m_bulletMgr);
		bRet = true;
	} while (0);

	return bRet;
}

Hero* Hero::createFromCsvFileByID( int iHeroID ) {
	Hero* hero = new Hero();

	if(hero && hero->initFromCsvFileByID(iHeroID)) {
		hero->autorelease();
	}
	else {
		CC_SAFE_DELETE(hero);
	}

	return hero;
}

bool Hero::initFromCsvFileByID( int iHeroID ) {
	bool bRet = false;

	do {
		CsvUtil* csvUtil = CsvUtil::sharedCsvUtil();
		CCSize csvSize = csvUtil->getFileRowColNum(PATH_CSV_HERO_CONF);

		 const char* chHeroID = CCString::createWithFormat("%d", iHeroID)->getCString();

		/* 寻找ID所在的行 */
		int iLine = csvUtil->findValueInWithLine(chHeroID, enHeroPropConf_ID, PATH_CSV_HERO_CONF);

		CC_BREAK_IF(iLine < 0);

		setID(iHeroID);
		setiModelID(csvUtil->getInt(iLine, enHeroPropConf_ModelID, PATH_CSV_HERO_CONF));
		setiBaseAtk(csvUtil->getInt(iLine, enHeroPropConf_BaseAtk, PATH_CSV_HERO_CONF));
		setiCurAtk(getiBaseAtk());
		setiAtkSpeed(csvUtil->getInt(iLine, enHeroPropConf_AtkSpeed, PATH_CSV_HERO_CONF));
		setiAtkRange(csvUtil->getInt(iLine, enHeroPropConf_AtkRange, PATH_CSV_HERO_CONF));
		setiUpgradeCostBase(csvUtil->getInt(iLine, enHeroPropConf_UpgradeCostBase, PATH_CSV_HERO_CONF));
		setfUpgradeAtkBase(csvUtil->getFloat(iLine, enHeroPropConf_UpgradeAtkBase, PATH_CSV_HERO_CONF));

		CCSprite* sprite = CCSprite::create(CCString::createWithFormat(PATH_CSV_GODDESS_HEAD_PNG, m_iModelID)->getCString());
		CC_BREAK_IF(!sprite);

		CC_BREAK_IF(!init(sprite));


		this->schedule(schedule_selector(Hero::checkAtkMonster), 0.3f);

		bRet = true;
	} while (0);

	return bRet;
}

void Hero::checkAtkMonster(float ft) {
	/* 获取关卡地图Layer */
	TollgateScene* scene = (TollgateScene*)GlobalClient::sharedGlobalClient()->getCurTollgateScene();
	TollgateMapLayer* layer =  (TollgateMapLayer*)scene->getChildByTag(TAG_MAP_LAYER);

	/* 获取关卡中已出场的怪物列表 */
	CCArray* monsterList = layer->getMonsterList();

	if(m_atkMonster != NULL) {
        /* 怪物已死亡 */
        if(m_atkMonster->isDead()) {
			/* 从怪物列表中删除怪物 */
            monsterList->removeObject(m_atkMonster);

			/* 清除锁定的怪物引用 */
            CC_SAFE_RELEASE_NULL(m_atkMonster);
            return;
        }
		/* 攻击冷却结束，可以攻击 */
        if(m_isAtkCoolDown == false) {
			atk();
        }

		/* 判断怪物是否离开攻击范围 */
		checkAimIsOutOfRange(monsterList);
	}
	else {
		/* 选择一个进入攻击范围的怪物 */
		chooseAim(monsterList);
	}
}

void Hero::atk() {
	/* 从子弹管理器中取出一个未被使用的子弹对象 */
	BulletBase* bullet = m_bulletMgr->getAnyUnUsedBullet();
	if(bullet != NULL) {
		/* 根据英雄情况设置子弹属性，锁定攻击目标 */
		bullet->setPosition(getPosition());
		bullet->setiAtkValue(getiCurAtk());
		bullet->lockAim(m_atkMonster);

		/* 标记攻击冷却 */
		m_isAtkCoolDown = true;

		/* 英雄攻击有间隔时间，指定若干秒后恢复攻击 */
		this->scheduleOnce(schedule_selector(Hero::atkCoolDownEnd), getiAtkSpeed() / 1000.0f);
	}
}

void Hero::atkCoolDownEnd( float dt ) {
	m_isAtkCoolDown = false;
}

void Hero::checkAimIsOutOfRange(CCArray* monsterList) {
	if(m_atkMonster != NULL) {
		if(isInAtkRange(m_atkMonster->getPosition()) == false) {
			CCLOG("Out of Range!!!");
			missAtkMonster();
		}
	}
}

void Hero::missAtkMonster() {
	CC_SAFE_RELEASE_NULL(m_atkMonster);
}

void Hero::chooseAim( CCArray* monsterList ) {
	CCObject* obj = NULL;
	Monster* monster = NULL;
	CCARRAY_FOREACH(monsterList, obj) {
		monster = dynamic_cast<Monster*>(obj);

		if(monster != NULL) {
			if(isInAtkRange(monster->getPosition())) {
				CCLOG("InAtkRange!!!");
				chooseAtkMonster(monster);
				break;
			}
		}
	}
}

bool Hero::isInAtkRange( CCPoint pos ) {
	int iDoubleAtkRange = getiAtkRange();	// 攻击范围
	CCPoint heroPos = getPosition();

	float length = ccpDistanceSQ(pos, heroPos);

	if(length <= iDoubleAtkRange * iDoubleAtkRange) {
		return true;
	}

	return false;
}

void Hero::chooseAtkMonster( Monster* monster ) {
	CC_SAFE_RELEASE(m_atkMonster);
	CC_SAFE_RETAIN(monster);
	m_atkMonster = monster;
}


// void Hero::draw() {
//     if(m_isShowRange) {
//         ccDrawColor4B(200, 50, 50, 255);
// 
// 	    /* 绘制以自身为起点 */
// 	    ccDrawCircle(CCPointZero, getiAtkRange(), 1, 20, false);
// 
// 	    ccDrawColor4B(255,255,255,255);
//     }
// }

void Hero::upgrade() {
    CCSprite* sprite = getSprite();
	if(sprite == NULL || m_iLevel >= 4) {
        return;
    }

	/* 判断塔魂是否足够 */
	TollgateDataLayer* dataLayer = (TollgateDataLayer*)GlobalClient::sharedGlobalClient()->getCurTollgateScene()->getChildByTag(TAG_DATA_LAYER);
	int iCurMagicNum = dataLayer->getiTowerSoulNum();

	if(iCurMagicNum < m_iUpgradeCostBase * m_iLevel) {
		return;
	}

	/* 发布消息，扣除塔魂 */
	CCDictionary* dict = CCDictionary::create();
	dict->setObject(CCInteger::create(-m_iUpgradeCostBase * m_iLevel), enMsgDataKey_TowerSoulAltNum);
	NOTIFY->postNotification("TowerSoulChange", dict);

	/* 增加等级 */
    m_iLevel++;

    /* 英雄遮罩 */
    if(m_iLevel == 2) {
        CCSprite* heroTop = CCSprite::create("sprite/hero/hero_top_1.png");
        CCPoint pos = ccp(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2);
        heroTop->setPosition(pos);
        sprite->addChild(heroTop);
    }
	if(m_iLevel == 3) {
		CCSprite* heroTop = CCSprite::create("sprite/hero/hero_top_2.png");
		heroTop->setOpacity(255);
		CCPoint pos = ccp(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2);
		heroTop->setPosition(pos);
		sprite->addChild(heroTop);

		CCActionInterval* rotateBy = CCRotateBy::create(25.0f, 360, 360);
		CCActionInterval* repeat = CCRepeatForever::create(rotateBy);
		heroTop->runAction(repeat);
	}
	if(m_iLevel == 4) {
		CCPoint pos = ccp(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2);
		CCSprite* heroTop = CCSprite::create("sprite/hero/hero_top_3.png");
		heroTop->setPosition(pos);
		sprite->addChild(heroTop);

		CCActionInterval* rotateBy = CCRotateBy::create(10.0f, 360, 360);
		CCActionInterval* repeat = CCRepeatForever::create(rotateBy);
		heroTop->runAction(repeat);
	}

	/* 增加英雄攻击力 */
	setiBaseAtk(getiBaseAtk() * m_fUpgradeAtkBase);
	setiCurAtk(getiBaseAtk());
}

// void Hero::setShowRange( bool isShowRange ) {
//     m_isShowRange = isShowRange;
// }
