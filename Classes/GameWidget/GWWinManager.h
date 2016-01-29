/*
    文件名：    GWWinManager.h
    描　述：    控件管理器
              主要负责控件操作的入口,加载XML创建控件等
*/
#ifndef __GW_WIN_MANAGER_H__
#define __GW_WIN_MANAGER_H__

#include "cocos2d.h"
#include "GWDesktopWin.h"
#include "GWWinSystem.h"
#include "support/tinyxml2/tinyxml2.h"
#include "GWWinXmlData.h"
#include "GWWinXmlDataSetting.h"
#include "GWBase.h"
USING_NS_CC;
using namespace tinyxml2;

class GWWinManager : public CCObject {
public:
    GWWinManager();
    ~GWWinManager();

    //static GWWinManager* sharedWinManager();
    virtual bool init();

    void printTest(GWWinXmlData* xmlData);

    /* 获取桌面 */
    GWDesktopWin* getDesktopWin();

    /* 获取控件生成器 */
    GWWinSystem* getWinSystem();
public:
    /* 根据XML文件,创建控件 */
    GWBase* createWinsFromXML(const char* sXmlPath);

	/* 清空 */
    void deleteAllData();

private:
    /* 读取XML元素,生成一个xml控件属性结构对象 */
    GWWinXmlData* createXmlData(XMLElement* xmlElement);

    /* 给XML data对象赋值 */
    void setWinXmlData(GWWinXmlData* xmlData, const char* sName, const char* sText);

private:
    //static GWWinManager* mWinManager;

private:
    /* 控件顶级桌面 */
    GWDesktopWin* mDesktopWin;

    /* 控件生成器 */
    GWWinSystem* mWinSystem;

    /* xml属性结构设置器 */
    GWWinXmlDataSetting* mWinXmlDataSetting;
};

#endif