#include "GWRoundOprBtn.h"

bool GWRoundOprBtn::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!GWBase::init());

		int distan = DEFAULT_DISTANCE;

		/* 在四个方向添加按钮 */
		addOneBtn(NULL, ccp(distan, 0));
		addOneBtn(NULL, ccp(0, -distan));
		addOneBtn(NULL, ccp(-distan, 0));
		addOneBtn(NULL, ccp(0, distan));

		bRet = true;
	} while (0);

	return bRet;
}

void GWRoundOprBtn::addOneBtn( CCNode* node, CCPoint pos )
{
	if(node == NULL) {
		node = CCSprite::create("sprite/hero/border_2.png");
	}
	this->addChild(node);

	CCActionInterval* moveOut = CCMoveBy::create(2.2f, pos);
	CCActionInterval* moveBack = CCEaseElasticOut::create(moveOut);
	node->runAction(moveBack);
}

GWRoundOprBtn* GWRoundOprBtn::createWithControlButtons( 
	CCControlButton* btn1, CCControlButton* btn2, CCControlButton* btn3, CCControlButton* btn4){
	GWRoundOprBtn* roundOprBtn = new GWRoundOprBtn();

	if(roundOprBtn && roundOprBtn->initWithControlButtons(btn1, btn2, btn3, btn4)) {
		roundOprBtn->autorelease();
	}
	else {
		CC_SAFE_DELETE(roundOprBtn);
	}

	return roundOprBtn;
}

bool GWRoundOprBtn::initWithControlButtons( 
	CCControlButton* btn1, CCControlButton* btn2, CCControlButton* btn3, CCControlButton* btn4) {
	bool bRet = false;

	do {
		CC_BREAK_IF(!GWBase::init());

		int distan = DEFAULT_DISTANCE;

		/* 在四个方向添加按钮 */
		addOneBtn(btn1, ccp(distan, 0));
		addOneBtn(btn2, ccp(0, -distan));
		addOneBtn(btn3, ccp(-distan, 0));
		addOneBtn(btn4, ccp(0, distan));

		bRet = true;
	} while (0);

	return bRet;
}

void GWRoundOprBtn::deleteMe() {
	this->removeFromParentAndCleanup(true);
}

