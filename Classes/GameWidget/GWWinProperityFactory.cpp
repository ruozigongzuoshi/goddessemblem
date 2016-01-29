#include "GWWinProperityFactory.h"
#include "GlobalSetting/GlobalPath.h"
#include "GlobalSetting/GlobalParam.h"

bool GWWinProperityFactory::init() {
    return true;
}

void GWWinProperityFactory::dressPropertiesByType( GWBase* mWin, GWWinXmlData* xmlData ) {
    /* 根据控件类型设置独特属性 */
    switch(mWin->getEnWinType()) {
    case en_Win_None:

        break;
    case en_Win_Scale9Button:
        dressGWButton((GWScale9Button*)mWin, xmlData);
        break;
    case en_Win_Div:
        dressGWDiv((GWDiv*)mWin, xmlData);
        break;
    case en_Win_Scale9Win:
        dressGWScale9Win((GWScale9Win*)mWin, xmlData);
        break;
	case en_Win_NormalWin:
		dressGWNormalWin((GWNormalWin*)mWin, xmlData);
		break;
	case en_Win_AnimationWin:
		dressGWAnimationWin((GWAnimationWin*)mWin, xmlData);
		break;
	case en_Win_Label:
		dressGWLabel((GWLabel*)mWin, xmlData);
		break;
    }

    /* 设置基础属性 */
    dressBaseProperties(mWin, xmlData);
}

void GWWinProperityFactory::dressBaseProperties( GWBase* mWin, GWWinXmlData* xmlData ) {
    /* 父控件的宽高（默认是全屏宽高） */
    CCSize parentSize = CCSizeMake(GlobalParam::DEFAULT_SCREEN_WIDTH, GlobalParam::DEFAULT_SCREEN_HEIGHT);

    /* 如果有父控件，则取父控件的宽高 */
    GWBase* mParent = NULL;
    if(mWin->isHasParentWin()) {
        mParent = (GWBase*)mWin->getParent();
        parentSize = mParent->getContentSize();
    }

    /* 
        这里要重点说明：cocos的y坐标是从底部开始算的，我们习惯从顶部开始算。
        子控件的(0, 0)点会在父控件的(0, 0)点上，当然，如果父控件设置了描点，则按照描点为准。
        比如，父控件的描点是(0.5, 0.5),则子控件的(0, 0)坐标会在父控件的中点。
        重点来了，为了让y坐标是从顶部开始计算的，我们需要让y坐标乘于-1，这样子控件的y坐标就会相对于(0, 0)点，从顶部开始计算。
        但是，顶级父控件的y坐标还是从底部开始计算，这是一个小麻烦，暂时不解决了
    */
    int iPosOffset = 1;
    if(mParent != NULL) {
        iPosOffset = -1;
    }
    mWin->setPositionX(xmlData->getiX());      // x坐标
    mWin->setPositionY(xmlData->getiY() * iPosOffset);      // y坐标
	//mWin->setPositionY(xmlData->getiY());      // y坐标
    mWin->setiOrder(xmlData->getiOrder());     // 层次
    mWin->setEnabled(xmlData->isEnable());     // 是否可用
    mWin->setVisible(xmlData->isVisible());    // 是否可见
    mWin->setOpacity(xmlData->getiAlpha());    // 透明度
    mWin->setScaleX(xmlData->getfScaleX());    // x缩放
    mWin->setScaleY(xmlData->getfScaleY());    // y缩放
    mWin->setTouchEnabled(xmlData->isTouchable()); // 是否可点击
    mWin->setAnchorPoint(ccp(xmlData->getfAmchorX(), xmlData->getfAmchorY())); // 描点


    /* 宽高 */
    CCSize sizeProp = getSizeProp(mParent, xmlData);
    int iWidth = sizeProp.width;
    int iHeight = sizeProp.height;
    

    if(iWidth > 0 && iHeight > 0) {
        mWin->setContentSize(CCSizeMake(iWidth, iHeight));
    }

    bool isXLeft = xmlData->isXLeft();      /* 是否靠最左对齐 */
    bool isXRight = xmlData->isXRight();    /* 是否靠最右对齐 */
    bool isXCenter = xmlData->isXCenter();  /* 是否居中对齐 */

    bool isYTop = xmlData->isYTop();        /* 是否靠最上对齐 */
    bool isYBottom = xmlData->isYBottom();  /* 是否靠最下对齐 */
    bool isYCenter = xmlData->isYCenter();  /* 是否居中对齐 */

    /* -------- 设置四个方向的靠边对齐(有Bug，尽量别用) ------------ */
    CCPoint anchorP = mWin->getAnchorPoint();
    CCSize winSize = mWin->getContentSize();

    if(isXLeft) {
        int x = 0;
        x += anchorP.x * winSize.width;
        mWin->setPositionX(x);
    }
    else if(isXRight) {
        int x = parentSize.width - winSize.width;
        x += anchorP.x * winSize.width;
        mWin->setPositionX(x);
    }

    if(isYTop) {
        int y = parentSize.height;
        y -= anchorP.y * winSize.height;
        mWin->setPositionY(y);
    }
    else if(isYBottom) {
        int y = 0;
        y += anchorP.y * winSize.height;
        mWin->setPositionY(y);
    }

    if(isXCenter) {
        int x = parentSize.width / 2;
        //x += anchorP.x * winSize.width;

        /* 如果控件有父控件，则（0, 0）坐标在父控件的中点 */
        if(mParent != NULL) {
            x = 0;
        }

        mWin->setPositionX(x);
    }
    if(isYCenter) {
        int y = parentSize.height / 2;
        //y += anchorP.y * winSize.height;

        if(mParent != NULL) {
            y = 0;
        }
        mWin->setPositionY(y);
    }
}

void GWWinProperityFactory::dressGWDiv( GWDiv* mDiv, GWWinXmlData* xmlData ) {

}

void GWWinProperityFactory::dressGWButton( GWScale9Button* mScale9Button, GWWinXmlData* xmlData ) {
    GWBase* mParent = NULL;
    if(mScale9Button->isHasParentWin()) {
        mParent = (GWBase*)mScale9Button->getParent();
    }

    /* 读取宽高属性 */
    CCSize size = getSizeProp(mParent, xmlData);
    int iWidth = size.width;
    int iHeight = size.height;
	int ifontSize = xmlData->getiFontSize();

    const char* scale9bg = xmlData->getsScale9bg();
    const char* scale9bgDown = xmlData->getsScale9bgDown();
    const char* sText = xmlData->getsText();
    

    if(strcmp(scale9bg, "") != 0) {
        mScale9Button->setBackgroundSpriteForState(CCScale9Sprite::create(scale9bg), CCControlStateNormal);
    }  

    if(strcmp(scale9bgDown, "") != 0) {
        mScale9Button->setBackgroundSpriteForState(CCScale9Sprite::create(scale9bgDown), CCControlStateHighlighted);
    }  

    if(strcmp(sText, "") != 0) {
        mScale9Button->setTitleForState(CCString::create(sText), CCControlStateNormal);
    }  

	/* 字体大小 */
    mScale9Button->setTitleTTFSizeForState(xmlData->getiFontSize(),  CCControlStateNormal);

    if(iWidth > 0 && iHeight > 0) {
        mScale9Button->setPreferredSize(CCSizeMake(iWidth, iHeight));
        mScale9Button->setAdjustBackgroundImage(false);
    } 

    int iMarginH = xmlData->getiMarginH();
    int iMarginV = xmlData->getiMarginV();
    mScale9Button->setMargins(iMarginH, iMarginV);
}

void GWWinProperityFactory::dressGWScale9Win( GWScale9Win* mScale9Win, GWWinXmlData* xmlData ) {
    GWBase* mParent = NULL;
    if(mScale9Win->isHasParentWin()) {
        mParent = (GWBase*)mScale9Win->getParent();
    }

    /* 读取宽高属性 */
    CCSize size = getSizeProp(mParent, xmlData);

    const char* scale9bg = xmlData->getsScale9bg();

    if(strcmp(scale9bg, "") != 0) {
        mScale9Win->setScale9BG(scale9bg, size);
    }
}

cocos2d::CCSize GWWinProperityFactory::getSizeProp( GWBase* parent, GWWinXmlData* xmlData )
{

    /* 宽高 */
    int iWidth = xmlData->getiWidth();
    int iHeight = xmlData->getiHeight();
    bool isMaxWidth = xmlData->isMaxWidth();
    bool isMaxHeight = xmlData->isMaxHeight();

    /* 宽高最大化 */
    if(isMaxWidth) {
        if(parent != NULL) {
            iWidth = parent->getContentSize().width;
        }
        else {
            iWidth = GlobalParam::DEFAULT_SCREEN_WIDTH;
        }
    }
    if(isMaxHeight) {
        if(parent != NULL) {
            iHeight = parent->getContentSize().height;
        }
        else {
            iHeight = GlobalParam::DEFAULT_SCREEN_HEIGHT;
        }
    }

    return CCSizeMake(iWidth, iHeight);
}

void GWWinProperityFactory::dressGWNormalWin( GWNormalWin* mNormalWin, GWWinXmlData* xmlData ) {
	const char* bgPath = xmlData->getsBg();
	CCString* dst = CCString::create(bgPath);
	
	if(bgPath != NULL && dst->m_sString.compare("") != 0) {
		mNormalWin->setBG(bgPath);
	}
}

void GWWinProperityFactory::dressGWLabel( GWLabel* mLabel, GWWinXmlData* xmlData ) {
    /* 文本 */
	const char* sText = xmlData->getsText();
	if(sText != NULL) {
		mLabel->setsText(sText);
	}

    /* 字体大小 */
    mLabel->setiFontSize(xmlData->getiFontSize());
}

void GWWinProperityFactory::dressGWAnimationWin(GWAnimationWin* mAnimationWin,GWWinXmlData*  xmlData){
	const char* bgPath = xmlData->getsBg();
	const char* sAnimation = xmlData->getsAnimation();
	const char* sAnimationName = xmlData->getsAnimationName();
	const char* sPlist = xmlData->getsPlist();
	int iLoops = xmlData->getiLoops();
	float fDelay = xmlData->getfDelay();

	if(bgPath != NULL) {
		mAnimationWin->setBG(bgPath);
	}

	if((sPlist != NULL)&&(sAnimation != NULL)&&(sAnimationName != NULL)){
		mAnimationWin->setAnimationName(sAnimationName);
		mAnimationWin->setAnimationPath(sAnimation);
		mAnimationWin->setAnimationPlistPath(sPlist);
		mAnimationWin->setLoops(iLoops);
		mAnimationWin->setDelay(fDelay);
		mAnimationWin->runAction();
	}
	
}
