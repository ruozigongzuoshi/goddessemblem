#include "TowerPosEditorLayer.h"
#include "support/tinyxml2/tinyxml2.h"

TowerPosEditorLayer::TowerPosEditorLayer() {
    m_towerPosList = NULL;
    m_iCurLevel = 1;
	m_iCurMonster = 1000;
	m_iCurList = 0;
	m_monsterListNum = 1;
	m_monsterMgrPosList = NULL;
	m_monsterMgrList = NULL;
	m_enMode = enTowerPos;
}

TowerPosEditorLayer::~TowerPosEditorLayer() {
    CC_SAFE_RELEASE(m_towerPosList);
	CC_SAFE_RELEASE(m_monsterMgrPosList);
	CC_SAFE_RELEASE(m_monsterMgrList);
}

bool TowerPosEditorLayer::init() {
    bool bRet = false;

    do {
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

        /* 初始化塔坐标列表 */
        m_towerPosList = CCArray::create();
        CC_SAFE_RETAIN(m_towerPosList);

		/* 初始化怪物坐标列表 */
		m_monsterMgrPosList = CCArray::create();
		CC_SAFE_RETAIN(m_monsterMgrPosList);

		/* 初始化怪物列表 */
		m_monsterMgrList = CCArray::create();
		CC_SAFE_RETAIN(m_monsterMgrList);

        /* 读取配置文件，生成塔坐标对象 */
        loadConfigFile();

        this->setTouchEnabled(true);
        bRet = true;
    } while (0);

    return true;
}

bool TowerPosEditorLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent ) {

    return true;
}

void TowerPosEditorLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent ) {

}

void TowerPosEditorLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent ) {
    CCPoint touchPos = pTouch->getLocationInView();
    CCPoint pos = CCDirector::sharedDirector()->convertToUI(touchPos);

	/* 判断当前编辑器的模式，进行不同的操作 */
    switch(m_enMode) {
	case enTowerPos:
		editTowerPos(pos);
		break;
	case enMonsterPos:
		editMonsterPos((CCArray*)m_monsterMgrPosList->objectAtIndex(m_iCurList), pos);
		break;
	}

    CCLOG("ccTouchEnded");
}

void TowerPosEditorLayer::registerWithTouchDispatcher( void ) {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}


void TowerPosEditorLayer::outputPosToPlistFile() {
	/* 输出炮台坐标配置文件 */
    CCString* sTowerPosPath = CCString::createWithFormat("towerPos_level_%d.plist", m_iCurLevel);
	outputPosToPlistFile(m_towerPosList, sTowerPosPath->getCString());

	/* 输出怪物坐标配置文件 */
	for(int i = 0; i < m_monsterListNum; i++){
		CCString* sMonsterPosPath = CCString::createWithFormat("monsterPos_level_%d_%d.plist", m_iCurLevel,i);
		outputPosToPlistFile((CCArray*)m_monsterMgrPosList->objectAtIndex(i), sMonsterPosPath->getCString());
	}

	/* 输出怪物坐标配置文件2 */
	CCString* sMonsterListPath = CCString::createWithFormat("level_%d_others.plist", m_iCurLevel);
	outputPosToPlistFile(m_monsterListNum , sMonsterListPath->getCString());

	/* 输出怪物配置文件 */
	for(int i = 0; i < m_monsterListNum; i++){
		CCString* sMonsterPath = CCString::createWithFormat("monster_level_%d_%d.plist", m_iCurLevel,i);
		outputPosToPlistFile2((CCArray*)m_monsterMgrList->objectAtIndex(i), sMonsterPath->getCString());
	}

}



void TowerPosEditorLayer::outputPosToPlistFile(int m_monsterListNum, const char* sFilePath ) {
	std::string filepath = CCFileUtils::sharedFileUtils()->getWritablePath() + sFilePath;
	
	FILE* file = fopen(filepath.c_str(), "w");

	/* xml头部信息 */
	fprintf(file,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(file,"<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n");

	/* plist父节点字段开头 */
	fprintf(file,"<plist version=\"1.0\">\n");

	/* <listNum> */
	fprintf(file,"<listNum>\n");
	/* 属性 */
	/* <integer>3</integer> */
			fprintf(file,"    <integer>%d</integer>\n", m_monsterListNum);
	/* </listNum> */
	fprintf(file,"</listNum>\n");

	/* plist父节点字段结束 */
	fprintf(file,"</plist>\n");

	fclose(file); 
}

void TowerPosEditorLayer::outputPosToPlistFile( CCArray* posList, const char* sFilePath ) {
	std::string filepath = CCFileUtils::sharedFileUtils()->getWritablePath() + sFilePath;
	FILE* file = fopen(filepath.c_str(), "w");

	/* xml头部信息 */
	fprintf(file,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(file,"<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n");

	/* plist父节点字段开头 */
	fprintf(file,"<plist version=\"1.0\">\n");

	/* <array> */
	fprintf(file,"<array>\n");
	/* 各个属性 */
	CCObject* obj = NULL;
	PosBase* posBase = NULL;
	CCARRAY_FOREACH(posList, obj) {
		posBase = dynamic_cast<PosBase*>(obj);

		if(posBase != NULL) {
			/* <dict> */
			fprintf(file,"    <dict>\n");

			/* <key>x</key> */
			fprintf(file,"        <key>x</key>\n");

			/* <integer>80</integer> */
			fprintf(file,"        <integer>%.0f</integer>\n", posBase->getPos().x);

			/* <key>y</key> */
			fprintf(file,"        <key>y</key>\n");

			/* <integer>266</integer> */
			fprintf(file,"        <integer>%.0f</integer>\n", posBase->getPos().y);

			/* </dict> */
			fprintf(file,"    </dict>\n");
		}
	}
	/* </array> */
	fprintf(file,"</array>\n");

	/* plist父节点字段结束 */
	fprintf(file,"</plist>\n");

	fclose(file); 
}

void TowerPosEditorLayer::outputPosToPlistFile2( CCArray* monsterList, const char* sFilePath ) {
	//获得文件在系统的可写路径
	std::string filepath = CCFileUtils::sharedFileUtils()->getWritablePath() + sFilePath;
	FILE* file = fopen(filepath.c_str(), "w");

	/* xml头部信息 */
	fprintf(file,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(file,"<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n");

	/* plist父节点字段开头 */
	fprintf(file,"<plist version=\"1.0\">\n");

	/* <array> */
	fprintf(file,"<array>\n");
	/* 各个属性 */
	CCObject* obj = NULL;
	CCDictionary* dict = NULL;
	CCString* id = 0;
	CCString* sShowTime = 0;
	CCARRAY_FOREACH(monsterList, obj) {
		dict = dynamic_cast<CCDictionary*>(obj);

		id = dynamic_cast<CCString*>(dict->objectForKey("id"));
		sShowTime = dynamic_cast<CCString*>(dict->objectForKey("showTime"));

		if(id != NULL && sShowTime != NULL) {
			/* <dict> */
			fprintf(file,"    <dict>\n");

			/* <key>x</key> */
			fprintf(file,"        <key>id</key>\n");

			/* <integer>80</integer> */
			fprintf(file,"        <integer>%s</integer>\n", id->getCString());

			/* <key>y</key> */
			fprintf(file,"        <key>showTime</key>\n");

			/* <integer>266</integer> */
			fprintf(file,"        <integer>%s</integer>\n", sShowTime->getCString());

			/* </dict> */
			fprintf(file,"    </dict>\n");
		}
	}
	/* </array> */
	fprintf(file,"</array>\n");

	/* plist父节点字段结束 */
	fprintf(file,"</plist>\n");

	fclose(file); 
}


void TowerPosEditorLayer::loadConfigFile() {
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    /* 添加地图背景 */
    CCString* sBG = CCString::createWithFormat("tollgate/level_%d.jpg", m_iCurLevel);
    CCSprite* map = CCSprite::create(sBG->getCString());
    map->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(map, 1);
    
	/* 加载怪物队列数量 */
	CCString* sMonsterListPath = CCString::createWithFormat("%slevel_%d_others.plist",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), m_iCurLevel);
	//CCLOG("%s",CCFileUtils::sharedFileUtils()->getWritablePath());
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


	/* 加载塔坐标对象 */
	CCString* sTowerPosPath = CCString::createWithFormat("%stowerPos_level_%d.plist",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), m_iCurLevel);
	
	if(!CCFileUtils::sharedFileUtils()->isFileExist(sTowerPosPath->getCString()))
	{
		sTowerPosPath = CCString::createWithFormat("tollgate/towerPos_level_%d.plist", m_iCurLevel);
	}
	
	CCArray* posList = PosLoadUtil::sharedPosLoadUtil()->loadPosWithFile(sTowerPosPath->getCString(), enTowerPos, this, 10, true);
	m_towerPosList->addObjectsFromArray(posList);

	/* 加载怪物坐标对象 */
	for(int i = 0; i < m_monsterListNum; i++){
		CCString* sMonsterPosPath = CCString::createWithFormat("%smonsterPos_level_%d_%d.plist",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), m_iCurLevel, i);
	
		if(!CCFileUtils::sharedFileUtils()->isFileExist(sMonsterPosPath->getCString()))
		{
			sMonsterPosPath = CCString::createWithFormat("tollgate/monsterPos_level_%d_%d.plist", m_iCurLevel, i);
		}
		
		posList = PosLoadUtil::sharedPosLoadUtil()->loadPosWithFile(sMonsterPosPath->getCString(), enMonsterPos, this, 10, true);
		CCArray* m_monsterPosList= CCArray::create();
		m_monsterPosList->addObjectsFromArray(posList);
		m_monsterMgrPosList->addObject(m_monsterPosList);
	}

	/* 加载怪物列表 */
	
	for(int i = 0; i < m_monsterListNum; i++){
		// 读取配置文件 
		CCString* sMonsterConfPath = CCString::createWithFormat("%smonster_level_%d_%d.plist",CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), m_iCurLevel, i);
	
		if(!CCFileUtils::sharedFileUtils()->isFileExist(sMonsterConfPath->getCString()))
		{
			sMonsterConfPath = CCString::createWithFormat("tollgate/monster_level_%d_%d.plist", m_iCurLevel, i);
		}
		
		CCArray* m_monsterList= CCArray::create();
		CCArray* confProsArr = CCArray::createWithContentsOfFile(sMonsterConfPath->getCString());
		if(confProsArr){
			m_monsterList->addObjectsFromArray(confProsArr);
		}
		
		m_monsterMgrList->addObject(m_monsterList);

	}
	
}


void TowerPosEditorLayer::editTowerPos(CCPoint pos) {
	/* 如果点击了已经存在的塔坐标对象，则删除该坐标对象，否则创建新坐标对象 */
	TowerPos* existPos = findExistTowerPos(pos);

	if(existPos != NULL) {
		deleteTowerPos(existPos);
	}
	else {
		createTowerPos(pos);
	}
}

TowerPos* TowerPosEditorLayer::findExistTowerPos( CCPoint pos ) {
	CCObject* obj = NULL;
	TowerPos* tPos = NULL;
	CCARRAY_FOREACH(m_towerPosList, obj) {
		tPos = dynamic_cast<TowerPos*>(obj);

		if(tPos) {
			if(tPos->isClickMe(pos)) {
				return tPos;
			}
		}
	}

	return NULL;
}

void TowerPosEditorLayer::createTowerPos( CCPoint pos ) {
    TowerPos* tPos = TowerPos::create(pos, true);
    this->addChild(tPos, 10);
    m_towerPosList->addObject(tPos);
}

void TowerPosEditorLayer::deleteTowerPos( TowerPos* existPos ) {
    this->removeChild(existPos);
    m_towerPosList->removeObject(existPos);
}

void TowerPosEditorLayer::deleteAllPos() {
    this->removeAllChildrenWithCleanup(true);
    m_towerPosList->removeAllObjects();
	m_monsterMgrList->removeAllObjects();
	m_monsterMgrPosList->removeAllObjects();
	m_monsterListNum = 1;
}


int TowerPosEditorLayer::nextLvl() {
	if(m_iCurLevel < 10){
		deleteAllPos();		/* 删除当前所有的坐标对象 */
		m_iCurLevel++;		/* 关卡计数加1 */
		loadConfigFile();	/* 重新读取配置文件 */
		m_iCurList = 0;
	}

    return m_iCurLevel;
}

int TowerPosEditorLayer::preLvl() {
	if(m_iCurLevel > 1)
	{
		deleteAllPos();		/* 删除当前所有的坐标对象 */
		m_iCurLevel--;		/* 关卡计数减1 */
		loadConfigFile();	/* 重新读取配置文件 */
		m_iCurList = 0;
	}

    return m_iCurLevel;
}

int TowerPosEditorLayer::nextList() {
	if(m_iCurList < (int)(m_monsterMgrPosList->count() - 1))
	{
		m_iCurList++;
	}
    
    return m_iCurList;
}

int TowerPosEditorLayer::preList() {
	if(m_iCurList > 0){
		m_iCurList--;
	}
    return m_iCurList;
}

int TowerPosEditorLayer::changeMode() {
	if(m_enMode == enTowerPos) {
		m_enMode = enMonsterPos;
		return 1;
	}
	else if(m_enMode == enMonsterPos) {
		m_enMode = enTowerPos;
		return 0;
	}
}

void TowerPosEditorLayer::addNewMonsterList() {
	CCArray* m_monsterPosList = new CCArray();
	m_monsterMgrPosList->addObject(m_monsterPosList);
	CCArray* m_monsterList = new CCArray();
	m_monsterMgrList->addObject(m_monsterList);
	m_iCurList = m_monsterMgrPosList->count() - 1;
	m_monsterListNum++;
}

CCString* TowerPosEditorLayer::startMonsterMgr() {
	CCArray* monsterList = (CCArray*)m_monsterMgrList->objectAtIndex(m_iCurList);
	CCString* sMonsterList = new CCString();
	CCObject* obj = NULL;
	CCDictionary* dict = NULL;
	CCString* id = 0;
	CCString* sShowTime = 0;
	CCARRAY_FOREACH(monsterList, obj) {
		dict = dynamic_cast<CCDictionary*>(obj);

		id = dynamic_cast<CCString*>(dict->objectForKey("id"));
		sShowTime = dynamic_cast<CCString*>(dict->objectForKey("showTime"));

		if(id != NULL && sShowTime != NULL) {
			sMonsterList = CCString::createWithFormat("%s%d;",sMonsterList->getCString(),id->intValue());
			//monster->setfShowTime(sShowTime->floatValue());
		}
	}
	//CCLOG("%s",sMonsterList->getCString());
	return sMonsterList;
}

void TowerPosEditorLayer::deleteLastMonster(){
	CCArray* nowMonsterList = (CCArray*)m_monsterMgrList->objectAtIndex(m_iCurList);
	if(nowMonsterList->count() > 1){
		nowMonsterList->removeLastObject();
	}
}

int TowerPosEditorLayer::preMonster(){
	if(m_iCurMonster > 1000){
		m_iCurMonster--;
	}
	return m_iCurMonster;
}

int TowerPosEditorLayer::nextMonster(){
	if(m_iCurMonster < 1004){
		m_iCurMonster++;
	}
	return m_iCurMonster;
}

void TowerPosEditorLayer::addNowMonster(){
	CCArray* nowMonsterList = (CCArray*)m_monsterMgrList->objectAtIndex(m_iCurList);
	int time = nowMonsterList->count() + 1;
	CCDictionary* dict = new CCDictionary();
	dict->setObject(CCString::createWithFormat("%d",m_iCurMonster),"id");
	dict->setObject(CCString::createWithFormat("%d",time),"showTime");
	nowMonsterList->addObject(dict);
}

void TowerPosEditorLayer::deleteNowMonsterList() {
	if(m_monsterMgrPosList->count() > 1){
		CCArray* m_monsterPosList = (CCArray*)m_monsterMgrPosList->objectAtIndex(m_iCurList);
		MonsterPos* existPos;
		do{
			existPos = (MonsterPos*)m_monsterPosList->lastObject();
			deleteMonsterPos(m_monsterPosList, existPos);
		}while(existPos != NULL);
		m_monsterMgrPosList->removeObject(m_monsterPosList);
		m_monsterListNum--;
		//删除怪物列表
		m_monsterMgrList->removeObjectAtIndex(m_iCurList);
	}
	if(m_iCurList > 0){
		m_iCurList --;
	}
}

void TowerPosEditorLayer::editMonsterPos(CCArray* m_monsterPosList, CCPoint pos) {
	/* 如果点击了已经存在的怪物坐标对象，则删除该坐标对象，否则创建新坐标对象 */
	MonsterPos* existPos = findExistMonsterPos(m_monsterPosList, pos);

	if(existPos != NULL) {
		deleteMonsterPos(m_monsterPosList, existPos);
	}
	else {
		createMonsterPos(m_monsterPosList, pos);
	}
}


MonsterPos* TowerPosEditorLayer::findExistMonsterPos(CCArray* m_monsterPosList, CCPoint pos ) {
	CCObject* obj = NULL;
	MonsterPos* tPos = NULL;
	CCARRAY_FOREACH(m_monsterPosList, obj) {
		tPos = dynamic_cast<MonsterPos*>(obj);

		if(tPos) {
			if(tPos->isClickMe(pos)) {
				return tPos;
			}
		}
	}

	return NULL;
}


void TowerPosEditorLayer::createMonsterPos(CCArray*  m_monsterPosList,  CCPoint pos ) {
	MonsterPos* mPos = MonsterPos::create(pos, true);
	this->addChild(mPos, 10);
	m_monsterPosList->addObject(mPos);
}

void TowerPosEditorLayer::deleteMonsterPos(CCArray*  m_monsterPosList, MonsterPos* existPos ) {
	this->removeChild(existPos);
	m_monsterPosList->removeObject(existPos);
}

CCArray* TowerPosEditorLayer::getMonsterMgrPosList() {
	return m_monsterMgrPosList;
}


