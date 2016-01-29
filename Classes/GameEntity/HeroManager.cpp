#include "HeroManager.h"
#include "TowerPos.h"
#include "TowerBorder.h"
#include "PosLoadUtil.h"
#include "EnumPosType.h"
#include "Hero.h"
#include "GlobalSetting\GlobalClient.h"

HeroManager::HeroManager() {
	m_towerPosList = NULL;
	m_towerBorderList = NULL;
	//m_curClickHero = NULL;
}

HeroManager::~HeroManager() {
	CC_SAFE_RELEASE(m_towerPosList);
	CC_SAFE_RELEASE(m_towerBorderList);
	//CC_SAFE_RELEASE(m_curClickHero);
}

HeroManager* HeroManager::createWithLevel( int iCurLevel ) {
	HeroManager* heroMgr = new HeroManager();

	if(heroMgr && heroMgr->initWithLevel(iCurLevel)) {
		heroMgr->autorelease();
	}
	else {
		CC_SAFE_DELETE(heroMgr);
	}

	return heroMgr;
}

bool HeroManager::initWithLevel(int iCurLevel) {
	bool bRet = false;

	do {
		/* 初始化塔坐标列表 */
		m_towerPosList = CCArray::create();
		CC_SAFE_RETAIN(m_towerPosList);

		/* 初始化炮台列表 */
		m_towerBorderList = CCArray::create();
		CC_SAFE_RETAIN(m_towerBorderList);

		/* 加载塔坐标对象 */
		CCString* sTowerPosPath = CCString::createWithFormat("%stowerPos_level_%d.plist",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), iCurLevel);
	
		if(!CCFileUtils::sharedFileUtils()->isFileExist(sTowerPosPath->getCString()))
		{
			sTowerPosPath = CCString::createWithFormat("tollgate/towerPos_level_%d.plist", iCurLevel);
		}
		//CCString* sTowerPosPath = CCString::createWithFormat("tollgate/towerPos_level_%d.plist", iCurLevel);

		CCArray* posList = PosLoadUtil::sharedPosLoadUtil()->loadPosWithFile(
			sTowerPosPath->getCString(), enTowerPos, this, 10, false);
		m_towerPosList->addObjectsFromArray(posList);

		/* 创建炮台 */
		createTowerBorder(iCurLevel);


		this->setTouchEnabled(true);
		bRet = true;
	} while (0);

	return bRet;
}

void HeroManager::createTowerBorder(int iCurLevel) {
	CCObject* obj = NULL;
	TowerPos* tPos = NULL;
	CCARRAY_FOREACH(m_towerPosList, obj) {
		tPos = dynamic_cast<TowerPos*>(obj);

		if(tPos) {
			TowerBorder* border = TowerBorder::create();
			border->upgrade();
			border->upgrade();
			border->setPosition(tPos->getPos());

			m_towerBorderList->addObject(border);
			this->addChild(border);
		}
	}
}

TowerBorder* HeroManager::findClickTowerBorder( CCPoint pos ) {
	CCObject* obj = NULL;
	TowerBorder* tBorder = NULL;
	CCARRAY_FOREACH(m_towerBorderList, obj) {
		tBorder = dynamic_cast<TowerBorder*>(obj);

		if(tBorder) {
			if(tBorder->isClickMe(pos)) {
				return tBorder;
			}
		}
	}

	return NULL;
}

void HeroManager::createTowerPos( CCPoint pos ) {
	TowerPos* tPos = TowerPos::create(pos, true);
	this->addChild(tPos, TOWER_POS_LAYER_LVL);
	m_towerPosList->addObject(tPos);
}

// void HeroManager::deleteTowerPos( TowerPos* existPos ) {
// 	this->removeChild(existPos);
// 	m_towerPosList->removeObject(existPos);
// }
// 
// void HeroManager::deleteAllTowerPos() {
// 	this->removeAllChildrenWithCleanup(true);
// 	m_towerPosList->removeAllObjects();
// }

bool HeroManager::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent ) {

	return true;
}

void HeroManager::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent ) {

}

void HeroManager::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent ) {
	CCPoint touchPos = pTouch->getLocationInView();
	CCPoint pos = CCDirector::sharedDirector()->convertToUI(touchPos);

	/* 获取被点击的塔坐标 */
	TowerBorder* clickBorder = findClickTowerBorder(pos);

	if(clickBorder == NULL) {
		return;
	}
	/* 当前塔坐标没有英雄对象，则添加英雄 */
	if(clickBorder->getHero() == NULL) {
		Hero* hero = Hero::createFromCsvFileByID(GlobalClient::sharedGlobalClient()->get_iCurHeroNo());
		hero->setPosition(clickBorder->getPosition());
		this->addChild(hero, TOWER_LAYER_LVL);

		/* 绑定塔对象 */
		clickBorder->bindHero(hero);

	}
	else {
// 		if(m_curClickHero != NULL) {
// 			m_curClickHero->setShowRange(false);
// 			CC_SAFE_RELEASE(m_curClickHero);
// 		}
// 		m_curClickHero = clickBorder->getHero();
// 		m_curClickHero->setShowRange(true);
// 		CC_SAFE_RETAIN(m_curClickHero);
		clickBorder->showTowerOprBtns();
	}
	CCLOG("ccTouchEnded");
}

void HeroManager::registerWithTouchDispatcher( void ) {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}
