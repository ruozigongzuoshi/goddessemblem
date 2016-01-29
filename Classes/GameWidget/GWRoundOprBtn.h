/*
    �ļ�����    GWRoundOprBtn.h
    �衡����    �ų�Բ�εĲ�����ť
    
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