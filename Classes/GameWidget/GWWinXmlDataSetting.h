/*
    �ļ�����    GWWinXmlDataSetting.h
    �衡����    �ؼ�XML���Խṹ������
   
*/
#ifndef __GW_WIN_XML_DATA_SETTING_H__
#define __GW_WIN_XML_DATA_SETTING_H__

/* XML�ļ��Ľڵ�����*/
#define XML_VALUE_enWinType "enWinType"     // �ؼ�����
#define XML_VALUE_x "x"                     // x����
#define XML_VALUE_y "y"                     // y����
#define XML_VALUE_width "width"             // ��
#define XML_VALUE_height "height"           // ��
#define XML_VALUE_alpha "alpha"             // ͸����
#define XML_VALUE_scaleX "scaleX"           // x����
#define XML_VALUE_scaleY "scaleY"           // y����
#define XML_VALUE_visible "visible"         // �Ƿ�ɼ�
#define XML_VALUE_enable "enable"           // �ǵĿ���
#define XML_VALUE_touchable "touchable"     // �Ƿ�ɵ��
#define XML_VALUE_des "des"                 // �ؼ��ַ�������
#define XML_VALUE_scale9bg "scale9bg"       // ����ͼƬ·��
#define XML_VALUE_scale9bgDown "scale9bgDown"       // ����ͼƬ·��
#define XML_VALUE_text "text"               // �ı�
#define XML_VALUE_marginH "marginH"         // ˮƽ����marginֵ
#define XML_VALUE_marginV "marginV"         // ��ֱ����marginֵ
#define XML_VALUE_max "max"                 // ���ֵ
#define XML_VALUE_bg "bg"					// ����ͼƬ·��
#define XML_VALUE_AnchorX "anchorX"			// AnchorPoint x
#define XML_VALUE_AnchorY "anchorY"			// AnchorPoint y
#define XML_VALUE_fontSize "fontSize"		// �����С
#define XML_VALUE_Plist "plist"		// ���������ļ�
#define XML_VALUE_Animation "animation"		// ������Դ�ļ�
#define XML_VALUE_AnimationName "animationName"		// ������Դ�ļ�
#define XML_VALUE_Loops "loops"		// ����ѭ������
#define XML_VALUE_Delay "delay"		// ���������ٶ�


/* xml�ļ����ֽڵ����� */
#define XML_TEXT_true "true"        // true
#define XML_TEXT_false "false"      // false
#define XML_TEXT_right "right"      // x���꿿����
#define XML_TEXT_left "left"        // x���꿿����
#define XML_TEXT_bottom "bottom"     // y���꿿����
#define XML_TEXT_top "top"         // y���꿿����
#define XML_TEXT_center "center"     // ����

#include "cocos2d.h"
#include "GWWinXmlData.h"
#include "GlobalSetting\GlobalDefine.h"

USING_NS_CC;

class GWWinXmlDataSetting : public CCObject {
public:
    CREATE_FUNC(GWWinXmlDataSetting);
    virtual bool init();

    /* ��XML data����ֵ */
    void setWinXmlData(GWWinXmlData* xmlData, const char* sName, const char* sText);
public:
    /* ------------- ����xml�еĽڵ��ַ������ݸ�ֵ --------------- */
    GW_SET_XML(EnWinType);/* ���ÿؼ����� */
    GW_SET_XML(iX);/* ����X���� */
    GW_SET_XML(iY);/* ����Y���� */
    GW_SET_XML(iWidth);/* ���ÿ� */
    GW_SET_XML(iHeight);/* ���ø� */
    GW_SET_XML(iAlpha);/* ����͸���� */
    GW_SET_XML(fScaleX);/* ����X����(scale) */
    GW_SET_XML(fScaleY);/* ����Y����(scale) */
    GW_SET_XML(Visible);/* �����Ƿ�ɼ� */
    GW_SET_XML(Enable);/* �����Ƿ���� */
    GW_SET_XML(Touchable);/* �����Ƿ�ɵ�� */
    GW_SET_XML(Des);/* ���ÿؼ��ַ������� */
    GW_SET_XML(Scale9bg);/* ���þ���ͼƬ·�� */
    GW_SET_XML(Scale9bgDown);/* ���þ���ͼƬ·��:down״̬ */
    GW_SET_XML(sText);/* �����ı� */
	GW_SET_XML(sBgPath);/* ���ñ���ͼƬ */
    GW_SET_XML(fAnchorX);/* AnchorPoint xֵ */
    GW_SET_XML(fAnchorY);/* AnchorPoint yֵ */
    GW_SET_XML_INT(iMarginH);/* ˮƽ����marginֵ */
    GW_SET_XML_INT(iMarginV);/* ��ֱ����marginֵ */
    GW_SET_XML_INT(iFontSize);/* �����С */
	GW_SET_XML_INT(iLoops);/* ����ѭ������ */
	GW_SET_XML(fDelay);/* ���������ٶ� */
	GW_SET_XML(sAnimation);/* ������Դ·�� */
	GW_SET_XML(sAnimationName);/* ������Դ���� */
	GW_SET_XML(sPlist);/* ���������ļ� */
};

#endif