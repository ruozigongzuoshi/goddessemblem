/*
    文件名：    I18N.h
    描　述：    国际化工具
*/

#ifndef __I18N_H__
#define __I18N_H__

#include "cocos2d.h"
#include "EnumStrKey.h"

using namespace cocos2d;

class I18N : public CCObject {
public:
    /* 获取对象 */
    static I18N* shareI18N();
    
    /* 初始化 */
    virtual bool init();

    /* 根据Key值获取字符串,返回CCString对象 */
    CCString* getString(EnumStrKey enStrKey);

    /* 根据Key值获取字符串,返回const char*对象 */
    const char* getcString(EnumStrKey enStrKey);

	/* 根据整型的Key值获取字符串,返回const char*对象 */
	const char* getcStringByKey( int iKey );
private:    /* 私有方法 */
    /* 从配置文件中读取字符串，保存到字典里 */
    void loadStringsFromConf(const char* filePath);

private:    /* 成员变量 */
    /* I18N对象 */
    static I18N* mI18N;

    /* 游戏中用到的字符串字典 */
    CCDictionary* mStringDict;
};

#endif