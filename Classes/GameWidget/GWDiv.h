/*
    �ļ�����    GWDiv.h
    �衡����    Div�ؼ�:
                һ���հ׵�layer,������������ؼ�
    
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