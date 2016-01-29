/*
    �ļ�����    PosLoadUtil.h
    �衡����    ���������ع���
    
*/
#ifndef _PosLoadUtil_H_
#define _PosLoadUtil_H_

#include "cocos2d.h"
#include "EnumPosType.h"
USING_NS_CC;

class PosLoadUtil : public CCNode {
public:
	static PosLoadUtil* sharedPosLoadUtil();
	virtual bool init();

	/* 
		�����������ʹ�plist�����ļ��ж�ȡ������� 
		sFilePath�������ļ�·��
		enPosType�������������
		container�����������������
		iLevel���������container���ò�����ʾ��������������еĲ��
		isDebug���Ƿ�������ģʽ
	*/
	CCArray* loadPosWithFile(
		const char* sFilePath,
		EnumPosType enPosType, 
		CCNode* container, 
		int iLevel, 
		bool isDebug);
private:
	static PosLoadUtil* m_posLoadUtil;
};

#endif