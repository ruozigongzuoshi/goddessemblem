#include "GWWinXmlData.h"
#include "EnumWinType.h"
#include "GlobalSetting/GlobalParam.h"

bool GWWinXmlData::init() {
    mCldXmlDataList = CCArray::create();  /* �ӽڵ��б� */

    m_isNone = false;       /* ��Ǳ����Ƿ�Ϊ�սڵ� */

    mEnWinType = en_Win_None; /* �ؼ����� */
    m_iX = 0;           /* X���� */
    m_iY = 0;           /* Y���� */
    m_iWidth = -1;       /* ��(���Ϊ��ֵ,�򲻸ı�ؼ���) */
    m_iHeight = -1;      /* ��(���Ϊ��ֵ,�򲻸ı�ؼ���) */
    m_iAlpha = 255;       /* ͸���� */
    m_iOrder = GlobalParam::LayerOrder_LvLNormal;       /* ��� */

    m_iMarginV = 0;
    m_iMarginH = 0;
    m_fAmchorX = 0.5f;  
    m_fAmchorY = 0.5f;
    m_iFontSize = GlobalParam::PublicFontSize;
    m_fScaleX = 1.0f;    /* X����(scale) */
    m_fScaleY = 1.0f;    /* Y����(scale) */
    m_isVisible = true;   /* �Ƿ�ɼ� */
    m_isEnable = true;    /* �Ƿ���� */
    m_isTouchable = false; /* �Ƿ����Ӧ����¼�(Ĭ��Ϊtrue�Ļ�,�ᱨ��,����Ϊ����û�����ݵ�ʱ���ܵ��?) */
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

    m_sDes = CCString::create("");      /* �ؼ��ַ������� */
    CC_SAFE_RETAIN(m_sDes);

	m_sScale9bg = CCString::create("");      /* ��ť����1 */
	CC_SAFE_RETAIN(m_sScale9bg);

	m_sScale9bgDown = CCString::create("");      /* ��ť����2 */
	CC_SAFE_RETAIN(m_sScale9bgDown);

    m_sBg = CCString::create("");       /* ͼƬ���� */
    CC_SAFE_RETAIN(m_sBg);

	m_sPlist = CCString::create("");       /* �������� */
    CC_SAFE_RETAIN(m_sPlist);

	m_sAnimation = CCString::create("");       /* �����ļ� */
    CC_SAFE_RETAIN(m_sAnimation);

	m_sAnimationName = CCString::create("");       /* �������� */
    CC_SAFE_RETAIN(m_sAnimationName);

	m_iLoops = -1;		/* ��������ѭ�� */
	m_fDelay = 1.0f;	/* ���������ٶ� */

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