#include "GWWinProperityFactory.h"
#include "GlobalSetting/GlobalPath.h"
#include "GlobalSetting/GlobalParam.h"

bool GWWinProperityFactory::init() {
    return true;
}

void GWWinProperityFactory::dressPropertiesByType( GWBase* mWin, GWWinXmlData* xmlData ) {
    /* ���ݿؼ��������ö������� */
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

    /* ���û������� */
    dressBaseProperties(mWin, xmlData);
}

void GWWinProperityFactory::dressBaseProperties( GWBase* mWin, GWWinXmlData* xmlData ) {
    /* ���ؼ��Ŀ�ߣ�Ĭ����ȫ����ߣ� */
    CCSize parentSize = CCSizeMake(GlobalParam::DEFAULT_SCREEN_WIDTH, GlobalParam::DEFAULT_SCREEN_HEIGHT);

    /* ����и��ؼ�����ȡ���ؼ��Ŀ�� */
    GWBase* mParent = NULL;
    if(mWin->isHasParentWin()) {
        mParent = (GWBase*)mWin->getParent();
        parentSize = mParent->getContentSize();
    }

    /* 
        ����Ҫ�ص�˵����cocos��y�����Ǵӵײ���ʼ��ģ�����ϰ�ߴӶ�����ʼ�㡣
        �ӿؼ���(0, 0)����ڸ��ؼ���(0, 0)���ϣ���Ȼ��������ؼ���������㣬�������Ϊ׼��
        ���磬���ؼ��������(0.5, 0.5),���ӿؼ���(0, 0)������ڸ��ؼ����е㡣
        �ص����ˣ�Ϊ����y�����ǴӶ�����ʼ����ģ�������Ҫ��y�������-1�������ӿؼ���y����ͻ������(0, 0)�㣬�Ӷ�����ʼ���㡣
        ���ǣ��������ؼ���y���껹�Ǵӵײ���ʼ���㣬����һ��С�鷳����ʱ�������
    */
    int iPosOffset = 1;
    if(mParent != NULL) {
        iPosOffset = -1;
    }
    mWin->setPositionX(xmlData->getiX());      // x����
    mWin->setPositionY(xmlData->getiY() * iPosOffset);      // y����
	//mWin->setPositionY(xmlData->getiY());      // y����
    mWin->setiOrder(xmlData->getiOrder());     // ���
    mWin->setEnabled(xmlData->isEnable());     // �Ƿ����
    mWin->setVisible(xmlData->isVisible());    // �Ƿ�ɼ�
    mWin->setOpacity(xmlData->getiAlpha());    // ͸����
    mWin->setScaleX(xmlData->getfScaleX());    // x����
    mWin->setScaleY(xmlData->getfScaleY());    // y����
    mWin->setTouchEnabled(xmlData->isTouchable()); // �Ƿ�ɵ��
    mWin->setAnchorPoint(ccp(xmlData->getfAmchorX(), xmlData->getfAmchorY())); // ���


    /* ��� */
    CCSize sizeProp = getSizeProp(mParent, xmlData);
    int iWidth = sizeProp.width;
    int iHeight = sizeProp.height;
    

    if(iWidth > 0 && iHeight > 0) {
        mWin->setContentSize(CCSizeMake(iWidth, iHeight));
    }

    bool isXLeft = xmlData->isXLeft();      /* �Ƿ�������� */
    bool isXRight = xmlData->isXRight();    /* �Ƿ����Ҷ��� */
    bool isXCenter = xmlData->isXCenter();  /* �Ƿ���ж��� */

    bool isYTop = xmlData->isYTop();        /* �Ƿ����϶��� */
    bool isYBottom = xmlData->isYBottom();  /* �Ƿ����¶��� */
    bool isYCenter = xmlData->isYCenter();  /* �Ƿ���ж��� */

    /* -------- �����ĸ�����Ŀ��߶���(��Bug����������) ------------ */
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

        /* ����ؼ��и��ؼ�����0, 0�������ڸ��ؼ����е� */
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

    /* ��ȡ������� */
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

	/* �����С */
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

    /* ��ȡ������� */
    CCSize size = getSizeProp(mParent, xmlData);

    const char* scale9bg = xmlData->getsScale9bg();

    if(strcmp(scale9bg, "") != 0) {
        mScale9Win->setScale9BG(scale9bg, size);
    }
}

cocos2d::CCSize GWWinProperityFactory::getSizeProp( GWBase* parent, GWWinXmlData* xmlData )
{

    /* ��� */
    int iWidth = xmlData->getiWidth();
    int iHeight = xmlData->getiHeight();
    bool isMaxWidth = xmlData->isMaxWidth();
    bool isMaxHeight = xmlData->isMaxHeight();

    /* ������ */
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
    /* �ı� */
	const char* sText = xmlData->getsText();
	if(sText != NULL) {
		mLabel->setsText(sText);
	}

    /* �����С */
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
