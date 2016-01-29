/*
    文件名：    EnumWinType.h
    描　述：    控件类型
*/
#ifndef __ENUM_WIN_TYPE_H__
#define __ENUM_WIN_TYPE_H__

/* 控件类型字符串 */
#define WINType_C_en_Win_None           "GWNone"            // 无
#define WINType_C_en_Win_Scale9Win      "GWScale9Win"       // 可拉伸窗口
#define WINType_C_en_Win_Div            "GWDiv"             // 区域
#define WINType_C_en_Win_Scale9Button   "GWScale9Button"    // 可拉伸按钮
#define WINType_C_en_Win_NormalWin		"GWNormalWin"		// 普通窗口
#define WINType_C_en_Win_AnimationWin		"GWAnimationWin"		// 动画窗口
#define WINType_C_en_Win_Label			"GWLabel"			// 标签

enum EnumWinType {
    en_Win_None,
    en_Win_Scale9Win,       /* 可拉伸窗口 */
    en_Win_Div,             /* 区域 */
    en_Win_Scale9Button,    /* 可拉伸按钮 */
	en_Win_NormalWin,		/* 普通窗口 */
	en_Win_AnimationWin,		/* 动画窗口 */
	en_Win_Label,			/* 普通标签 */
};

#endif