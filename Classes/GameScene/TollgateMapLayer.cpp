#include "TollgateMapLayer.h"
#include "GameEntity/TowerPos.h"
#include "GameEntity/EnumPosType.h"
#include "GameEntity/PosLoadUtil.h"
#include "SimpleAudioEngine.h"
#include "GlobalSetting/GlobalDefine.h"
#include "GameEntity/MonsterPos.h"
#include "GameEntity/HeroManager.h"
#include "GameEntity/MonsterManager.h"
#include "GameEntity/EnumMsgDataKey.h"
#include "GlobalSetting/GlobalClient.h"

TollgateMapLayer::TollgateMapLayer() {
    m_iCurLevel = GlobalClient::sharedGlobalClient()->get_iCurTollgateLevel();
	m_monsterMgrList = NULL;
	m_heroMgr = NULL;
}

TollgateMapLayer::~TollgateMapLayer() {
	CC_SAFE_RELEASE(m_monsterMgrList);
}

bool TollgateMapLayer::init() {
    bool bRet = false;

    do {
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

        /* 读取关卡配置 */
        loadConfig();

		/* 加载怪物队列数量 */
		CCString* sMonsterListPath = CCString::createWithFormat("%slevel_%d_others.plist",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), m_iCurLevel);
	
		if(!CCFileUtils::sharedFileUtils()->isFileExist(sMonsterListPath->getCString()))
		{
			sMonsterListPath = CCString::createWithFormat("tollgate/level_%d_others.plist", m_iCurLevel);
		}
		tinyxml2::XMLDocument * xmlDoc = new tinyxml2::XMLDocument();
		unsigned char* pBuffer = NULL;
		unsigned long bufferSize = 0;

		pBuffer = CCFileUtils::sharedFileUtils()->getFileData(sMonsterListPath->getCString(), "r", &bufferSize);

		if (pBuffer)
		{
			xmlDoc->Parse((const char*)pBuffer);
			CCString* nums = CCString::create(xmlDoc->RootElement()->FirstChildElement()->FirstChildElement()->GetText());
			m_monsterListNum = nums->intValue();
		}
		delete xmlDoc;

		
		/* 创建怪物管理器 */
		m_monsterMgrList = CCArray::createWithCapacity(m_monsterListNum);
		CC_SAFE_RETAIN(m_monsterMgrList);
		for(int i = 0; i < m_monsterListNum; i++){
			m_monsterMgrList->insertObject(MonsterManager::createWithLevel(m_iCurLevel, i), i);
			this->addChild((MonsterManager*)m_monsterMgrList->objectAtIndex(i), MONSTER_LAYER_LVL);
		}
		
		/* 创建英雄管理器 */
		m_heroMgr = HeroManager::createWithLevel(m_iCurLevel);
		this->addChild(m_heroMgr, HERO_LAYER_LVL);

        /* 创建起始点 */
        createStartPoint();

        /* 创建堡垒 */
        createHome();
		
        /* 初始化塔魂、怪物和魔力数量 */
        CCDictionary* dict = CCDictionary::create();

        dict->setObject(CCInteger::create(5), enMsgDataKey_TowerSoulNum);
        NOTIFY->postNotification("TowerSoulChange", dict);

        dict->removeAllObjects();
		CCObject* it = NULL;
		int NotShowMonster = 0;
		CCARRAY_FOREACH(m_monsterMgrList, it){
			MonsterManager* m_monsterMgr = dynamic_cast<MonsterManager*>(it);
			NotShowMonster += m_monsterMgr->getNotShowMonsterCount();
		}
		dict->setObject(CCInteger::create(NotShowMonster), enMsgDataKey_MonsterNum);
        //dict->setObject(CCInteger::create(m_monsterMgr->getNotShowMonsterCount()), enMsgDataKey_MonsterNum);
        NOTIFY->postNotification("MonsterNumChange", dict);

        dict->removeAllObjects();
        dict->setObject(CCInteger::create(100), enMsgDataKey_MagicNum);
        NOTIFY->postNotification("MagicChange", dict);

		dict->removeAllObjects();
        dict->setObject(CCInteger::create(3), enMsgDataKey_MagicNum);
		NOTIFY->postNotification("MonsterListNumChange", dict);

		NOTIFY->addObserver(this, 
			callfuncO_selector(TollgateMapLayer::removeMonsterList), 
			"AllMonsterDead", 
		NULL);

        bRet = true;

    } while (0);

    return true;
}

void TollgateMapLayer::loadConfig() {
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	/* 添加背景音乐 */
	CCString* backgroundMusic = CCString::createWithFormat("%stollgate_%d.mp3",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), m_iCurLevel);
	
	if(!CCFileUtils::sharedFileUtils()->isFileExist(backgroundMusic->getCString()))
	{
		backgroundMusic = CCString::createWithFormat("music/tollgate_%d.mp3", m_iCurLevel);
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		backgroundMusic->getCString(), true);


    /* 添加地图背景 */
    CCString* sBG = CCString::createWithFormat("%slevel_%d.jpg",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), m_iCurLevel);
	
	if(!CCFileUtils::sharedFileUtils()->isFileExist(sBG->getCString()))
	{
		sBG = CCString::createWithFormat("tollgate/level_%d.jpg", m_iCurLevel);
	}
    CCSprite* map = CCSprite::create(sBG->getCString());
    map->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(map, 1);

}

CCArray* TollgateMapLayer::getMonsterList() {
	CCObject* it = NULL;
	CCArray* monsterList = CCArray::create();
	CCARRAY_FOREACH(m_monsterMgrList, it){
		MonsterManager* m_monsterMgr = dynamic_cast<MonsterManager*>(it);
		monsterList->addObjectsFromArray(m_monsterMgr->getMonsterList());
	}
	
	return monsterList;
}

void TollgateMapLayer::onExit() {
    this->unscheduleAllSelectors();

    /* 取消订阅消息 */
	NOTIFY->removeObserver(this, "AllMonsterDead");
}

void TollgateMapLayer::createHome() {
	CCObject* it = NULL;
	CCARRAY_FOREACH(m_monsterMgrList, it){
		MonsterManager* m_monsterMgr = dynamic_cast<MonsterManager*>(it);
		MonsterPos* pos = m_monsterMgr->getMonsterEndPos();

		CCSprite* home = CCSprite::create("tollgate/home.png");
		home->setPosition(pos->getPos());

		CCActionInterval* rotateBy = CCRotateBy::create(15.0f, 360, 360);
		CCActionInterval* repeat = CCRepeatForever::create(rotateBy);
		home->runAction(repeat);

		this->addChild(home, HOME_LAYER_LVL);
	}
	
}

void TollgateMapLayer::createStartPoint() {
	CCObject* it = NULL;
	CCARRAY_FOREACH(m_monsterMgrList, it){
		MonsterManager* m_monsterMgr = dynamic_cast<MonsterManager*>(it);
		MonsterPos* pos = m_monsterMgr->getMonsterStartPos();

		CCSprite* startSp = CCSprite::create("tollgate/start.png");
		startSp->setPosition(pos->getPos());

		CCActionInterval* rotateBy = CCRotateBy::create(15.0f, 360, 360);
		CCActionInterval* repeat = CCRepeatForever::create(rotateBy);
		startSp->runAction(repeat);

		this->addChild(startSp, HOME_LAYER_LVL);
	}
	/*
	MonsterPos* pos = m_monsterMgr->getMonsterStartPos();

	CCSprite* startSp = CCSprite::create("tollgate/start.png");
	startSp->setPosition(pos->getPos());

	CCActionInterval* rotateBy = CCRotateBy::create(15.0f, 360, 360);
	CCActionInterval* repeat = CCRepeatForever::create(rotateBy);
	startSp->runAction(repeat);

	this->addChild(startSp, HOME_LAYER_LVL);
	*/
}

void TollgateMapLayer::removeMonsterList( CCObject* pData ) {
	m_monsterMgrList->removeObject((MonsterManager*)pData);
	CCLOG("Delete a monster list");
	if(m_monsterMgrList->count() == 0){
		/* 怪物队列为0，发布怪物胜利消息 */
		NOTIFY->postNotification("GameIsWin");
		CCLOG("GameIsWin");
	}
}
