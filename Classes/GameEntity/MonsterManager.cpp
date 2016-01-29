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
		/* ��ʼ�����������б� */
		m_monsterPosList = CCArray::create();
		CC_SAFE_RETAIN(m_monsterPosList);

		/* ��ʼ�������б� */
		m_monsterList = CCArray::create();
		CC_SAFE_RETAIN(m_monsterList);

		/* �������� */
		createMonsters(iCurLevel, num);
		bRet = true;
	} while (0);

	return bRet;
}

void MonsterManager::createMonsters(int iCurLevel, int num) {
	/* ���ع���������� */
	CCString* sMonsterPosPath = CCString::createWithFormat("%smonsterPos_level_%d_%d.plist",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), iCurLevel, num);
	
	if(!CCFileUtils::sharedFileUtils()->isFileExist(sMonsterPosPath->getCString()))
	{
		sMonsterPosPath = CCString::createWithFormat("tollgate/monsterPos_level_%d_%d.plist", iCurLevel, num);
	}
	//CCString* sMonsterPosPath = CCString::createWithFormat("tollgate/monsterPos_level_%d_%d.plist", iCurLevel, num);
	CCArray* posList = PosLoadUtil::sharedPosLoadUtil()->loadPosWithFile(sMonsterPosPath->getCString(), enMonsterPos, this, 10, false);
	m_monsterPosList->addObjectsFromArray(posList);


	/* ��ȡ�����ļ� */
	CCString* sMonsterConfPath = CCString::createWithFormat("%smonster_level_%d_%d.plist",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), iCurLevel, num);
	
	if(!CCFileUtils::sharedFileUtils()->isFileExist(sMonsterConfPath->getCString()))
	{
		sMonsterConfPath = CCString::createWithFormat("tollgate/monster_level_%d_%d.plist", iCurLevel, num);
	}
	//CCString* sMonsterConfPath = CCString::createWithFormat("tollgate/monster_level_%d_%d.plist", iCurLevel, num);
	CCArray* confProsArr = CCArray::createWithContentsOfFile(sMonsterConfPath->getCString());

	/* ��ʼ��δ�����Ĺ����б� */
	m_notShowMonsterList = CCArray::create();
	CC_SAFE_RETAIN(m_notShowMonsterList);

	/* �ӹ�����������ļ���ȡ����ID�ͳ���ʱ�䣬�������й��ﵽδ�����б� */
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

	/* ����Ƿ����¹������ */
	this->schedule(schedule_selector(MonsterManager::showMonster));

	/* ����Ƿ��й������� */
	this->schedule(schedule_selector(MonsterManager::logic), 0.2f);
}

void MonsterManager::showMonster( float dt ) {
	int iNotShowMonsterCount = m_notShowMonsterList->count();

	if(iNotShowMonsterCount > 0) {
		m_fShowTimeCount += dt;
	}
	
	/* ��ȡ����ĵ�һ������� */
	PosBase* monsterFirstPos = getMonsterStartPos();

	CCObject* obj = NULL;
	Monster* monster = NULL;

	CCArray* monsterWantToDelete = CCArray::create();
	CCARRAY_FOREACH(m_notShowMonsterList, obj) {
		monster = dynamic_cast<Monster*>(obj);

		if(monster != NULL) {
			/* ʱ��ﵽ����ĳ���ʱ�䣬�ù������ */
			if(m_fShowTimeCount >= monster->getfShowTime()) {
				/* ��ӹ��ﵽɾ���б�������Ĺ���Ҫ��δ�����б���ɾ�� */
				monsterWantToDelete->addObject(monster);

				monster->setPosition(monsterFirstPos->getPos());
				monster->setVisible(true);

				/* �ù��ﰴ��ָ���������� */
				monster->moveByPosList(m_monsterPosList);
			}
		}
	}

	/* ɾ���Ѿ������Ĺ��� */
	CCARRAY_FOREACH(monsterWantToDelete, obj) {
		monster = dynamic_cast<Monster*>(obj);

		if(monster != NULL) {
			m_notShowMonsterList->removeObject(monster);
		}
	}

	/* �������������ı���Ϣ */
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
			/* ���б���ɾ���Ѿ�����Ŀ�ĵصĹ��� */
			if(monster->getisMoveEnd() == true) {
				m_monsterList->removeObject(monster);
			}
			/* ���б���ɾ���Ѿ������Ĺ��� */
			else if(monster->isDead() == true) {
				m_monsterList->removeObject(monster);
			}
		}
	}

	if(m_monsterList->count() == 0) {
		/* ��������Ϊ0����������ȫ����Ϣ */
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
