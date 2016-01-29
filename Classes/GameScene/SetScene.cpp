#include "SetScene.h"
#include "SceneManager.h"
#include "GameWidget\GWBase.h"
#include "GameWidget\GWWinManager.h"
#include "platform\CCFileUtils.h"
#include "GlobalSetting\GlobalPath.h"
#include "GlobalSetting\GlobalClient.h"
#include "FileLoad\I18N.h"

SetScene::SetScene()
: pProgressLabel(NULL)
, isUpdateItemClicked(false)
{
    init();
}

SetScene::~SetScene()
{
	AssetsManager *pAssetsManager = getAssetsManager();
    CC_SAFE_DELETE(pAssetsManager);
}

CCScene* SetScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        SetScene *layer = SetScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SetScene::init()
{
	createDownloadedDir();
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	GWWinManager* winManager = new GWWinManager();
	GWBase* win = winManager->createWinsFromXML("xml/set.xml");

	this->addChild(winManager->getDesktopWin());

	GWScale9Button* gotoMenuBtn = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("back");
	gotoMenuBtn->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(SetScene::gotoMenu),
		CCControlEventTouchUpInside);

	//以下是用来实现单选框的功能的
	//添加文本信息
	GWLabel * musicText = GWLabel::create();
	musicText->setsText("@72");
	musicText->setiFontSize(24);
	//musicText->setColor(ccc3(255,100,100));
	musicText->setPosition(ccp(visibleSize.width/3,visibleSize.height/5 * 4));
	this->addChild(musicText);

	//创建俩个菜单项，用来实现当选框的功能
	musicON = CCMenuItemImage::create(PATH_PublicUI_Ring_Normal,
		PATH_PublicUI_Ring_Selected,
		this,menu_selector(SetScene::btnMusicON));
	musicOFF = CCMenuItemImage::create(PATH_PublicUI_Ring_Normal,
		PATH_PublicUI_Ring_Selected,
		this,menu_selector(SetScene::btnMusicOFF));

	CCMenu * musicMenu = CCMenu::create(musicON,musicOFF,NULL);
	musicMenu->alignItemsHorizontallyWithPadding(80);
	musicMenu->setPosition(ccp(visibleSize.width/2,visibleSize.height/5 * 4));
	//关键处在这里，设置菜单项为选中状态，单选框在任何时刻必须有一个为选中状态
	
	GlobalClient::sharedGlobalClient()->loadMusicSet();
	if(GlobalClient::sharedGlobalClient()->getMusicSet() == 0)
	{
		musicON->selected();
		musicOFF->unselected();
	}
	else
	{
		musicON->selected();
		musicOFF->unselected();
	}
	this->addChild(musicMenu);

	//添加文本信息
	GWLabel * languageText = GWLabel::create();
	languageText->setsText("@73");
	languageText->setiFontSize(24);
	//languageText->setColor(ccc3(255,100,100));
	languageText->setPosition(ccp(visibleSize.width/3,visibleSize.height/5 * 3));
	this->addChild(languageText);

	//创建俩个菜单项，用来实现当选框的功能
	chinese = CCMenuItemImage::create(PATH_PublicUI_Ring_Normal,
		PATH_PublicUI_Ring_Selected,
		this,menu_selector(SetScene::changeToChinese));
	english = CCMenuItemImage::create(PATH_PublicUI_Ring_Normal,
		PATH_PublicUI_Ring_Selected,
		this,menu_selector(SetScene::changeToEnglish));

	CCMenu * languageMenu = CCMenu::create(chinese,english,NULL);
	languageMenu->alignItemsHorizontallyWithPadding(80);
	languageMenu->setPosition(ccp(visibleSize.width/2,visibleSize.height/5 * 3));
	//关键处在这里，设置菜单项为选中状态，单选框在任何时刻必须有一个为选中状态
	GlobalClient::sharedGlobalClient()->loadLanguage();
	if(GlobalClient::sharedGlobalClient()->getLanguage() == 0)
	{
		chinese->selected();
		english->unselected();
	}
	else
	{
		english->selected();
		chinese->unselected();
	}
	this->addChild(languageMenu);

	

	GWScale9Button* updateBtn = (GWScale9Button*)winManager->getDesktopWin()->getWinByDes("updateBtn");
	updateBtn->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(SetScene::updateBtn),
		CCControlEventTouchUpInside);
	
	pProgressLabel = (GWLabel*)winManager->getDesktopWin()->getWinByDes("progress");
	pProgressLabel->setsText("");

    return true;
}
 void  SetScene::gotoMenu(CCObject* pSender, CCControlEvent event)
 {
	 GlobalClient::sharedGlobalClient()->saveLanguage();
	 GlobalClient::sharedGlobalClient()->saveMusicSet();
	 I18N::shareI18N()->init();
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_MenuScene);
 }

 void  SetScene::updateBtn(CCObject* pSender, CCControlEvent event)
 {
	 pProgressLabel->setsText("");
    
    // update resources
    getAssetsManager()->update();
    
    isUpdateItemClicked = true;
 }

 AssetsManager* SetScene::getAssetsManager()
{
    static AssetsManager *pAssetsManager = NULL;
    
    if (! pAssetsManager)
    {
        pAssetsManager = new AssetsManager("https://raw.githubusercontent.com/ruozigongzuoshi/goddessemblem/master/update/package.zip",
                                           "https://raw.githubusercontent.com/ruozigongzuoshi/goddessemblem/master/update/version.txt",
                                           pathToSave.c_str());
        pAssetsManager->setDelegate(this);
        pAssetsManager->setConnectionTimeout(3);
    }
    
    return pAssetsManager;
}

 void SetScene::createDownloadedDir()
{
    pathToSave = CCFileUtils::sharedFileUtils()->getWritablePath();
    //pathToSave += "tmpdir";
    
    // Create the folder if it doesn't exist
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    DIR *pDir = NULL;
    
    pDir = opendir (pathToSave.c_str());
    if (! pDir)
    {
        mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }
#else
	if ((GetFileAttributesA(pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(pathToSave.c_str(), 0);
	}
#endif
}

void SetScene::onError(AssetsManager::ErrorCode errorCode)
{
    if (errorCode == AssetsManager::kNoNewVersion)
    {
        pProgressLabel->setsText("@75");
    }
    
    if (errorCode == AssetsManager::kNetwork)
    {
        pProgressLabel->setsText("@76");
    }
}

void SetScene::onProgress(int percent)
{
    char progress[20];
    snprintf(progress, 20, "downloading %d%%", percent);
    pProgressLabel->setsText(progress);
}

void SetScene::onSuccess()
{
    pProgressLabel->setsText("@77");
}

void SetScene::close(CCObject* pSender,  CCControlEvent event)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

//在以下俩个事件回调函数中改变他们的选中状态
void SetScene::btnMusicON(CCObject * obj)
{
	musicON->selected();
	musicOFF->unselected();
	GlobalClient::sharedGlobalClient()->setMusicSet(0);
}

void SetScene::btnMusicOFF(CCObject * obj)
{
	musicOFF->selected();
	musicON->unselected();
	GlobalClient::sharedGlobalClient()->setMusicSet(1);
}

void SetScene::changeToChinese(CCObject * obj)
{
	chinese->selected();
	english->unselected();
	GlobalClient::sharedGlobalClient()->setLanguage(0);
}

void SetScene::changeToEnglish(CCObject * obj)
{
	english->selected();
	chinese->unselected();
	GlobalClient::sharedGlobalClient()->setLanguage(1);
}

