/*
    文件名：    PosBase.h
    描　述：    坐标对象基类
    
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

	/* 开启或关闭调试模式 */
	void setDebug(bool isDebug);

protected:
	/* 是否为调试状态 */
	bool m_isDebug;
};

#endif