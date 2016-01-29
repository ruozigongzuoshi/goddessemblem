/*
    �ļ�����    I18N.h
    �衡����    ���ʻ�����
*/

#ifndef __I18N_H__
#define __I18N_H__

#include "cocos2d.h"
#include "EnumStrKey.h"

using namespace cocos2d;

class I18N : public CCObject {
public:
    /* ��ȡ���� */
    static I18N* shareI18N();
    
    /* ��ʼ�� */
    virtual bool init();

    /* ����Keyֵ��ȡ�ַ���,����CCString���� */
    CCString* getString(EnumStrKey enStrKey);

    /* ����Keyֵ��ȡ�ַ���,����const char*���� */
    const char* getcString(EnumStrKey enStrKey);

	/* �������͵�Keyֵ��ȡ�ַ���,����const char*���� */
	const char* getcStringByKey( int iKey );
private:    /* ˽�з��� */
    /* �������ļ��ж�ȡ�ַ��������浽�ֵ��� */
    void loadStringsFromConf(const char* filePath);

private:    /* ��Ա���� */
    /* I18N���� */
    static I18N* mI18N;

    /* ��Ϸ���õ����ַ����ֵ� */
    CCDictionary* mStringDict;
};

#endif