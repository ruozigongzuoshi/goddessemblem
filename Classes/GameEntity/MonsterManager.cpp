#include "MonsterManager.h"
#include "Monster.h"
#include "PosBase.h"
#include "GlobalSetting/GlobalDefine.h"
#include "PosLoadUtil.h"
#include "EnumPosType.h"
#include "MonsterPos.h"
#include "EnumMsgDataKey.h"

MonsterManager::MonsterManager() {
	m_monsterPosList = NULL;
	m_monsterList = NULL;
	m_notShowMonsterList = NULL;
	m_fShowTimeCount = 0;
}

MonsterManager::~MonsterManager() {
	CC_SAFE_RELEASE(m_monsterPosList);
	CC_SAFE_RELEASE(m_monsterList);
	CC_SAFE_RELEASE(m_notShowMonsterList);
}

MonsterManager* MonsterManager::createWithLevel( int iCurLevel, int num) {
	MonsterManager* monsterMgr = new MonsterManager();

	if(monsterMgr && monsterMgr->initWithLevel(iCurLevel, num)) {
		monsterMgr->autorelease();
	}
	else {
		CC_SAFE_DELETE(monsterMgr);
	}

	return monsterMgr;
}

bool MonsterManager::initWithLevel(int iCurLevel, int num) {
	bool bRet = false;

	do {
		/* 初始化怪物坐标列表 */
		m_monsterPosList = CCArray::create();
		CC_SAFE_RETAIN(m_monsterPosList);

		/* 初始化怪物列表 */
		m_monsterList = CCArray::create();
		CC_SAFE_RETAIN(m_monsterList);

		/* 创建怪物 */
		createMonsters(iCurLevel, num);
		bRet = true;
	} while (0);

	return bRet;
}

void MonsterManager::createMonsters(int iCurLevel, int num) {
	/* 加载怪物坐标对象 */
	CCString* sMonsterPosPath = CCString::createWithFormat("%smonsterPos_level_%d_%d.plist",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), iCurLevel, num);
	
	if(!CCFileUtils::sharedFileUtils()->isFileExist(sMonsterPosPath->getCString()))
	{
		sMonsterPosPath = CCString::createWithFormat("tollgate/monsterPos_level_%d_%d.plist", iCurLevel, num);
	}
	//CCString* sMonsterPosPath = CCString::createWithFormat("tollgate/monsterPos_level_%d_%d.plist", iCurLevel, num);
	CCArray* posList = PosLoadUtil::sharedPosLoadUtil()->loadPosWithFile(sMonsterPosPath->getCString(), enMonsterPos, this, 10, false);
	m_monsterPosList->addObjectsFromArray(posList);


	/* 读取配置文件 */
	CCString* sMonsterConfPath = CCString::createWithFormat("%smonster_level_%d_%d.plist",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), iCurLevel, num);
	
	if(!CCFileUtils::sharedFileUtils()->isFileExist(sMonsterConfPath->getCString()))
	{
		sMonsterConfPath = CCString::createWithFormat("tollgate/monster_level_%d_%d.plist", iCurLevel, num);
	}
	//CCString* sMonsterConfPath = CCString::createWithFormat("tollgate/monster_level_%d_%d.plist", iCurLevel, num);
	CCArray* confProsArr = CCArray::createWithContentsOfFile(sMonsterConfPath->getCString());

	/* 初始化未出场的怪物列表 */
	m_notShowMonsterList = CCArray::create();
	CC_SAFE_RETAIN(m_notShowMonsterList);

	/* 从怪物出场配置文件读取怪物ID和出场时间，保存所有怪物到未出场列表 */
	CCObject* obj = NULL;
	CCDictionary* dict = NULL;
	Monster* monster = NULL;
	CCString* id = 0;
	CCString* sShowTime = 0;
	CCARRAY_FOREACH(confProsArr, obj) {
		dict = dynamic_cast<CCDictionary*>(obj);

		id = dynamic_cast<CCString*>(dict->objectForKey("id"));
		sShowTime = dynamic_cast<CCString*>(dict->objectForKey("showTime"));

		if(id != NULL && sShowTime != NULL) {
			monster = Monster::createFromCsvFileByID(id->intValue());
			monster->setfShowTime(sShowTime->floatValue());
			monster->setVisible(false);
			monster->bindSprite(CCSprite::create(
				CCString::createWithFormat("sprite/monster/monster_%d.png", monster->getiModelID())->getCString()));
			m_monsterList->addObject(monster);
			m_notShowMonsterList->addObject(monster);
			this->addChild(monster);
		}
	}

	/* 检查是否有新怪物出场 */
	this->schedule(schedule_selector(MonsterManager::showMonster));

	/* 检查是否有怪物死亡 */
	this->schedule(schedule_selector(MonsterManager::logic), 0.2f);
}

void MonsterManager::showMonster( float dt ) {
	int iNotShowMonsterCount = m_notShowMonsterList->count();

	if(iNotShowMonsterCount > 0) {
		m_fShowTimeCount += dt;
	}
	
	/* 获取怪物的第一个坐标点 */
	PosBase* monsterFirstPos = getMonsterStartPos();

	CCObject* obj = NULL;
	Monster* monster = NULL;

	CCArray* monsterWantToDelete = CCArray::create();
	CCARRAY_FOREACH(m_notShowMonsterList, obj) {
		monster = dynamic_cast<Monster*>(obj);

		if(monster != NULL) {
			/* 时间达到怪物的出场时间，让怪物出场 */
			if(m_fShowTimeCount >= monster->getfShowTime()) {
				/* 添加怪物到删除列表，出场后的怪物要出未出场列表中删除 */
				monsterWantToDelete->addObject(monster);

				monster->setPosition(monsterFirstPos->getPos());
				monster->setVisible(true);

				/* 让怪物按照指定坐标行走 */
				monster->moveByPosList(m_monsterPosList);
			}
		}
	}

	/* 删除已经出场的怪物 */
	CCARRAY_FOREACH(monsterWantToDelete, obj) {
		monster = dynamic_cast<Monster*>(obj);

		if(monster != NULL) {
			m_notShowMonsterList->removeObject(monster);
		}
	}

	/* 发布怪物数量改变消息 */
	CCDictionary* dict = CCDictionary::create();

	dict->setObject(CCInteger::create(m_notShowMonsterList->count()), enMsgDataKey_MonsterNum);
	NOTIFY->postNotification("MonsterNumChange", dict);
}

void MonsterManager::logic( float dt ) {
	CCObject* obj = NULL;
	Monster* monster = NULL;

	CCARRAY_FOREACH(m_monsterList, obj) {
		monster = dynamic_cast<Monster*>(obj);

		if(monster != NULL) {
			/* 从列表中删除已经到达目的地的怪物 */
			if(monster->getisMoveEnd() == true) {
				m_monsterList->removeObject(monster);
			}
			/* 从列表中删除已经死亡的怪物 */
			else if(monster->isDead() == true) {
				m_monsterList->removeObject(monster);
			}
		}
	}

	if(m_monsterList->count() == 0) {
		/* 怪物数量为0，发布怪物全灭消息 */
		NOTIFY->postNotification("AllMonsterDead",this);
		CCLOG("AllMonsterDead");
	}
}

int MonsterManager::getNotShowMonsterCount() {
	return m_notShowMonsterList->count();
}

CCArray* MonsterManager::getMonsterList() {
	return m_monsterList;
}

MonsterPos* MonsterManager::getMonsterStartPos() {
	return (MonsterPos*)m_monsterPosList->objectAtIndex(0);
}

MonsterPos* MonsterManager::getMonsterEndPos() {
	return (MonsterPos*)m_monsterPosList->lastObject();
}
