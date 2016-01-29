/*
    文件名：    GWWinSyetem.h
    描　述：    控件基类
*/
#ifndef __GW_BASE_H__
#define __GW_BASE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EnumWinType.h"
#include "GlobalSetting/GlobalDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

/*
 * 继承了CCControl
 * 它可以看做是Cocos2d-x的基类
 * 自定义控件都必须继承GWBase.
 */
class GWBase : public CCControl {
public:
    GWBase();
    ~GWBase();

private:
    int m_ID;       /* 控件ID */
    int m_iOrder;   /* 层次 */
    CC_PRIVATE_BOOL(m_isHasParentWin, HasParentWin);  /* 是否有父控件 */
    CC_PRIVATE_BOOL(m_isHasChildWin, HasChildWin);    /* 是否有子控件 */
    EnumWinType mEnWinType; /* 控件类型 */
public:
    const int getiWinID();         /* 获取控件ID*/
    void setiWinID(int _ID);         /* 设置控件ID*/
    const int getiOrder();
    void setiOrder(int _iOrder);
    const EnumWinType getEnWinType();
    void setEnWinType(EnumWinType _mEnWinType);
};

#endif