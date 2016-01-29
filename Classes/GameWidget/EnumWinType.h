/*
    �ļ�����    EnumWinType.h
    �衡����    �ؼ�����
*/
#ifndef __ENUM_WIN_TYPE_H__
#define __ENUM_WIN_TYPE_H__

/* �ؼ������ַ��� */
#define WINType_C_en_Win_None           "GWNone"            // ��
#define WINType_C_en_Win_Scale9Win      "GWScale9Win"       // �����촰��
#define WINType_C_en_Win_Div            "GWDiv"             // ����
#define WINType_C_en_Win_Scale9Button   "GWScale9Button"    // �����찴ť
#define WINType_C_en_Win_NormalWin		"GWNormalWin"		// ��ͨ����
#define WINType_C_en_Win_AnimationWin		"GWAnimationWin"		// ��������
#define WINType_C_en_Win_Label			"GWLabel"			// ��ǩ

enum EnumWinType {
    en_Win_None,
    en_Win_Scale9Win,       /* �����촰�� */
    en_Win_Div,             /* ���� */
    en_Win_Scale9Button,    /* �����찴ť */
	en_Win_NormalWin,		/* ��ͨ���� */
	en_Win_AnimationWin,		/* �������� */
	en_Win_Label,			/* ��ͨ��ǩ */
};

#endif