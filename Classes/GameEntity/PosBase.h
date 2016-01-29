/*
    �ļ�����    PosBase.h
    �衡����    ����������
    
*/
#ifndef _PosBase_H_
#define _PosBase_H_

#include "cocos2d.h"
USING_NS_CC;

class PosBase : public CCNode {
public:
	PosBase();
	~PosBase();

	static PosBase* create(CCPoint pos);
	static PosBase* create(CCPoint pos, bool isDebug);
	bool init(CCPoint pos);
	bool init(CCPoint pos, bool isDebug);

	CC_SYNTHESIZE(CCPoint, m_pos, Pos);

	/* ������رյ���ģʽ */
	void setDebug(bool isDebug);

protected:
	/* �Ƿ�Ϊ����״̬ */
	bool m_isDebug;
};

#endif