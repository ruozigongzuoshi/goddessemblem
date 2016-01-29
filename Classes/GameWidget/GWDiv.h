/*
    文件名：    GWDiv.h
    描　述：    Div控件:
                一个空白的layer,可以添加其他控件
    
*/
#ifndef __GW_DIV_H__
#define __GW_DIV_H__

#include "GWBase.h"

class GWDiv : public GWBase {
public:
    GWDiv();
    ~GWDiv();

    CREATE_FUNC(GWDiv);
    virtual bool init();

    virtual void draw( void );
    
private:
    int iOffset;
};

#endif