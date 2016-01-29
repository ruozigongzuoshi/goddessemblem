/*
    文件名：    GWAnimationWin.h
    描　述：    动画窗口
   
*/
#ifndef __GW_ANIMATION_H__
#define __GW_ANIMATION_H__

#include "GWBase.h"

class GWAnimationWin : public GWBase {
public:
    GWAnimationWin();
    ~GWAnimationWin();

    CREATE_FUNC(GWAnimationWin);
    virtual bool init();

    virtual void setAnchorPoint(const CCPoint& anchorPoint);

    void setBG(const char* sPath);

	CCSprite* getSprite();

	CC_PRIVATE(int, m_loops, Loops);
	CC_PRIVATE(float, m_delay, Delay);
	CC_PRIVATE(const char*, m_animationPath, AnimationPath);
	CC_PRIVATE(const char*, m_animationPlistPath, AnimationPlistPath);
	CC_PRIVATE(const char*, m_animationName, AnimationName);

	void runAction();
    
private:
    CCSprite* m_sprite;
	//CCSpriteFrameCache* m_frameCache;
	//CCAnimation* m_animation;
	//CCAnimate* m_animate;
	//float delay;
	//unsigned int iLoops;

};

#endif