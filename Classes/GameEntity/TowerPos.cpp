#include "TowerPos.h"

TowerPos::TowerPos() {
    m_pos = CCPointMake(0, 0);
    m_isDebug = false;
}

TowerPos::~TowerPos() {
}

TowerPos* TowerPos::create( CCPoint pos ) {
    TowerPos* tPos = new TowerPos();

    if(tPos && tPos->init(pos)) {
        tPos->autorelease();
    }
    else {
        CC_SAFE_DELETE(tPos);
    }

    return tPos;
}

TowerPos* TowerPos::create( CCPoint pos, bool isDebug ) {
    TowerPos* tPos = new TowerPos();

    if(tPos && tPos->init(pos, isDebug)) {
        tPos->autorelease();
    }
    else {
        CC_SAFE_DELETE(tPos);
    }

    return tPos;
}
bool TowerPos::init( CCPoint pos ) {
    bool bRet = false;

    do {
        CC_BREAK_IF(! PosBase::init(pos));
        bRet = true;
    } while (0);

    return bRet;
}

bool TowerPos::init( CCPoint pos, bool isDebug ) {
    bool bRet = false;

    do {
        CC_BREAK_IF(! PosBase::init(pos, isDebug));

        bRet = true;
    } while (0);

    return bRet;
}

void TowerPos::draw() {
    /* »æÖÆ²âÊÔ·½¿ò */
    if(m_isDebug) {
        glLineWidth(5);	// ÉèÖÃ»­±Ê´ÖÏ¸
		ccDrawColor4F(0.3, 0.0, 0.3, 1.0);
		/* »æÖÆ¾ØÐÎ */
        CCPoint srcPos = CCPoint(m_pos.x - RADIUS, m_pos.y + RADIUS);
        CCPoint destPos = CCPoint(m_pos.x + RADIUS, m_pos.y - RADIUS);
        ccDrawRect(srcPos, destPos);
		ccDrawColor4F(1.0, 1.0, 1.0, 1.0);
        glLineWidth(1);	// »Ö¸´»­±Ê´ÖÏ¸
    }
}

bool TowerPos::isClickMe( CCPoint pos ) {
    CCPoint srcPos = CCPoint(m_pos.x - RADIUS, m_pos.y + RADIUS);
    CCPoint destPos = CCPoint(m_pos.x + RADIUS, m_pos.y - RADIUS);

    if(pos.x >= srcPos.x && pos.x <= destPos.x && pos.y <= srcPos.y && pos.y >= destPos.y) {
        return true;
    }

    return false;
}

