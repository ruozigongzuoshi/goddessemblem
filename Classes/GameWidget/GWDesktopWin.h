/*
    文件名：   GWWinManager.h
    描　述：    控件顶层桌面
*/
#ifndef __GW_DESKTOP_WIN_H__
#define __GW_DESKTOP_WIN_H__

#include "cocos2d.h"
#include "GWBase.h"

USING_NS_CC;

class GWDesktopWin : public GWBase {
public:
    GWDesktopWin();
    ~GWDesktopWin();

    CREATE_FUNC(GWDesktopWin);
    virtual bool init();

    virtual void registerWithTouchDispatcher();

    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

    virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

    virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
public:
    /* 添加一个控件 */
    void addWin(GWBase* mmWin);

    /* 添加控件ID和控件字符串描述键值对 */
    void addDesID(int iWinID, const char* sDes);

    /* 根据ID获取控件 */
    GWBase* getWinByID(int ID);

    /* 根据控件字符串描述获取控件 */
    GWBase* getWinByDes(const char* sDes);

    /* 删除所有控件 */
    void removeAllWins();
private:
    /* 存放所有控件的字典<GWBase, CCInteger> */
    CCDictionary* mWinDict;

    /* 控件字符串描述和控件ID对应键值对<CCInteger*, const char*> */
    CCDictionary* mDesIDDict;
};

#endif