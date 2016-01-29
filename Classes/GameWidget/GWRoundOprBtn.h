/*
    文件名：    GWRoundOprBtn.h
    描　述：    排成圆形的操作按钮
    
*/
#ifndef _GWRoundOprBtn_H_
#define _GWRoundOprBtn_H_

#include "GWBase.h"
#define DEFAULT_DISTANCE 120;
class GWRoundOprBtn : public GWBase {
public:
    virtual bool init();
	CREATE_FUNC(GWRoundOprBtn);

	static GWRoundOprBtn* createWithControlButtons(
		CCControlButton* btn1,
		CCControlButton* btn2, 
		CCControlButton* btn3, 
		CCControlButton* btn4);
	bool initWithControlButtons(
		CCControlButton* btn1,
		CCControlButton* btn2, 
		CCControlButton* btn3, 
		CCControlButton* btn4);

	void deleteMe();
private:
	void addOneBtn(CCNode* node, CCPoint pos);
};

#endif