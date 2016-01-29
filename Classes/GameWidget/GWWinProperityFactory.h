/*
    �ļ�����    GWWinProperityFactory.h
    �衡����    �ؼ����Լӹ���
              ��Ҫ�������ÿؼ�������
    
*/
#ifndef __GW_WIN_PROPERITY_FACTORY_H__
#define __GW_WIN_PROPERITY_FACTORY_H__

#include "cocos2d.h"
#include "GWBase.h"
#include "EnumWinType.h"
#include "GWWinXmlData.h"
#include "GWDiv.h"
#include "GWScale9Button.h"
#include "GWScale9Win.h"
#include "GWAnimationWin.h"
#include "GWLabel.h"
#include "GWNormalWin.h"
USING_NS_CC;

//class GWNormalWin;
//class GWAnimationWin;
//class GWLabel;
class GWWinProperityFactory : public CCObject {
public:
    CREATE_FUNC(GWWinProperityFactory);
    virtual bool init();

public:
    /* ���ؼ���������(���·�~) */
    void dressPropertiesByType( GWBase* mmWin, GWWinXmlData* xmlData );

private:
    /* ���ÿؼ���������,���пؼ����������� */
    void dressBaseProperties(GWBase* mmWin, GWWinXmlData* xmlData);

private:
    /* ��ȡxml�����ļ����趨�Ŀ������ */
    CCSize getSizeProp(GWBase* parent, GWWinXmlData* xmlData);

    void dressGWButton(GWScale9Button* mDiv, GWWinXmlData* xmlData);
    void dressGWDiv(GWDiv* mDiv, GWWinXmlData* xmlData);
    void dressGWScale9Win(GWScale9Win* mScale9Win, GWWinXmlData* xmlData);
	void dressGWNormalWin(GWNormalWin* mNormalWin, GWWinXmlData* xmlData);
	void dressGWAnimationWin(GWAnimationWin* mAnimationWin,GWWinXmlData*  xmlData);
	void dressGWLabel(GWLabel* mmLabel, GWWinXmlData* xmlData);
};

#endif