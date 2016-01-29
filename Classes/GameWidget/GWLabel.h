/*
    文件名：    GWLabel.h
    描　述：    标签控件
*/
#ifndef __GW_LABEL_H__
#define __GW_LABEL_H__

#include "GWBase.h"

class GWLabel : public GWBase {
public:
    GWLabel();
    ~GWLabel();

    CREATE_FUNC(GWLabel);
    virtual bool init();

    virtual void setAnchorPoint(const CCPoint& anchorPoint);

    void setsText(const char* sText);
    void setsText(int iValue);
    void setiFontSize(int iFontSize);
    void setColorRGB(int r, int g, int b);
private:
    CCLabelTTF* m_label;
};

#endif