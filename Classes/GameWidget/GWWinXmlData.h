/*
    �ļ�����    GWWinXmlData.h
    �衡����    xml�еĿؼ����Խṹ
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

    /* ����ӽڵ� */
    void addCldXmlData(GWWinXmlData* cldXmlData);

    /* ��ȡ�ӽڵ��б�<MMWinXmlData*> */
    CCArray* getCldXmlDataList();

    /* �Ƿ����ӽڵ� */
    bool isHasChild();
private:
    /* �ӽڵ��б�<MMWinXmlData*> */
    CCArray* mCldXmlDataList;

    CC_PRIVATE_BOOL(m_isNone, None);/* ��Ǳ����Ƿ�Ϊ�սڵ�(û������,���������ӽڵ�) */

private:
    CC_PRIVATE(EnumWinType, mEnWinType, EnWinType);/* �ؼ����� */ 
    CC_PRIVATE(int, m_iX, iX);                  /* X���� */
    CC_PRIVATE(int, m_iY, iY);                  /* Y���� */
    CC_PRIVATE(int, m_iWidth, iWidth);          /* �� */
    CC_PRIVATE(int, m_iHeight, iHeight);        /* �� */
    CC_PRIVATE(int, m_iAlpha, iAlpha);          /* ͸���� */
    CC_PRIVATE(int, m_iOrder, iOrder);          /* ���,ֵԽ��,���Խ��,Խ�ٻ��� */
    CC_PRIVATE(int, m_iMarginH, iMarginH);      /* ˮƽ����marginֵ */
    CC_PRIVATE(int, m_iMarginV, iMarginV);      /* ��ֱ����marginֵ */
    CC_PRIVATE(int, m_iFontSize, iFontSize);    /* �����С */
    CC_PRIVATE(float, m_fAmchorX, fAmchorX);      /* AnchorPoint xֵ */
    CC_PRIVATE(float, m_fAmchorY, fAmchorY);      /* AnchorPoint yֵ */
    CC_PRIVATE(float, m_fScaleX, fScaleX);      /* X����(scale) */
    CC_PRIVATE(float, m_fScaleY, fScaleY);      /* Y����(scale) */
    CC_PRIVATE_BOOL(m_isVisible, Visible);      /* �Ƿ�ɼ� */
    CC_PRIVATE_BOOL(m_isEnable, Enable);        /* �Ƿ���� */
    CC_PRIVATE_BOOL(m_isTouchable, Touchable);  /* �Ƿ�ɵ�� */
    CC_PRIVATE_BOOL(m_isXLeft, XLeft);      /* �Ƿ�������� */
    CC_PRIVATE_BOOL(m_isXRight, XRight);    /* �Ƿ����Ҷ��� */
    CC_PRIVATE_BOOL(m_isXCenter, XCenter);  /* X�����Ƿ���ж��� */
    CC_PRIVATE_BOOL(m_isYTop, YTop);        /* �Ƿ����϶��� */
    CC_PRIVATE_BOOL(m_isYBottom, YBottom);  /* �Ƿ����¶��� */
    CC_PRIVATE_BOOL(m_isYCenter, YCenter);  /* Y�����Ƿ���ж��� */
    CC_PRIVATE_BOOL(m_isMaxWidth, MaxWidth);    /* ����Ƿ���� */
    CC_PRIVATE_BOOL(m_isMaxHeight, MaxHeight);  /* �߶��Ƿ���� */
    CCString* m_sDes;           /* �ؼ��ַ������� */
    GW_XML_PRIVATE_CHAR(m_sScale9bg, sScale9bg);      /* ����ͼƬ·�� */
    GW_XML_PRIVATE_CHAR(m_sScale9bgDown, sScale9bgDown)/* ����ͼƬ·��:down״̬ */
    GW_XML_PRIVATE_CHAR(m_sText, sText);          /* �ı� */
	GW_XML_PRIVATE_CHAR(m_sBg, sBg);          /* ����ͼƬ */
	GW_XML_PRIVATE_CHAR(m_sPlist, sPlist);          /* ���������ļ� */
	GW_XML_PRIVATE_CHAR(m_sAnimation, sAnimation);  /* �����ļ� */
	CC_PRIVATE(int, m_iLoops, iLoops);                  /* ����ѭ������ */
	CC_PRIVATE(float, m_fDelay, fDelay);      /* ���������ٶ� */
	GW_XML_PRIVATE_CHAR(m_sAnimationName, sAnimationName);  /* �������� */
public:
    const char* getsDes();
    void setsDes(const char* _sDes);

};


#endif