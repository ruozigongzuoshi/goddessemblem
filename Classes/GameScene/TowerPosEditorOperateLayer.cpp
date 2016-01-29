#include "TowerPosEditorOperateLayer.h"
#include "TowerPosEditorLayer.h"
#include "GameEntity/MonsterPos.h"
#include "GameWidget\GWBase.h"
#include "GameWidget\GWWinManager.h"
#include "SceneManager.h"
#include "FileLoad\I18N.h"

TowerPosEditorOperateLayer::TowerPosEditorOperateLayer() {
    layer = NULL;
}

TowerPosEditorOperateLayer::~TowerPosEditorOperateLayer() {
    CC_SAFE_RETAIN(layer);
}

TowerPosEditorOperateLayer* TowerPosEditorOperateLayer::create( TowerPosEditorLayer* layer ) {
    TowerPosEditorOperateLayer* oprLayer = new TowerPosEditorOperateLayer();

    if(oprLayer && oprLayer->init(layer)) {
        oprLayer->autorelease();
    }
    else {
        CC_SAFE_DELETE(oprLayer);
    }

    return oprLayer;
}

bool TowerPosEditorOperateLayer::init(TowerPosEditorLayer* layer) {
    bool bRet = false;

    do {
        CC_BREAK_IF(! CCLayer::init());

        CC_SAFE_RETAIN(layer);
        this->layer = layer;

        /* ��Ӳ����ؼ� */
        addWins();

        bRet = true;
    } while (0);

    return bRet;
}

void TowerPosEditorOperateLayer::addWins() {

	//��������
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("start.mp3",true);
	manager = new GWWinManager();
	GWBase* win = manager->createWinsFromXML("xml/PosEditorOperateLayer.xml");

	this->addChild(manager->getDesktopWin(),20);

    //CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	modeLabel = (GWLabel*)manager->getDesktopWin()->getWinByDes("modeLabel");
	

    /* ������ɰ�ť */
	GWScale9Button* ouputBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("ouputBtn");
	ouputBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::outputPosToPlistFile),
			CCControlEventTouchUpInside);
    

    /* �����һ�ذ�ť */
	
	GWScale9Button* nextLvlBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("nextLvlBtn");
	nextLvlBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::nextLvl),
			CCControlEventTouchUpInside);
	

	/* �����һ�ذ�ť */
	GWScale9Button* preLvlBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("preLvlBtn");
	preLvlBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::preLvl),
			CCControlEventTouchUpInside);
	

	// ����л�ģʽ��ť 
	GWScale9Button* changeModeBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("changeModeBtn");
	changeModeBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::changeMode),
			CCControlEventTouchUpInside);
	

	// ����½������б�ť 
	GWScale9Button* newMonsterMgrBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("newMonsterMgrBtn");
	newMonsterMgrBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::addNewMonsterList),
			CCControlEventTouchUpInside);
	

    // �����һ����ť 
	GWScale9Button* nextListBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("nextListBtn");
	nextListBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::nextList),
			CCControlEventTouchUpInside);
	

	//�����һ����ť 
	GWScale9Button* preListBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("preListBtn");
	preListBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::preList),
			CCControlEventTouchUpInside);
	
	// ���ɾ����ť 
	GWScale9Button* deleteListBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("deleteListBtn");
	deleteListBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::deleteNowMonsterList),
			CCControlEventTouchUpInside);

	// ��ӹ��ﶨ�ư�ť 
	GWScale9Button* startMonsterMgrBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("startMonsterMgrBtn");
	startMonsterMgrBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::startMonsterMgr),
			CCControlEventTouchUpInside);
	

    // �����һ����ť 
	GWScale9Button* nextMonsterBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("nextMonsterBtn");
	nextMonsterBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::nextMonster),
			CCControlEventTouchUpInside);
	

	//�����һ����ť 
	GWScale9Button* preMonsterBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("preMonsterBtn");
	preMonsterBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::preMonster),
			CCControlEventTouchUpInside);
	
	// ���ɾ����ť 
	GWScale9Button* deleteLastMonsterBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("deleteLastMonsterBtn");
	deleteLastMonsterBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::deleteLastMonster),
			CCControlEventTouchUpInside);

	// ��ӵ�ǰ���ﰴť 
	GWScale9Button* addNowMonsterBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("addNowMonsterBtn");
	addNowMonsterBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::addNowMonster),
			CCControlEventTouchUpInside);

	GWScale9Button* gotoMenuBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("back");
		gotoMenuBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(TowerPosEditorOperateLayer::gotoMenu),
			CCControlEventTouchUpInside);
	
	
}

 void  TowerPosEditorOperateLayer::gotoMenu(CCObject* pSender, CCControlEvent event)
 {
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_MenuScene);
 }

void TowerPosEditorOperateLayer::outputPosToPlistFile( CCObject* pSender, CCControlEvent event ) {
    layer->outputPosToPlistFile();
	modeLabel->setsText("@61");

}

void TowerPosEditorOperateLayer::nextLvl( CCObject* pSender, CCControlEvent event ) {
	modeLabel->setsText(CCString::createWithFormat("%s%d",I18N::shareI18N()->getcStringByKey(62),layer->nextLvl())->getCString());
}

void TowerPosEditorOperateLayer::preLvl( CCObject* pSender, CCControlEvent event ) {
    modeLabel->setsText(CCString::createWithFormat("%s%d",I18N::shareI18N()->getcStringByKey(62),layer->preLvl())->getCString());
}

void TowerPosEditorOperateLayer::changeMode(CCObject* pSender, CCControlEvent event) {
	if(layer->changeMode() == 0)
	{
		modeLabel->setsText("@11");
	}
	else
	{
		modeLabel->setsText("@70");
	}
}

void TowerPosEditorOperateLayer::addNewMonsterList( CCObject* pSender, CCControlEvent event ) {
    layer->addNewMonsterList();
	modeLabel->setsText("@63");
}

void TowerPosEditorOperateLayer::nextList( CCObject* pSender, CCControlEvent event ) {
	modeLabel->setsText(CCString::createWithFormat("%s%d",I18N::shareI18N()->getcStringByKey(64),layer->nextList()+1)->getCString());
 
}

void TowerPosEditorOperateLayer::preList( CCObject* pSender, CCControlEvent event ) {
    modeLabel->setsText(CCString::createWithFormat("%s%d",I18N::shareI18N()->getcStringByKey(64),layer->preList()+1)->getCString());
 
}

void TowerPosEditorOperateLayer::deleteNowMonsterList(CCObject* pSender, CCControlEvent event) {
	layer->deleteNowMonsterList();
	modeLabel->setsText("@65");
}

void TowerPosEditorOperateLayer::startMonsterMgr( CCObject* pSender, CCControlEvent event ) {
	
	modeLabel->setsText(CCString::createWithFormat("%s\n%s",I18N::shareI18N()->getcStringByKey(66),layer->startMonsterMgr()->getCString())->getCString());
}

void TowerPosEditorOperateLayer::nextMonster( CCObject* pSender, CCControlEvent event ) {
	modeLabel->setsText(CCString::createWithFormat("%s%d",I18N::shareI18N()->getcStringByKey(67),layer->nextMonster())->getCString());
    
}

void TowerPosEditorOperateLayer::preMonster( CCObject* pSender, CCControlEvent event ) {
    modeLabel->setsText(CCString::createWithFormat("%s%d",I18N::shareI18N()->getcStringByKey(67),layer->preMonster())->getCString());
    
}

void TowerPosEditorOperateLayer::deleteLastMonster(CCObject* pSender, CCControlEvent event) {
	layer->deleteLastMonster();
	modeLabel->setsText(CCString::createWithFormat("%s\n%s\n%s",I18N::shareI18N()->getcStringByKey(68),I18N::shareI18N()->getcStringByKey(66),layer->startMonsterMgr()->getCString())->getCString());
    
}

void TowerPosEditorOperateLayer::addNowMonster(CCObject* pSender, CCControlEvent event) {
	layer->addNowMonster();
	modeLabel->setsText(CCString::createWithFormat("%s\n%s\n%s",I18N::shareI18N()->getcStringByKey(69),I18N::shareI18N()->getcStringByKey(66),layer->startMonsterMgr()->getCString())->getCString());
    
}

void TowerPosEditorOperateLayer::draw() {
	
	CCLayer::draw();
	glLineWidth(2);
	
	CCObject* mgrObj = NULL;
	
	CCArray* m_monsterMgrPosList = layer->getMonsterMgrPosList();
	CCARRAY_FOREACH(m_monsterMgrPosList, mgrObj) {
		CCArray* m_monsterPosList = dynamic_cast<CCArray*>(mgrObj);

		CCObject* obj = NULL;
		MonsterPos* mPos = NULL;
		MonsterPos* prePos = NULL;
		CCARRAY_FOREACH(m_monsterPosList, obj) {
			mPos = dynamic_cast<MonsterPos*>(obj);

			if(mPos != NULL) {
				if(prePos != NULL) {
					ccDrawColor4F(0,  1, 0, 1.0);
					ccDrawLine(prePos->getPos(), mPos->getPos());
					prePos = mPos;
				}
				else {
					prePos = mPos;
				}
			}
		}
	}
	
	glLineWidth(1);
	ccDrawColor4F(1.0, 1.0, 1.0, 1.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
