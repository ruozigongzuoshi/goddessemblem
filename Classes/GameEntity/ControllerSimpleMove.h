/*
    文件名：    ControllerSimpleMove.h
    描　述：    简单移动控制器，按照指定坐标路径移动
    
*/
#ifndef _ControllerSimpleMove_H_
#define _ControllerSimpleMove_H_

#include "ControllerMoveBase.h"
#include "Entity.h"
#include "PosBase.h"

typedef void (CCObject::*SEL_CallFuncM) (CCObject*);  
#define callfuncL_selector(_SELECTOR) (SEL_CallFuncM)(&_SELECTOR)  

class MoveEnd {
public:
    MoveEnd(CCObject* target, SEL_CallFuncM selector);
    ~MoveEnd();

    void moveEnd();

private:
    SEL_CallFuncM m_selector;
    CCObject* m_target;
};

class ControllerSimpleMove : public ControllerMoveBase {
public:
	ControllerSimpleMove();
	~ControllerSimpleMove();

	static ControllerSimpleMove* create(Entity* entity);
	bool init(Entity* entity);

	static ControllerSimpleMove* create(Entity* entity, SEL_CallFuncM selector);
	bool init(Entity* entity, SEL_CallFuncM selector);

	void checkMoveUpdate(float delta);

	/* 按照给定的坐标点移动 */
    void moveByPosList(CCArray* posList);
    /* 按照给定的坐标点和移动速度 */
	void moveByPosList(CCArray* posList, int iSpeed);
    /* 按照给定的坐标点、速度、移动间隔时间移动 */
    void moveByPosList(CCArray* posList, int iSpeed, int iSpanTime);

	/* 按照给定坐标移动 */
	void moveByPos(PosBase* pos);
private:
	/* 移动一步 */
	void moveOneStep();

	/* 设置下一个移动目的点 */
	void nextMovePos();
private:
	CCArray* m_movePosList; // 移动目的列表
	PosBase* m_curDestPos;  // 当前移动目的地

    float m_MoveSpan;       // 移动间隔时间
    float m_fMoveTimeCount; // 计时器

    /* 移动结束回调 */
    MoveEnd* m_moveEnd;
};



#endif