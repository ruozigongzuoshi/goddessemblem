/*
    �ļ�����    ControllerSimpleMove.h
    �衡����    ���ƶ�������������ָ������·���ƶ�
    
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

	/* ���ո�����������ƶ� */
    void moveByPosList(CCArray* posList);
    /* ���ո������������ƶ��ٶ� */
	void moveByPosList(CCArray* posList, int iSpeed);
    /* ���ո���������㡢�ٶȡ��ƶ����ʱ���ƶ� */
    void moveByPosList(CCArray* posList, int iSpeed, int iSpanTime);

	/* ���ո��������ƶ� */
	void moveByPos(PosBase* pos);
private:
	/* �ƶ�һ�� */
	void moveOneStep();

	/* ������һ���ƶ�Ŀ�ĵ� */
	void nextMovePos();
private:
	CCArray* m_movePosList; // �ƶ�Ŀ���б�
	PosBase* m_curDestPos;  // ��ǰ�ƶ�Ŀ�ĵ�

    float m_MoveSpan;       // �ƶ����ʱ��
    float m_fMoveTimeCount; // ��ʱ��

    /* �ƶ������ص� */
    MoveEnd* m_moveEnd;
};



#endif