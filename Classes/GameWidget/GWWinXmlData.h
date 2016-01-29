/*
    文件名：    GWWinXmlData.h
    描　述：    xml中的控件属性结构
*/
#ifndef __GW_WIN_XML_DATA_H__
#define __GW_WIN_XML_DATA_H__

#include "cocos2d.h"
#include "EnumWinType.h"
#include "GlobalSetting/GlobalDefine.h"

USING_NS_CC;


class GWWinXmlData : public CCObject {
public:
    CREATE_FUNC(GWWinXmlData);
    virtual bool init();

    /* 添加子节点 */
    void addCldXmlData(GWWinXmlData* cldXmlData);

    /* 获取子节点列表<MMWinXmlData*> */
    CCArray* getCldXmlDataList();

    /* 是否有子节点 */
    bool isHasChild();
private:
    /* 子节点列表<MMWinXmlData*> */
    CCArray* mCldXmlDataList;

    CC_PRIVATE_BOOL(m_isNone, None);/* 标记本身是否为空节点(没有内容,但可以有子节点) */

private:
    CC_PRIVATE(EnumWinType, mEnWinType, EnWinType);/* 控件类型 */ 
    CC_PRIVATE(int, m_iX, iX);                  /* X坐标 */
    CC_PRIVATE(int, m_iY, iY);                  /* Y坐标 */
    CC_PRIVATE(int, m_iWidth, iWidth);          /* 宽 */
    CC_PRIVATE(int, m_iHeight, iHeight);        /* 高 */
    CC_PRIVATE(int, m_iAlpha, iAlpha);          /* 透明度 */
    CC_PRIVATE(int, m_iOrder, iOrder);          /* 层次,值越大,层次越高,越迟绘制 */
    CC_PRIVATE(int, m_iMarginH, iMarginH);      /* 水平方向margin值 */
    CC_PRIVATE(int, m_iMarginV, iMarginV);      /* 垂直方向margin值 */
    CC_PRIVATE(int, m_iFontSize, iFontSize);    /* 字体大小 */
    CC_PRIVATE(float, m_fAmchorX, fAmchorX);      /* AnchorPoint x值 */
    CC_PRIVATE(float, m_fAmchorY, fAmchorY);      /* AnchorPoint y值 */
    CC_PRIVATE(float, m_fScaleX, fScaleX);      /* X缩放(scale) */
    CC_PRIVATE(float, m_fScaleY, fScaleY);      /* Y缩放(scale) */
    CC_PRIVATE_BOOL(m_isVisible, Visible);      /* 是否可见 */
    CC_PRIVATE_BOOL(m_isEnable, Enable);        /* 是否可用 */
    CC_PRIVATE_BOOL(m_isTouchable, Touchable);  /* 是否可点击 */
    CC_PRIVATE_BOOL(m_isXLeft, XLeft);      /* 是否靠最左对齐 */
    CC_PRIVATE_BOOL(m_isXRight, XRight);    /* 是否靠最右对齐 */
    CC_PRIVATE_BOOL(m_isXCenter, XCenter);  /* X方向是否居中对齐 */
    CC_PRIVATE_BOOL(m_isYTop, YTop);        /* 是否靠最上对齐 */
    CC_PRIVATE_BOOL(m_isYBottom, YBottom);  /* 是否靠最下对齐 */
    CC_PRIVATE_BOOL(m_isYCenter, YCenter);  /* Y方向是否居中对齐 */
    CC_PRIVATE_BOOL(m_isMaxWidth, MaxWidth);    /* 宽度是否最大化 */
    CC_PRIVATE_BOOL(m_isMaxHeight, MaxHeight);  /* 高度是否最大化 */
    CCString* m_sDes;           /* 控件字符串描述 */
    GW_XML_PRIVATE_CHAR(m_sScale9bg, sScale9bg);      /* 九妹图片路径 */
    GW_XML_PRIVATE_CHAR(m_sScale9bgDown, sScale9bgDown)/* 九妹图片路径:down状态 */
    GW_XML_PRIVATE_CHAR(m_sText, sText);          /* 文本 */
	GW_XML_PRIVATE_CHAR(m_sBg, sBg);          /* 背景图片 */
	GW_XML_PRIVATE_CHAR(m_sPlist, sPlist);          /* 动画配置文件 */
	GW_XML_PRIVATE_CHAR(m_sAnimation, sAnimation);  /* 动画文件 */
	CC_PRIVATE(int, m_iLoops, iLoops);                  /* 动画循环次数 */
	CC_PRIVATE(float, m_fDelay, fDelay);      /* 动画播放速度 */
	GW_XML_PRIVATE_CHAR(m_sAnimationName, sAnimationName);  /* 动画名字 */
public:
    const char* getsDes();
    void setsDes(const char* _sDes);

};


#endif