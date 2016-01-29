#include "MonsterPos.h"

MonsterPos::MonsterPos() {
	m_pos = CCPointMake(0, 0);
	m_isDebug = false;
}

MonsterPos::~MonsterPos() {
}

MonsterPos* MonsterPos::create( CCPoint pos ) {
	MonsterPos* tPos = new MonsterPos();

	if(tPos && tPos->init(pos)) {
		tPos->autorelease();
	}
	else {
		CC_SAFE_DELETE(tPos);
	}

	return tPos;
}

MonsterPos* MonsterPos::create( CCPoint pos, bool isDebug ) {
	MonsterPos* tPos = new MonsterPos();

	if(tPos && tPos->init(pos, isDebug)) {
		tPos->autorelease();
	}
	else {
		CC_SAFE_DELETE(tPos);
	}

	return tPos;
}
bool MonsterPos::init( CCPoint pos ) {
	bool bRet = false;

	do {
		setPos(pos);
		bRet = true;
	} while (0);

	return bRet;
}

bool MonsterPos::init( CCPoint pos, bool isDebug ) {
	bool bRet = false;

	do {
		CC_BREAK_IF(! init(pos));

		m_isDebug = isDebug;

		bRet = true;
	} while (0);

	return bRet;
}

void MonsterPos::draw() {
	/* »æÖÆ²âÊÔÔ² */
	if(m_isDebug) {
		glLineWidth(4);
		ccDrawColor4F(0.1, 0.2, 0.3, 1.0);
		ccDrawCircle(m_pos, MONSTER_RADIUS, 360, 20, false);
		ccDrawColor4F(1.0, 1.0, 1.0, 1.0);
		glLineWidth(1);
	}
}

bool MonsterPos::isClickMe( CCPoint pos ) {
	CCPoint srcPos = CCPoint(m_pos.x - MONSTER_RADIUS, m_pos.y + MONSTER_RADIUS);
	CCPoint destPos = CCPoint(m_pos.x + MONSTER_RADIUS, m_pos.y - MONSTER_RADIUS);

	if(pos.x >= srcPos.x && pos.x <= destPos.x && pos.y <= srcPos.y && pos.y >= destPos.y) {
		return true;
	}

	return false;
}
