#include "PosLoadUtil.h"
#include "EnumPosType.h"
#include "TowerPos.h"
#include "MonsterPos.h"

PosLoadUtil* PosLoadUtil::m_posLoadUtil = NULL;

PosLoadUtil* PosLoadUtil::sharedPosLoadUtil() {
	if(m_posLoadUtil == NULL) {
		m_posLoadUtil = new PosLoadUtil();

		if(m_posLoadUtil && m_posLoadUtil->init()) {
			m_posLoadUtil->autorelease();
		}
		else {
			CC_SAFE_DELETE(m_posLoadUtil);
		}
	}

	return m_posLoadUtil;
}

bool PosLoadUtil::init() {

	return true;
}

CCArray* PosLoadUtil::loadPosWithFile( const char* sFilePath, EnumPosType enPosType, 
		CCNode* container, int iLevel, bool isDebug ) {
	CCArray* posList = CCArray::create();

	/* 读取plist文件 */
	CCArray* configArr = CCArray::createWithContentsOfFile(sFilePath);

	CCObject* obj = NULL;
	CCDictionary* dict = NULL;

	CCString* sX = NULL;
	CCString* sY = NULL;

	PosBase* posBase = NULL;
	CCARRAY_FOREACH(configArr, obj) {
		dict = dynamic_cast<CCDictionary*>(obj);

		/* 根据key值获取内容 */
		sX = dynamic_cast<CCString*>(dict->objectForKey("x"));
		sY = dynamic_cast<CCString*>(dict->objectForKey("y"));

		if(sX != NULL && sY != NULL) {
			if(sX != NULL && sY != NULL) {
				switch(enPosType) {
				case enTowerPos:
					posBase = TowerPos::create(CCPoint(sX->intValue(), sY->intValue()), isDebug);
					break;
				case enMonsterPos:
					posBase = MonsterPos::create(CCPoint(sX->intValue(), sY->intValue()), isDebug);
					break;
				default:
					posBase = TowerPos::create(CCPoint(sX->intValue(), sY->intValue()), isDebug);
					break;
				}
				posList->addObject(posBase);

				if(container != NULL) {
					container->addChild(posBase, iLevel);
				}
			}
		}
	}
	return posList;
}

