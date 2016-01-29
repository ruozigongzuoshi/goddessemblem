/*
    文件名：    GlobalDefine.h
    描　述：    游戏中定义的宏
    
*/
#ifndef __GLOBAL_DEFINE_H__

#include "FileLoad\StringUtil.h"
#include "cocos2d.h"

#define CC_PRIVATE(varType, varName, funName)\
private: varType varName;\
public: varType get##funName(void) const { return varName; }\
public: void set##funName(varType var){ varName = var; }

/* 创建bool私有变量，包括get和set方法 */
#define CC_PRIVATE_BOOL(varName, funName)\
private: bool varName;\
public: bool is##funName(void) const { return varName; }\
public: void set##funName(bool var){ varName = var; }

/* 消息派发 */
#define NOTIFY cocos2d::CCNotificationCenter::sharedNotificationCenter()

/* 字符串工具类 */
#define STRING_UTIL StringUtil::sharedStrUtil()

/* 例子:CCString* m_sDes;  */
#define GW_XML_PRIVATE_CHAR(varName, funName)\
private: CCString* varName;\
public: const char* get##funName(void) { return varName->getCString(); }\
public: void set##funName(const char* var){ \
CC_SAFE_RELEASE(varName); \
varName = CCString::createWithFormat(var); \
CC_SAFE_RETAIN(varName); \
}

/* 普通set函数, 为了减少重复工作, 例子:void setXmliX(GWWinXmlData* xmlData, const char* sText); */
#define GW_SET_XML(funName)\
public: void setXml##funName(GWWinXmlData* xmlData, const char* sText);

/* 
    整型数字set函数,为了减少重复工作, 例子:
    void GWWinXmlDataSetting::setXmlfScaleY( GWWinXmlData* xmlData, const char* sText ) {
        xmlData->setfScaleY(atof(sText));
    } 
*/
#define GW_SET_XML_INT(funName)\
public: void setXml##funName( GWWinXmlData* xmlData, const char* sText ) {\
xmlData->set##funName(atoi(sText));\
}

/* 将整型转换为字符串 */
#define INT_TO_CHAR(num) StringUtil::sharedStrUtil()->transIntToStr(num)
#endif

