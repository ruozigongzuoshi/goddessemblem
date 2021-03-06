/*
    文件名：    ControllerMoveBase.h
    描　述：    移动控制器基类
    
*/
#ifndef _ControllerMoveBase_H_
#define _ControllerMoveBase_H_

#include "ControllerBase.h"
#include "Entity.h"

#define SPEED 1

/* 检查移动的间隔时间，时间越短，移动越快 */
#define CHECK_MOVE_SPEED_LVL1 0.1f  
#define CHECK_MOVE_SPEED_LVL2 0.04f
#define CHECK_MOVE_SPEED_LVL3 0.03f

class ControllerMoveBase : public ControllerBase {
public:
    ControllerMoveBase();
    ~ControllerMoveBase();

    CC_SYNTHESIZE(int, m_iSpeed, iSpeed);   // 移动速度
protected:
    Entity* m_entity;		// 实体对象
    bool m_isMoving;        // 是否正在移动
    bool m_isXLeft;		    // 标记x方向是否往左移
    bool m_isYUp;		    // 标记y方向是否往上移
    int m_iCheckMoveSpeed;  // 检查移动的间隔时间，时间越短，移动越快

    /* 给定当前坐标和目标坐标，计算出下一次要设置的坐标 */
    CCPoint getNextPos(CCPoint curPos, CCPoint destPos);
};


#endif