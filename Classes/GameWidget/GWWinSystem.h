/*
    �ļ�����    GWWinSyetem.h
    �衡����    ����ؼ������߼�
*/
#ifndef __GW_WIN_SYSTEM_H__
#define __GW_WIN_SYSTEM_H__

#include "cocos2d.h"
#include "GWBase.h"
#include "GWWinXmlData.h"
#include "EnumWinType.h"
#include "GWDesktopWin.h"
#include "GWWinFactory.h"
#include "GWWinProperityFactory.h"
#include "GWWinBaseFactory.h"

USING_NS_CC;
class GWWinManager;

class GWWinSystem : public CCObject {
public:
    GWWinSystem();
    ~GWWinSystem();

    static GWWinSystem* create(GWWinManager* manager, GWDesktopWin* desktopWin);
    virtual bool init(GWWinManager* managers, GWDesktopWin* desktopWin);

    /*
        ����XML�ṹ���ݴ����ؼ�.
        ���п��ܴ����ܶ���ؼ�,�����ն�����ӵ�һ�����ؼ���.
        ���仰˵,xml�ļ���ֻ�������һ����߸��ؼ�,���ܳ���ͬ����ĸ��ؼ�.
    */
    GWBase* createWinsByXmlData(GWWinXmlData* xmlData, bool isHasParent);

    /* ���ݿؼ����͸��ؼ���������(�����·�һ��) */
    void dressPropertiesByType(GWBase* mmWin, GWWinXmlData* xmlData);

    /* ����һ��ΨһID */
    int createUniqueID();
private:/* ---------- ���� ---------- */

	GWWinManager* manager;

    /* ���� */
    GWDesktopWin* mDesktopWin;

    /* �ؼ����� */
    GWWinBaseFactory* mWinFactory;

    /* �ؼ����Լӹ��� */
    GWWinProperityFactory* mWinProperityFactory;

    /* �ؼ�ID */
    int m_iWinID;

private:/* ---------- ���� ---------- */

    /* ����XML�ṹ���ݴ���һ���ؼ� */
    GWBase* createWinByXmlData(GWWinXmlData* xmlData);

    /* ���ݿؼ����ʹ���һ���ؼ� */
    GWBase* createWinByType(EnumWinType enWinType);

};

#endif