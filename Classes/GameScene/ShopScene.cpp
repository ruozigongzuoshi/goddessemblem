#include "ShopScene.h"
#include "SceneManager.h"
#include "GameWidget\GWBase.h"
#include "GameWidget\GWWinManager.h"
#include "GlobalSetting\GlobalClient.h"
#include "platform\CCFileUtils.h"

CCScene* ShopScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        ShopScene *layer = ShopScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShopScene::init()
{
    bool bRet = false;
    do 
    {
		//背景音乐
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("start.mp3",true);
		manager = new GWWinManager();
		GWBase* win = manager->createWinsFromXML("xml/shop.xml");

		this->addChild(manager->getDesktopWin());

		loadGold();

		goldLabel = (GWLabel*)manager->getDesktopWin()->getWinByDes("goldLabel");

		heroLabel = CCArray::create();

		heroLabel->retain();
		
		for(int i = 1; i <= 10; i++)
		{
			CCString* sHeroLabel = CCString::createWithFormat("heroLabel%d",i);
			heroLabel->addObject((GWLabel*)manager->getDesktopWin()->getWinByDes(sHeroLabel->getCString()));
		}

		goldLabel->setsText(GlobalClient::sharedGlobalClient()->get_iCurGold());
		setLockLabel();
		
		GWScale9Button* gotoMenuBtn = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("back");
		gotoMenuBtn->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(ShopScene::gotoMenu),
			CCControlEventTouchUpInside);
		
        bRet = true;
    } while (0);

	this->schedule(schedule_selector(ShopScene::goldUpdate),1.0f); //重写自己的update

    return bRet;
}

void ShopScene::goldUpdate(float dt)
{
	GlobalClient::sharedGlobalClient()->set_iCurGold(GlobalClient::sharedGlobalClient()->get_iCurGold()+1);
	goldLabel->setsText(GlobalClient::sharedGlobalClient()->get_iCurGold());
	setLockLabel();
}

void ShopScene::setLockLabel()
{
	int iGold = GlobalClient::sharedGlobalClient()->get_iCurGold();
	CCObject* obj;
	int temp = 1;
	CCARRAY_FOREACH(heroLabel, obj)
	{
		GWLabel* heroLabel = (GWLabel*)obj;
		if(iGold > 1 * temp){
			heroLabel->setsText("@50");
		}
		temp = temp * 10;
	}
}

void ShopScene::loadGold()
{
	char* filename = "gold.plist";
	//获得文件在系统的绝对路径
	
	std::string sGoldPath = CCFileUtils::sharedFileUtils()->getWritablePath() + filename;
	if(!CCFileUtils::sharedFileUtils()->isFileExist(sGoldPath))
	{
		sGoldPath = "save/gold.plist";
	}
	
	/* 加载金币数量 */
	
	tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
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

void ShopScene::saveGold()
{
	char* filename = "gold.plist";
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
	fprintf(file,"<goldNum>\n");
	// 属性 
			fprintf(file,"    <integer>%d</integer>\n", GlobalClient::sharedGlobalClient()->get_iCurGold());
	fprintf(file,"</goldNum>\n");

	// plist父节点字段结束 
	fprintf(file,"</plist>\n");

	fclose(file); 
	
}

 void  ShopScene::gotoMenu(CCObject* pSender, CCControlEvent event)
 {
	 saveGold();
	 manager->getDesktopWin()->removeAllWins();
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_MenuScene);
 }

void ShopScene::close(CCObject* pSender,  CCControlEvent event)
{
    // "close" menu item clicked
	manager->getDesktopWin()->removeAllWins();
    CCDirector::sharedDirector()->end();
}
