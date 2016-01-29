/*
    �ļ�����    GWScale9Win.h
    �衡����    �����촰��
*/
#ifndef __GW_SCALE9_WIN_H__
#define __GW_SCALE9_WIN_H__

#include "GWBase.h"

class GWScale9Win : public GWBase {
public:
    GWScale9Win();
    ~GWScale9Win();

    CREATE_FUNC(GWScale9Win);
    virtual bool init();
public:
    /* ���þ��ñ��� */
    void setScale9BG(const char* sPath, CCSize size);
private:
    void setScale9Sprite(CCScale9Sprite* scale9Sprite);

    /* ������sprite */
    CCScale9Sprite* mScale9Sprite;
};

#endif