#include "TollgateDataLayer.h"
#include "FileLoad/I18N.h"
#include "GameEntity/EnumStrKey.h"
#include "GlobalSetting/GlobalPath.h"
#include "GameWidget/GWWinManager.h"
#include "GlobalSetting/GlobalParam.h"
#include "GlobalSetting/GlobalDefine.h"
#include "GameEntity/EnumMsgDataKey.h"
#include "GameWidget/GWLabel.h"
#include "SceneManager.h"
#include "GlobalSetting/GlobalDefine.h"
#include "GameEntity/EnumMsgDataKey.h"
#include "GlobalSetting\GlobalClient.h"

TollgateDataLayer::TollgateDataLayer() {
	m_towerSoulLab = NULL;
	m_monsterLab = NULL;
	m_magicLab = NULL;
	mLVLab = NULL;
	mATKLab = NULL;
	mSPLab = NULL;
	mSQLab = NULL;
}

TollgateDataLayer::~TollgateDataLayer() {
	CC_SAFE_RELEASE(m_towerSoulLab);
	CC_SAFE_RELEASE(m_monsterLab);
	CC_SAFE_RELEASE(m_magicLab);
	CC_SAFE_RELEASE(mLVLab);
	CC_SAFE_RELEASE(mATKLab);
	CC_SAFE_RELEASE(mSPLab);
	CC_SAFE_RELEASE(mSQLab);
}

bool TollgateDataLayer::init() {
    bool bRet = false;

    do {
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		winManager = new GWWinManager();
		GWBase* win = winManager->createWinsFromXML(PATH_UI_TollgateProMsgWin);
		this->addChild(winManager->getDesktopWin());

		GWScale9Button* endGameBtn = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("back");
		endGameBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TollgateDataLayer::endGame),
			CCControlEventTouchUpInside);
		//MMWinManager::sharedWinManager()->createWinsFromXML(PATH_UI_Menu);

        /* 塔魂标签 */
        m_towerSoulLab = (GWLabel*)winManager->getDesktopWin()->getWinByDes("tollgateMsgWinTowerSoulLab");
		CC_SAFE_RETAIN(m_towerSoulLab);

        /* 怪物标签 */
        m_monsterLab = (GWLabel*)winManager->getDesktopWin()->getWinByDes("tollgateMsgWinMonsterLab");
		CC_SAFE_RETAIN(m_monsterLab);

        /* 魔力标签 */
        m_magicLab = (GWLabel*)winManager->getDesktopWin()->getWinByDes("tollgateMsgWinHPLab");
		CC_SAFE_RETAIN(m_magicLab);

		mLVLab = (GWLabel*)winManager->getDesktopWin()->getWinByDes("tollgateMsgWinLVLab");
		CC_SAFE_RETAIN(mLVLab);

		mATKLab = (GWLabel*)winManager->getDesktopWin()->getWinByDes("tollgateMsgWinATKLab");
		CC_SAFE_RETAIN(mATKLab);

		mSPLab = (GWLabel*)winManager->getDesktopWin()->getWinByDes("tollgateMsgWinSPLab");
		CC_SAFE_RETAIN(mSPLab);

		mSQLab = (GWLabel*)winManager->getDesktopWin()->getWinByDes("tollgateMsgWinSQLab");
		CC_SAFE_RETAIN(mSQLab);

		CCArray* hero = new CCArray();
		//hero->retain();
		int temp = 1;
		loadGold();
		int gold = GlobalClient::sharedGlobalClient()->get_iCurGold();
		for(int i = 1; i <= 10; i++){
			
			if(gold >= temp){
				CCString* sHero = CCString::createWithFormat("hero%d",i);
				GWScale9Button* heroBtn = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes(sHero->getCString());
				heroBtn->addTargetWithActionForControlEvents(
				this,
				cccontrol_selector(TollgateDataLayer::setHero),
				CCControlEventTouchUpInside);
				heroBtn->setTouchEnabled(true);
				temp = temp * 10;
			}
			
		}
		


        /* 订阅消息 */
        NOTIFY->addObserver(this, 
            callfuncO_selector(TollgateDataLayer::recvRefreshTowerSoulNum), 
            "TowerSoulChange", 
            NULL);

        NOTIFY->addObserver(this, 
            callfuncO_selector(TollgateDataLayer::recvRefreshMonsterNum), 
            "MonsterNumChange", 
            NULL);

        NOTIFY->addObserver(this, 
            callfuncO_selector(TollgateDataLayer::recvRefreshMagicNum), 
            "MagicChange", 
            NULL);

		NOTIFY->addObserver(this, 
            callfuncO_selector(TollgateDataLayer::recvRefreshLevelNum), 
            "curLevelShow", 
            NULL);
		NOTIFY->addObserver(this, 
            callfuncO_selector(TollgateDataLayer::recvRefreshATKNum), 
            "curATKShow", 
            NULL);
		NOTIFY->addObserver(this, 
            callfuncO_selector(TollgateDataLayer::recvRefreshSpeedNum), 
            "curSpeedShow", 
            NULL);
		NOTIFY->addObserver(this, 
            callfuncO_selector(TollgateDataLayer::recvRefreshRangeNum), 
            "curRangeShow", 
            NULL);

		NOTIFY->addObserver(this, 
			callfuncO_selector(TollgateDataLayer::recvMonsterDead), 
			"MonsterDead", 
			NULL);

		NOTIFY->addObserver(this, 
			callfuncO_selector(TollgateDataLayer::recvGameIsWin), 
			"GameIsWin", 
			NULL);

        bRet = true;
    } while (0);

    return bRet;
}

void TollgateDataLayer::recvRefreshTowerSoulNum( CCObject* pData ) {
    CCDictionary* dict = dynamic_cast<CCDictionary*>(pData);

    if(dict == NULL) {
        return;
    }

    /* 塔魂改变值 */
    CCInteger* towerSoulAltNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_TowerSoulAltNum));
    if(towerSoulAltNum != NULL) {
        m_iTowerSoulNum += towerSoulAltNum->getValue();
    }

    /* 塔魂值 */
    CCInteger* towerSoulNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_TowerSoulNum));
    if(towerSoulNum != NULL) {
        m_iTowerSoulNum = towerSoulNum->getValue();
    }

    m_towerSoulLab->setsText(m_iTowerSoulNum);

	
}

void TollgateDataLayer::recvRefreshMonsterNum( CCObject* pData ) {
    CCDictionary* dict = dynamic_cast<CCDictionary*>(pData);

    if(dict == NULL) {
        return;
    }

    /* 怪物改变值 */
    CCInteger* monsterAltNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MonsterAltNum));
    if(monsterAltNum != NULL) {
        m_iMonsterNum += monsterAltNum->getValue();
    }

    /* 怪物值 */
    CCInteger* monsterSoulNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MonsterNum));
    if(monsterSoulNum != NULL) {
        m_iMonsterNum = monsterSoulNum->getValue();
    }

    m_monsterLab->setsText(m_iMonsterNum);

}

void TollgateDataLayer::recvRefreshMagicNum( CCObject* pData ) {
    CCDictionary* dict = dynamic_cast<CCDictionary*>(pData);

    if(dict == NULL) {
        return;
    }

    /* 魔力改变值 */
    CCInteger* magicAltNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MagicAltNum));
    if(magicAltNum != NULL) {
        m_iMagicNum += magicAltNum->getValue();
    }

    /* 魔力值 */
    CCInteger* magicNum = dynamic_cast<CCInteger*>(dict->objectForKey(enMsgDataKey_MagicNum));
    if(magicNum != NULL) {
        m_iMagicNum = magicNum->getValue();
    }

    m_magicLab->setsText(m_iMagicNum);

	/* 魔力值小于等于0，游戏失败 */
	if(m_iMagicNum <= 0) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->end();
		winManager->getDesktopWin()->removeAllWins();
		SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameOverScene);
	}
}

void TollgateDataLayer::recvRefreshLevelNum( CCObject* pData ) { 
	CCString* ss = (CCString*)pData;
	mLVLab->setsText(ss->getCString());
}

void TollgateDataLayer::recvRefreshATKNum( CCObject* pData ) { 
	CCString* ss = (CCString*)pData;
	mATKLab->setsText(ss->getCString());
}

void TollgateDataLayer::recvRefreshSpeedNum( CCObject* pData ) { 
	CCString* ss = (CCString*)pData;
	mSPLab->setsText(ss->getCString());
}

void TollgateDataLayer::recvRefreshRangeNum( CCObject* pData ) { 
	CCString* ss = (CCString*)pData;
	mSQLab->setsText(ss->getCString());
}

void TollgateDataLayer::recvMonsterDead(CCObject* pData) {
	m_iTowerSoulNum += 10;
	m_towerSoulLab->setsText(m_iTowerSoulNum);
}

void TollgateDataLayer::recvGameIsWin( CCObject* pData ) {
	
	if(m_iMagicNum > 0) {
		SceneManager::sharedSceneManager()->changeScene(SceneManager::en_WinScene);
	}
}

void TollgateDataLayer::onExit() { 
    /* 取消订阅消息 */
    NOTIFY->removeObserver(this, "TowerSoulChange");
    NOTIFY->removeObserver(this, "MonsterNumChange");
    NOTIFY->removeObserver(this, "MagicChange");
	NOTIFY->removeObserver(this, "curLevelShow");
	NOTIFY->removeObserver(this, "curATKShow");
	NOTIFY->removeObserver(this, "curSpeedShow");
	NOTIFY->removeObserver(this, "curRangeShow");
	NOTIFY->removeObserver(this, "MonsterDead");
	NOTIFY->removeObserver(this, "GameIsWin");

	//GWWinManager::sharedWinManager()->getDesktopWin()->removeAllWins();
}

int TollgateDataLayer::getiMagicNum() {
	return m_iMagicNum;
}

int TollgateDataLayer::getiTowerSoulNum() {
	return m_iTowerSoulNum;
}

void  TollgateDataLayer::setHero(CCObject* pSender, CCControlEvent event)
{
	GWScale9Button* heroBtn = (GWScale9Button*)pSender;
	int temp = 1;
	temp = heroBtn->getCurrentTitle()->intValue();
	GlobalClient::sharedGlobalClient()->set_iCurHeroNo(temp);
}

void TollgateDataLayer::loadGold()
{
	/* 加载金币数量 */
	char* filename = "gold.plist";
	//获得文件在系统的绝对路径
	
	std::string sGoldPath = CCFileUtils::sharedFileUtils()->getWritablePath() + filename;
	if(!CCFileUtils::sharedFileUtils()->isFileExist(sGoldPath))
	{
		sGoldPath = "save/gold.plist";
	}
	//CCString* sGoldPath = CCString::create("save/gold.plist");
	tinyxml2::XMLDocument * xmlDoc = new tinyxml2::XMLDocument();
	unsigned char* pBuffer = NULL;
	unsigned long bufferSize = 0;

	pBuffer = CCFileUtils::sharedFileUtils()->getFileData(sGoldPath.c_str(), "r", &bufferSize);

	if (pBuffer)
	{
		xmlDoc->Parse((const char*)pBuffer);
		CCString* nums = CCString::create(xmlDoc->RootElement()->FirstChildElement()->FirstChildElement()->GetText());
		CCLOG(nums->getCString());
		GlobalClient::sharedGlobalClient()->set_iCurGold(nums->intValue());
	}
	delete xmlDoc;

}

void TollgateDataLayer::endGame(CCObject* pSender, CCControlEvent event) { 
	CocosDenshion::SimpleAudioEngine::sharedEngine()->end();
	winManager->getDesktopWin()->removeAllWins();
	SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameOverScene);
}
