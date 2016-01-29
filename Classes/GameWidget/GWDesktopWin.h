/*
    �ļ�����   GWWinManager.h
    �衡����    �ؼ���������
*/
#ifndef __GW_DESKTOP_WIN_H__
#define __GW_DESKTOP_WIN_H__

#include "cocos2d.h"
#include "GWBase.h"

USING_NS_CC;

class GWDesktopWin : public GWBase {
public:
    GWDesktopWin();
    ~GWDesktopWin();

    CREATE_FUNC(GWDesktopWin);
    virtual bool init();

    virtual void registerWithTouchDispatcher();

    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

    virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

    virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
public:
    /* ���һ���ؼ� */
    void addWin(GWBase* mmWin);

    /* ��ӿؼ�ID�Ϳؼ��ַ���������ֵ�� */
    void addDesID(int iWinID, const char* sDes);

    /* ����ID��ȡ�ؼ� */
    GWBase* getWinByID(int ID);

    /* ���ݿؼ��ַ���������ȡ�ؼ� */
    GWBase* getWinByDes(const char* sDes);

    /* ɾ�����пؼ� */
    void removeAllWins();
private:
    /* ������пؼ����ֵ�<GWBase, CCInteger> */
    CCDictionary* mWinDict;

    /* �ؼ��ַ��������Ϳؼ�ID��Ӧ��ֵ��<CCInteger*, const char*> */
    CCDictionary* mDesIDDict;
};

#endif