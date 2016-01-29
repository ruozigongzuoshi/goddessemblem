/*
    文件名：    GWNormalWin.h
    描　述：    普通窗口
   
*/
#ifndef __GW_NORMAL_H__
#define __GW_NORMAL_H__

#include "GWBase.h"

class GWNormalWin : public GWBase {
public:
    GWNormalWin();
    ~GWNormalWin();

    CREATE_FUNC(GWNormalWin);
    virtual bool init();

    virtual void setAnchorPoint(const CCPoint& anchorPoint);

    void setBG(const char* sPath);

	CCSprite* getSprite();
    
private:
    CCSprite* m_sprite;
};

#endif