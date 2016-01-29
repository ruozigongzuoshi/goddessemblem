/*
    �ļ�����    GWWinManager.h
    �衡����    �ؼ�������
              ��Ҫ����ؼ����������,����XML�����ؼ���
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

    /* ��ȡ���� */
    GWDesktopWin* getDesktopWin();

    /* ��ȡ�ؼ������� */
    GWWinSystem* getWinSystem();
public:
    /* ����XML�ļ�,�����ؼ� */
    GWBase* createWinsFromXML(const char* sXmlPath);

	/* ��� */
    void deleteAllData();

private:
    /* ��ȡXMLԪ��,����һ��xml�ؼ����Խṹ���� */
    GWWinXmlData* createXmlData(XMLElement* xmlElement);

    /* ��XML data����ֵ */
    void setWinXmlData(GWWinXmlData* xmlData, const char* sName, const char* sText);

private:
    //static GWWinManager* mWinManager;

private:
    /* �ؼ��������� */
    GWDesktopWin* mDesktopWin;

    /* �ؼ������� */
    GWWinSystem* mWinSystem;

    /* xml���Խṹ������ */
    GWWinXmlDataSetting* mWinXmlDataSetting;
};

#endif