/*
    �ļ�����    GlobalDefine.h
    �衡����    ��Ϸ�ж���ĺ�
    
*/
#ifndef __GLOBAL_DEFINE_H__

#include "FileLoad\StringUtil.h"
#include "cocos2d.h"

#define CC_PRIVATE(varType, varName, funName)\
private: varType varName;\
public: varType get##funName(void) const { return varName; }\
public: void set##funName(varType var){ varName = var; }

/* ����bool˽�б���������get��set���� */
#define CC_PRIVATE_BOOL(varName, funName)\
private: bool varName;\
public: bool is##funName(void) const { return varName; }\
public: void set##funName(bool var){ varName = var; }

/* ��Ϣ�ɷ� */
#define NOTIFY cocos2d::CCNotificationCenter::sharedNotificationCenter()

/* �ַ��������� */
#define STRING_UTIL StringUtil::sharedStrUtil()

/* ����:CCString* m_sDes;  */
#define GW_XML_PRIVATE_CHAR(varName, funName)\
private: CCString* varName;\
public: const char* get##funName(void) { return varName->getCString(); }\
public: void set##funName(const char* var){ \
CC_SAFE_RELEASE(varName); \
varName = CCString::createWithFormat(var); \
CC_SAFE_RETAIN(varName); \
}

/* ��ͨset����, Ϊ�˼����ظ�����, ����:void setXmliX(GWWinXmlData* xmlData, const char* sText); */
#define GW_SET_XML(funName)\
public: void setXml##funName(GWWinXmlData* xmlData, const char* sText);

/* 
    ��������set����,Ϊ�˼����ظ�����, ����:
    void GWWinXmlDataSetting::setXmlfScaleY( GWWinXmlData* xmlData, const char* sText ) {
        xmlData->setfScaleY(atof(sText));
    } 
*/
#define GW_SET_XML_INT(funName)\
public: void setXml##funName( GWWinXmlData* xmlData, const char* sText ) {\
xmlData->set##funName(atoi(sText));\
}

/* ������ת��Ϊ�ַ��� */
#define INT_TO_CHAR(num) StringUtil::sharedStrUtil()->transIntToStr(num)
#endif

