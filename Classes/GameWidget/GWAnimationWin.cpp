#include "GWAnimationWin.h"
#include "AnimationUtil.h"

GWAnimationWin::GWAnimationWin() {
	
}

GWAnimationWin::~GWAnimationWin() {
	
}

bool GWAnimationWin::init() {
	GWBase::init();
	return true;
}

void GWAnimationWin::setBG( const char* sPath ) {
	m_sprite = CCSprite::create(sPath);
	this->addChild(m_sprite);
}

void GWAnimationWin::setAnchorPoint( const CCPoint& anchorPoint ) {
    CCNode::setAnchorPoint(anchorPoint);

    /* child的描点也要设置 */
    m_sprite->setAnchorPoint(anchorPoint);
}

CCSprite* GWAnimationWin::getSprite(){
	return m_sprite;
}

void GWAnimationWin::runAction(){
	CCSpriteFrameCache* m_frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	m_frameCache->addSpriteFramesWithFile(m_animationPlistPath, m_animationPath);
	CCAnimation* m_animation = AnimationUtil::createAnimWithSingleFrameN(m_animationName, m_delay, m_loops);
	CCAnimate* m_animate = CCAnimate::create(m_animation);
	m_sprite->runAction(CCAnimate::create(m_animation));
}

