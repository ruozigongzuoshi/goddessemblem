#include "GlobalClient.h"

GlobalClient* GlobalClient::m_client = NULL;

GlobalClient::GlobalClient() {
	m_curTollgateScene = NULL;
	m_iCurHeroNo = 1;
	m_iMusicSet = 0;
	m_iLanguage = 0;
}

GlobalClient::~GlobalClient() {
	CC_SAFE_RELEASE(m_curTollgateScene);
}

GlobalClient* GlobalClient::sharedGlobalClient() {
	if(m_client == NULL) {
		m_client = new GlobalClient();

		if(m_client && m_client->init()) {
			m_client->autorelease();
		}
		else {
			CC_SAFE_DELETE(m_client);
		}
	}

	return m_client;
}

bool GlobalClient::init() {
	bool bRet = false;

	do 
	{
        m_iCurTollgateLevel = 1;
		bRet = true;
	} while (0);

	return bRet;
}

void GlobalClient::setCurTollgateScene( TollgateScene* scene ) {
	CC_SAFE_RETAIN(scene);
	CC_SAFE_RELEASE(m_curTollgateScene);

	this->m_curTollgateScene = scene;
}

TollgateScene* GlobalClient::getCurTollgateScene() {
	return this->m_curTollgateScene;
}

int GlobalClient::get_iCurTollgateLevel() {
    return m_iCurTollgateLevel;
}

void GlobalClient::setiCurTollgateLevel( int iLevel ) {
    m_iCurTollgateLevel = iLevel;
}

int GlobalClient::get_iCurHeroNo() {
    return m_iCurHeroNo;
}

void GlobalClient::set_iCurHeroNo( int iNo ) {
    m_iCurHeroNo = iNo;
}

int GlobalClient::get_iCurGold() {
    return m_iCurGold;
}

void GlobalClient::set_iCurGold( int iGold ) {
    m_iCurGold = iGold;
}

int GlobalClient::getMusicSet() {
    return m_iMusicSet;
}

void GlobalClient::setMusicSet( int iMusicSet ) {
    m_iMusicSet = iMusicSet;
}

int GlobalClient::getLanguage() {
    return m_iLanguage;
}

void GlobalClient::setLanguage( int iLanguage ) {
    m_iLanguage = iLanguage;
}

void GlobalClient::loadLanguage()
{
	char* filename = "language.plist";
	//获得文件在系统的绝对路径
	
	std::string sGoldPath = CCFileUtils::sharedFileUtils()->getWritablePath() + filename;
	if(!CCFileUtils::sharedFileUtils()->isFileExist(sGoldPath))
	{
		sGoldPath = "save/language.plist";
	}
	
	/* 加载 */
	
	tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
	unsigned char* pBuffer = NULL;
	unsigned long bufferSize = 0;

	pBuffer = CCFileUtils::sharedFileUtils()->getFileData(sGoldPath.c_str(), "r", &bufferSize);

	if (pBuffer)
	{
		xmlDoc->Parse((const char*)pBuffer);
		CCString* nums = CCString::create(xmlDoc->RootElement()->FirstChildElement()->FirstChildElement()->GetText());
		CCLOG(nums->getCString());
		setLanguage(nums->intValue());
	}
	delete xmlDoc;

}

void GlobalClient::saveLanguage()
{
	char* filename = "language.plist";
	//获得文件在系统的可写路径
	std::string filepath = CCFileUtils::sharedFileUtils()->getWritablePath() + filename;
	
	FILE* file = fopen(filepath.c_str(), "w");
	//fwrite(data,sizeof(char),len,file);

	// xml头部信息 
	fprintf(file,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(file,"<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n");

	// plist父节点字段开头 
	fprintf(file,"<plist version=\"1.0\">\n");

	// <goldNum> 
	fprintf(file,"<languageNum>\n");
	// 属性 
			fprintf(file,"    <integer>%d</integer>\n", getLanguage());
	fprintf(file,"</languageNum>\n");

	// plist父节点字段结束 
	fprintf(file,"</plist>\n");

	fclose(file); 
	
}

void GlobalClient::loadMusicSet()
{
	char* filename = "music.plist";
	//获得文件在系统的绝对路径
	
	std::string sGoldPath = CCFileUtils::sharedFileUtils()->getWritablePath() + filename;
	if(!CCFileUtils::sharedFileUtils()->isFileExist(sGoldPath))
	{
		sGoldPath = "save/music.plist";
	}
	
	/* 加载 */
	
	tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
	unsigned char* pBuffer = NULL;
	unsigned long bufferSize = 0;

	pBuffer = CCFileUtils::sharedFileUtils()->getFileData(sGoldPath.c_str(), "r", &bufferSize);

	if (pBuffer)
	{
		xmlDoc->Parse((const char*)pBuffer);
		CCString* nums = CCString::create(xmlDoc->RootElement()->FirstChildElement()->FirstChildElement()->GetText());
		CCLOG(nums->getCString());
		setMusicSet(nums->intValue());
	}
	delete xmlDoc;

}

void GlobalClient::saveMusicSet()
{
	char* filename = "music.plist";
	//获得文件在系统的可写路径
	std::string filepath = CCFileUtils::sharedFileUtils()->getWritablePath() + filename;
	
	FILE* file = fopen(filepath.c_str(), "w");
	//fwrite(data,sizeof(char),len,file);

	// xml头部信息 
	fprintf(file,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(file,"<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n");

	// plist父节点字段开头 
	fprintf(file,"<plist version=\"1.0\">\n");

	// <goldNum> 
	fprintf(file,"<musicNum>\n");
	// 属性 
			fprintf(file,"    <integer>%d</integer>\n", getMusicSet());
	fprintf(file,"</musicNum>\n");

	// plist父节点字段结束 
	fprintf(file,"</plist>\n");

	fclose(file); 
	
}
