/*
    �ļ�����    StringUtil.h
    �衡����    �ַ���������
    
*/
#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include "cocos2d.h"

using namespace cocos2d;

class StringUtil : public CCObject {
public:
    static StringUtil* sharedStrUtil();

    bool init();

    /** �÷ָ����ָ��ַ����������ŵ�һ���б��У��б��еĶ���ΪCCString */
    CCArray* split(const char* srcStr, const char* sSep);

    /* ת������Ϊ�ַ��� */
    const char* transIntToStr(int iValue);
private:
    static StringUtil* mStringUtil;

    /* ת������Ϊ�ַ��� */
    CCString* transIntToCCStr(int iValue);
};

#endif