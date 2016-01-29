/*
    文件名：    GWWinXmlDataSetting.h
    描　述：    控件XML属性结构设置器
   
*/
#ifndef __GW_WIN_XML_DATA_SETTING_H__
#define __GW_WIN_XML_DATA_SETTING_H__

/* XML文件的节点名称*/
#define XML_VALUE_enWinType "enWinType"     // 控件类型
#define XML_VALUE_x "x"                     // x坐标
#define XML_VALUE_y "y"                     // y坐标
#define XML_VALUE_width "width"             // 宽
#define XML_VALUE_height "height"           // 高
#define XML_VALUE_alpha "alpha"             // 透明度
#define XML_VALUE_scaleX "scaleX"           // x缩放
#define XML_VALUE_scaleY "scaleY"           // y缩放
#define XML_VALUE_visible "visible"         // 是否可见
#define XML_VALUE_enable "enable"           // 是的可用
#define XML_VALUE_touchable "touchable"     // 是否可点击
#define XML_VALUE_des "des"                 // 控件字符串描述
#define XML_VALUE_scale9bg "scale9bg"       // 九妹图片路径
#define XML_VALUE_scale9bgDown "scale9bgDown"       // 九妹图片路径
#define XML_VALUE_text "text"               // 文本
#define XML_VALUE_marginH "marginH"         // 水平方向margin值
#define XML_VALUE_marginV "marginV"         // 垂直方向margin值
#define XML_VALUE_max "max"                 // 最大值
#define XML_VALUE_bg "bg"					// 背景图片路径
#define XML_VALUE_AnchorX "anchorX"			// AnchorPoint x
#define XML_VALUE_AnchorY "anchorY"			// AnchorPoint y
#define XML_VALUE_fontSize "fontSize"		// 字体大小
#define XML_VALUE_Plist "plist"		// 动画配置文件
#define XML_VALUE_Animation "animation"		// 动画资源文件
#define XML_VALUE_AnimationName "animationName"		// 动画资源文件
#define XML_VALUE_Loops "loops"		// 动画循环次数
#define XML_VALUE_Delay "delay"		// 动画播放速度


/* xml文件部分节点内容 */
#define XML_TEXT_true "true"        // true
#define XML_TEXT_false "false"      // false
#define XML_TEXT_right "right"      // x坐标靠最右
#define XML_TEXT_left "left"        // x坐标靠最左
#define XML_TEXT_bottom "bottom"     // y坐标靠最下
#define XML_TEXT_top "top"         // y坐标靠最上
#define XML_TEXT_center "center"     // 居中

#include "cocos2d.h"
#include "GWWinXmlData.h"
#include "GlobalSetting\GlobalDefine.h"

USING_NS_CC;

class GWWinXmlDataSetting : public CCObject {
public:
    CREATE_FUNC(GWWinXmlDataSetting);
    virtual bool init();

    /* 给XML data对象赋值 */
    void setWinXmlData(GWWinXmlData* xmlData, const char* sName, const char* sText);
public:
    /* ------------- 根据xml中的节点字符串内容赋值 --------------- */
    GW_SET_XML(EnWinType);/* 设置控件类型 */
    GW_SET_XML(iX);/* 设置X坐标 */
    GW_SET_XML(iY);/* 设置Y坐标 */
    GW_SET_XML(iWidth);/* 设置宽 */
    GW_SET_XML(iHeight);/* 设置高 */
    GW_SET_XML(iAlpha);/* 设置透明度 */
    GW_SET_XML(fScaleX);/* 设置X缩放(scale) */
    GW_SET_XML(fScaleY);/* 设置Y缩放(scale) */
    GW_SET_XML(Visible);/* 设置是否可见 */
    GW_SET_XML(Enable);/* 设置是否可用 */
    GW_SET_XML(Touchable);/* 设置是否可点击 */
    GW_SET_XML(Des);/* 设置控件字符串描述 */
    GW_SET_XML(Scale9bg);/* 设置九妹图片路径 */
    GW_SET_XML(Scale9bgDown);/* 设置九妹图片路径:down状态 */
    GW_SET_XML(sText);/* 设置文本 */
	GW_SET_XML(sBgPath);/* 设置背景图片 */
    GW_SET_XML(fAnchorX);/* AnchorPoint x值 */
    GW_SET_XML(fAnchorY);/* AnchorPoint y值 */
    GW_SET_XML_INT(iMarginH);/* 水平方向margin值 */
    GW_SET_XML_INT(iMarginV);/* 垂直方向margin值 */
    GW_SET_XML_INT(iFontSize);/* 字体大小 */
	GW_SET_XML_INT(iLoops);/* 动画循环次数 */
	GW_SET_XML(fDelay);/* 动画播放速度 */
	GW_SET_XML(sAnimation);/* 动画资源路径 */
	GW_SET_XML(sAnimationName);/* 动画资源名字 */
	GW_SET_XML(sPlist);/* 动画配置文件 */
};

#endif