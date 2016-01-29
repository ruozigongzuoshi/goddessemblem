#include "GWNormalWin.h"

GWNormalWin::GWNormalWin() {
	m_sprite = NULL;
}

GWNormalWin::~GWNormalWin() {

}

bool GWNormalWin::init() {
	GWBase::init();
	return true;
}

void GWNormalWin::setBG( const char* sPath ) {
	m_sprite = CCSprite::create(sPath);
	this->addChild(m_sprite);
}

void GWNormalWin::setAnchorPoint( const CCPoint& anchorPoint ) {
    CCNode::setAnchorPoint(anchorPoint);

    /* child的描点也要设置 */
	if(m_sprite != NULL)
		m_sprite->setAnchorPoint(anchorPoint);
}

CCSprite* GWNormalWin::getSprite(){
	return m_sprite;
}
