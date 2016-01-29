#include "GWWinXmlData.h"
#include "EnumWinType.h"
#include "GlobalSetting/GlobalParam.h"

bool GWWinXmlData::init() {
    mCldXmlDataList = CCArray::create();  /* 子节点列表 */

    m_isNone = false;       /* 标记本身是否为空节点 */

    mEnWinType = en_Win_None; /* 控件类型 */
    m_iX = 0;           /* X坐标 */
    m_iY = 0;           /* Y坐标 */
    m_iWidth = -1;       /* 宽(如果为负值,则不改变控件宽) */
    m_iHeight = -1;      /* 高(如果为负值,则不改变控件高) */
    m_iAlpha = 255;       /* 透明度 */
    m_iOrder = GlobalParam::LayerOrder_LvLNormal;       /* 层次 */

    m_iMarginV = 0;
    m_iMarginH = 0;
    m_fAmchorX = 0.5f;  
    m_fAmchorY = 0.5f;
    m_iFontSize = GlobalParam::PublicFontSize;
    m_fScaleX = 1.0f;    /* X缩放(scale) */
    m_fScaleY = 1.0f;    /* Y缩放(scale) */
    m_isVisible = true;   /* 是否可见 */
    m_isEnable = true;    /* 是否可用 */
    m_isTouchable = false; /* 是否可响应点击事件(默认为true的话,会报错,是因为对象没有内容的时候不能点击?) */
    m_isXLeft = false;
    m_isXRight = false;
    m_isYTop = false;
    m_isYBottom = false;
    m_isXCenter = false;
    m_isYCenter = false;
    m_isMaxWidth = false;
    m_isMaxHeight = false;
    
    m_sText = CCString::create("btn");
    CC_SAFE_RETAIN(m_sText);

    m_sDes = CCString::create("");      /* 控件字符串描述 */
    CC_SAFE_RETAIN(m_sDes);

	m_sScale9bg = CCString::create("");      /* 按钮背景1 */
	CC_SAFE_RETAIN(m_sScale9bg);

	m_sScale9bgDown = CCString::create("");      /* 按钮背景2 */
	CC_SAFE_RETAIN(m_sScale9bgDown);

    m_sBg = CCString::create("");       /* 图片背景 */
    CC_SAFE_RETAIN(m_sBg);

	m_sPlist = CCString::create("");       /* 动画配置 */
    CC_SAFE_RETAIN(m_sPlist);

	m_sAnimation = CCString::create("");       /* 动画文件 */
    CC_SAFE_RETAIN(m_sAnimation);

	m_sAnimationName = CCString::create("");       /* 动画名字 */
    CC_SAFE_RETAIN(m_sAnimationName);

	m_iLoops = -1;		/* 动画无限循环 */
	m_fDelay = 1.0f;	/* 动画播放速度 */

    return true;
}

void GWWinXmlData::addCldXmlData( GWWinXmlData* cldXmlData )
{
    this->mCldXmlDataList->addObject(cldXmlData);
}

CCArray* GWWinXmlData::getCldXmlDataList() {
    return this->mCldXmlDataList;
}

bool GWWinXmlData::isHasChild() {
    if(mCldXmlDataList->count() > 0) {
        return true;
    }
    else {
        return false;
    }
}

const char* GWWinXmlData::getsDes()
{
    return m_sDes->getCString(); 
}

void GWWinXmlData::setsDes( const char* _sDes )
{
    m_sDes = CCString::createWithFormat(_sDes);
}