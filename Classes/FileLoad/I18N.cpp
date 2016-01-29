#include "I18N.h"
#include "CsvUtil.h"
#include "GlobalSetting/GlobalPath.h"
#include "GlobalSetting\GlobalClient.h"

/* 初始化变量 */
I18N* I18N::mI18N = NULL;

I18N* I18N::shareI18N() {
    if(mI18N == NULL) {
        mI18N = new I18N();
        if(mI18N && mI18N->init()) {
            mI18N->autorelease();
        }
        else {
            CC_SAFE_DELETE(mI18N);
            mI18N = NULL;
        }
    }

    return mI18N;
}

bool I18N::init() {

    /* 初始化字典 */
    mStringDict = CCDictionary::create();
    mStringDict->retain();
	GlobalClient::sharedGlobalClient()->loadLanguage();

	/* 读取配置文件的字符串 */
	switch(GlobalClient::sharedGlobalClient()->getLanguage())
	{
	case 0:loadStringsFromConf(PATH_I18N_PUBLIC);break;
	case 1:loadStringsFromConf(PATH_I18N_ENGLISH);break;
	default:loadStringsFromConf(PATH_I18N_PUBLIC);break;
	}
    
    return true;
}

CCString* I18N::getString( EnumStrKey enStrKey ) {
    CCObject* obj = mStringDict->objectForKey(enStrKey);

    /* 如果找不到字符串，则返回空白字符串 */
    if(obj == NULL) {
        obj = CCString::create("");
    }
    return (CCString *)obj;
}


const char* I18N::getcString( EnumStrKey enStrKey ) {
	CCString* pStr = getString(enStrKey);

	/* 如果找不到字符串，则返回空白字符串 */
	if(pStr == NULL) {
		return "";
	}

	return pStr->getCString();
}

const char* I18N::getcStringByKey( int iKey ) {
	CCObject* obj = mStringDict->objectForKey(iKey);

	/* 如果找不到字符串，则返回空白字符串 */
	if(obj == NULL) {
		obj = CCString::create("");
	}
	return ((CCString *)obj)->getCString();
}

/* ---------------- 私有方法 ----------------- */

void I18N::loadStringsFromConf(const char* filePath) {
    CsvUtil::sharedCsvUtil()->loadFile(filePath);

    CCSize size = CsvUtil::sharedCsvUtil()->getFileRowColNum(filePath);

    int iRowNum = size.width;
    int iColNum = size.height;

    /* 如果列数小于2，表示配置文件有问题 */
    if(iColNum < 2) {
        return;
    }

    /* 将配置文件的所有字符串存放到字典中（忽略第一行） */
    CCString* keyStr = CCString::create("");
    CCString* valueStr = NULL;
    for(int i = 1; i < iRowNum; i++) {
        valueStr = CCString::create("");

        keyStr->m_sString = CsvUtil::sharedCsvUtil()->get(i, 0, filePath);
        valueStr->m_sString = CsvUtil::sharedCsvUtil()->get(i, 1, filePath);

        int iKey = 0;
        sscanf(keyStr->getCString(), "%d", &iKey);
        mStringDict->setObject(valueStr, iKey);
    }

}
