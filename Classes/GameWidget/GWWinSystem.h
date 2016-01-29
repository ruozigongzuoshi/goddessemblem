/*
    文件名：    GWWinSyetem.h
    描　述：    负责控件创建逻辑
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
        根据XML结构数据创建控件.
        它有可能创建很多个控件,但最终都会添加到一个父控件里.
        换句话说,xml文件里只允许出现一个最高父控件,不能出现同级别的父控件.
    */
    GWBase* createWinsByXmlData(GWWinXmlData* xmlData, bool isHasParent);

    /* 根据控件类型给控件设置属性(就像穿衣服一样) */
    void dressPropertiesByType(GWBase* mmWin, GWWinXmlData* xmlData);

    /* 创建一个唯一ID */
    int createUniqueID();
private:/* ---------- 属性 ---------- */

	GWWinManager* manager;

    /* 桌面 */
    GWDesktopWin* mDesktopWin;

    /* 控件工厂 */
    GWWinBaseFactory* mWinFactory;

    /* 控件属性加工厂 */
    GWWinProperityFactory* mWinProperityFactory;

    /* 控件ID */
    int m_iWinID;

private:/* ---------- 方法 ---------- */

    /* 根据XML结构数据创建一个控件 */
    GWBase* createWinByXmlData(GWWinXmlData* xmlData);

    /* 根据控件类型创建一个控件 */
    GWBase* createWinByType(EnumWinType enWinType);

};

#endif