#include "I18N.h"
#include "CsvUtil.h"
#include "GlobalSetting/GlobalPath.h"
#include "GlobalSetting\GlobalClient.h"

/* ��ʼ������ */
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

    /* ��ʼ���ֵ� */
    mStringDict = CCDictionary::create();
    mStringDict->retain();
	GlobalClient::sharedGlobalClient()->loadLanguage();

	/* ��ȡ�����ļ����ַ��� */
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

    /* ����Ҳ����ַ������򷵻ؿհ��ַ��� */
    if(obj == NULL) {
        obj = CCString::create("");
    }
    return (CCString *)obj;
}


const char* I18N::getcString( EnumStrKey enStrKey ) {
	CCString* pStr = getString(enStrKey);

	/* ����Ҳ����ַ������򷵻ؿհ��ַ��� */
	if(pStr == NULL) {
		return "";
	}

	return pStr->getCString();
}

const char* I18N::getcStringByKey( int iKey ) {
	CCObject* obj = mStringDict->objectForKey(iKey);

	/* ����Ҳ����ַ������򷵻ؿհ��ַ��� */
	if(obj == NULL) {
		obj = CCString::create("");
	}
	return ((CCString *)obj)->getCString();
}

/* ---------------- ˽�з��� ----------------- */

void I18N::loadStringsFromConf(const char* filePath) {
    CsvUtil::sharedCsvUtil()->loadFile(filePath);

    CCSize size = CsvUtil::sharedCsvUtil()->getFileRowColNum(filePath);

    int iRowNum = size.width;
    int iColNum = size.height;

    /* �������С��2����ʾ�����ļ������� */
    if(iColNum < 2) {
        return;
    }

    /* �������ļ��������ַ�����ŵ��ֵ��У����Ե�һ�У� */
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
