/*
    �ļ�����    GWWinSyetem.h
    �衡����    �ؼ�����
*/
#ifndef __GW_BASE_H__
#define __GW_BASE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EnumWinType.h"
#include "GlobalSetting/GlobalDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

/*
 * �̳���CCControl
 * �����Կ�����Cocos2d-x�Ļ���
 * �Զ���ؼ�������̳�GWBase.
 */
class GWBase : public CCControl {
public:
    GWBase();
    ~GWBase();

private:
    int m_ID;       /* �ؼ�ID */
    int m_iOrder;   /* ��� */
    CC_PRIVATE_BOOL(m_isHasParentWin, HasParentWin);  /* �Ƿ��и��ؼ� */
    CC_PRIVATE_BOOL(m_isHasChildWin, HasChildWin);    /* �Ƿ����ӿؼ� */
    EnumWinType mEnWinType; /* �ؼ����� */
public:
    const int getiWinID();         /* ��ȡ�ؼ�ID*/
    void setiWinID(int _ID);         /* ���ÿؼ�ID*/
    const int getiOrder();
    void setiOrder(int _iOrder);
    const EnumWinType getEnWinType();
    void setEnWinType(EnumWinType _mEnWinType);
};

#endif