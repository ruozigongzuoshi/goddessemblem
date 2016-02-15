#include "HeroInfoScene.h"
#include "SceneManager.h"
#include "FileLoad\CsvUtil.h"
#include "GlobalSetting\GlobalPath.h"
#include "GameWidget\GWBase.h"
#include "GameWidget\GWWinManager.h"
#include "GameEntity\Hero.h"
#include "GlobalSetting\GlobalClient.h"
#include "GameEntity\EnumHeroPropConfType.h"

CCScene* HeroInfoScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HeroInfoScene *layer = HeroInfoScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HeroInfoScene::init()
{
    bool bRet = false;
    do 
    {
		//背景音乐
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("start.mp3",true);

		manager = new GWWinManager();
		GWBase* win = manager->createWinsFromXML("xml/heroinfo.xml");

		this->addChild(manager->getDesktopWin());

		CsvUtil* csvUtil = CsvUtil::sharedCsvUtil();
		CCSize csvSize = csvUtil->getFileRowColNum(PATH_CSV_HERO_CONF);

		const int iHeroID = GlobalClient::sharedGlobalClient()->get_iCurHeroNo();
		const char* chHeroID = CCString::createWithFormat("%d", iHeroID)->getCString();

		/* 寻找ID所在的行 */
		int iLine = csvUtil->findValueInWithLine(chHeroID, enHeroPropConf_ID, PATH_CSV_HERO_CONF);

		CC_BREAK_IF(iLine < 0);

		GWLabel* IDLabelValue = (GWLabel*)manager->getDesktopWin()->getWinByDes("IDLabelValue");
		IDLabelValue->setsText(iHeroID);

		GWLabel* NameLabelValue = (GWLabel*)manager->getDesktopWin()->getWinByDes("NameLabelValue");
		NameLabelValue->setsText(csvUtil->get(iLine, enHeroPropConf_Name, PATH_CSV_HERO_CONF));

		GWLabel* KindLabelValue = (GWLabel*)manager->getDesktopWin()->getWinByDes("KindLabelValue");
		KindLabelValue->setsText(csvUtil->get(iLine, enHeroPropConf_Type, PATH_CSV_HERO_CONF));

		GWLabel* ModeLabelValue = (GWLabel*)manager->getDesktopWin()->getWinByDes("ModeLabelValue");
		ModeLabelValue->setsText(csvUtil->getInt(iLine, enHeroPropConf_ModelID, PATH_CSV_HERO_CONF));

		GWLabel* ATKLabelValue = (GWLabel*)manager->getDesktopWin()->getWinByDes("ATKLabelValue");
		ATKLabelValue->setsText(csvUtil->getInt(iLine, enHeroPropConf_BaseAtk, PATH_CSV_HERO_CONF));

		GWLabel* SPLabelValue = (GWLabel*)manager->getDesktopWin()->getWinByDes("SPLabelValue");
		SPLabelValue->setsText(csvUtil->getInt(iLine, enHeroPropConf_AtkSpeed, PATH_CSV_HERO_CONF));

		GWLabel* RangeLabelValue = (GWLabel*)manager->getDesktopWin()->getWinByDes("RangeLabelValue");
		RangeLabelValue->setsText(csvUtil->getInt(iLine, enHeroPropConf_AtkRange, PATH_CSV_HERO_CONF));

		GWLabel* GrowLabelValue = (GWLabel*)manager->getDesktopWin()->getWinByDes("GrowLabelValue");
		CCString* sGrowLabelValue = CCString::createWithFormat("%.2f",csvUtil->getFloat(iLine, enHeroPropConf_UpgradeAtkBase, PATH_CSV_HERO_CONF));
		GrowLabelValue->setsText(sGrowLabelValue->getCString());

		GWLabel* ConsumeLabelValue = (GWLabel*)manager->getDesktopWin()->getWinByDes("ConsumeLabelValue");
		ConsumeLabelValue->setsText(csvUtil->getInt(iLine, enHeroPropConf_UpgradeCostBase, PATH_CSV_HERO_CONF));

		GWScale9Button* hero_body = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("hero_body");
		CCString* sHeroBody = CCString::createWithFormat("sprite/goddess/body/%s.png",chHeroID);
		hero_body->setBackgroundSpriteForState(CCScale9Sprite::create(sHeroBody->getCString()), CCControlStateNormal);

		GWScale9Button* back = (GWScale9Button*)manager->getDesktopWin()->getWinByDes("back");
		back->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(HeroInfoScene::back),
			CCControlEventTouchUpInside);
		
        bRet = true;
    } while (0);

    return bRet;
}
 void  HeroInfoScene::back(CCObject* pSender, CCControlEvent event)
 {
	 manager->getDesktopWin()->removeAllWins();
	 SceneManager::sharedSceneManager()->changeScene(SceneManager::en_HandbookScene);
 }

void HeroInfoScene::close(CCObject* pSender,  CCControlEvent event)
{
    // "close" menu item clicked
	manager->getDesktopWin()->removeAllWins();
    CCDirector::sharedDirector()->end();
}

