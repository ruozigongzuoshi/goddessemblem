#include "ControllerSimpleMove.h"


ControllerSimpleMove::ControllerSimpleMove() {
	m_movePosList = NULL;
	m_curDestPos = NULL;
    m_fMoveTimeCount = 0;
    m_MoveSpan = 0;
	m_moveEnd = NULL;
}

ControllerSimpleMove::~ControllerSimpleMove() {
	CC_SAFE_RELEASE(m_movePosList);
	CC_SAFE_RELEASE(m_curDestPos);
    CC_SAFE_DELETE(m_moveEnd);
}

ControllerSimpleMove* ControllerSimpleMove::create( Entity* entity ) {
	ControllerSimpleMove* ctrlSimpleMove = new ControllerSimpleMove();

	if(ctrlSimpleMove && ctrlSimpleMove->init(entity)) {
		ctrlSimpleMove->autorelease();
	}
	else {
		CC_SAFE_DELETE(ctrlSimpleMove);
	}
	return ctrlSimpleMove;
}

bool ControllerSimpleMove::init( Entity* entity ) {
	bool bRet = false;

	do  {
		CC_SAFE_RETAIN(entity);
		this->m_entity = entity;

		m_movePosList = CCArray::create();
		CC_SAFE_RETAIN(m_movePosList);

		this->schedule(schedule_selector(ControllerSimpleMove::checkMoveUpdate));
		bRet = true;
	} while (0);

	return bRet;
}

ControllerSimpleMove* ControllerSimpleMove::create( Entity* entity, SEL_CallFuncM selector ) {
	ControllerSimpleMove* ctrlSimpleMove = new ControllerSimpleMove();

	if(ctrlSimpleMove && ctrlSimpleMove->init(entity, selector)) {
		ctrlSimpleMove->autorelease();
	}
	else {
		CC_SAFE_DELETE(ctrlSimpleMove);
	}
	return ctrlSimpleMove;
}

bool ControllerSimpleMove::init( Entity* entity, SEL_CallFuncM selector ) {
	bool bRet = false;

	do  {
		CC_SAFE_RETAIN(entity);
		this->m_entity = entity;

        m_movePosList = CCArray::create();
        CC_SAFE_RETAIN(m_movePosList);

		/* 创建一个MoveEnd对象 */
        m_moveEnd = new MoveEnd(entity, selector);

		this->schedule(schedule_selector(ControllerSimpleMove::checkMoveUpdate));
		bRet = true;
	} while (0);

	return bRet;
}

void ControllerSimpleMove::moveByPosList( CCArray* posList ) {
	if(posList == NULL || posList->count() < 1) {
		return;
	}

	this->m_movePosList->removeAllObjects();
    this->m_movePosList->addObjectsFromArray(posList);

	nextMovePos();

	this->m_isMoving = true;
}

void ControllerSimpleMove::moveByPosList( CCArray* posList, int iSpeed ) {
    this->m_iSpeed = iSpeed;
    moveByPosList(posList);
}

void ControllerSimpleMove::moveByPosList( CCArray* posList, int iSpeed, int iSpanTime ) {
    m_MoveSpan = iSpanTime;
    moveByPosList(posList, iSpeed);
}
void ControllerSimpleMove::checkMoveUpdate( float delta ) {
	if(m_isMoving) {
        m_fMoveTimeCount += delta * 1000;

        if(m_fMoveTimeCount >= m_MoveSpan) {
            m_fMoveTimeCount = 0;
		    moveOneStep();
        }
	}
}

void ControllerSimpleMove::moveOneStep() {
	CCSprite* sprite = m_entity->getSprite();

	if(sprite != NULL) {
		CCPoint entityPos = m_entity->getPosition();
		CCPoint curDestPos = m_curDestPos->getPos();
		
		/* 取得下一个移动坐标点 */
        entityPos = getNextPos(entityPos, curDestPos);

		/* 移动实体 */
		m_entity->setPosition(entityPos);

		/* 到达当前目的地，开始下一个目的地 */
		if(entityPos.x == curDestPos.x && entityPos.y == curDestPos.y) {
			if(m_movePosList->count() > 0) {
				nextMovePos();
			}
			else {
				/* 移动结束 */
				m_isMoving = false;
				if(m_moveEnd != NULL) {
					m_moveEnd->moveEnd();
				}
			}
		}
	}
}

void ControllerSimpleMove::nextMovePos() {
	if(m_movePosList == NULL || m_movePosList->count() < 1) {
		return;
	}

	CC_SAFE_RELEASE(m_curDestPos);
	m_curDestPos = (PosBase*)m_movePosList->objectAtIndex(0);
	CC_SAFE_RETAIN(m_curDestPos);

	m_movePosList->removeObjectAtIndex(0);
}

void ControllerSimpleMove::moveByPos( PosBase* pos ) {
	if(m_isMoving == false && pos != NULL) {
		CCArray* posList = CCArray::createWithCapacity(1);
		posList->addObject(pos);
		moveByPosList(posList);
	}
}

MoveEnd::MoveEnd( CCObject* target, SEL_CallFuncM selector ) {
    CC_SAFE_RETAIN(target);
    m_target = target;

    m_selector = selector;
}

MoveEnd::~MoveEnd() {
    CC_SAFE_RELEASE(m_target);
}

void MoveEnd::moveEnd() {
    (m_target->*m_selector)(NULL);
}