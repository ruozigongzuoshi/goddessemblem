 #include "GWWinManager.h"
#include "support/tinyxml2/tinyxml2.h"
#include "GWWinXmlData.h"
#include "GWWinXmlDataSetting.h"
#include "GWDiv.h"


//GWWinManager* GWWinManager::mWinManager = NULL;


GWWinManager::GWWinManager() {
	//init();
	mWinXmlDataSetting = GWWinXmlDataSetting::create();
    mWinXmlDataSetting->retain();

    mDesktopWin = GWDesktopWin::create();
    mDesktopWin->retain();

    mWinSystem = GWWinSystem::create(this, mDesktopWin);
    mWinSystem->retain();
}

GWWinManager::~GWWinManager() {
    CC_SAFE_RELEASE_NULL(mWinXmlDataSetting);
    CC_SAFE_RELEASE_NULL(mWinSystem);
    CC_SAFE_RELEASE_NULL(mDesktopWin);
}


/*
GWWinManager* GWWinManager::sharedWinManager() {
    if(mWinManager == NULL) {
        mWinManager = new GWWinManager();

        if(mWinManager && mWinManager->init()) {
            mWinManager->autorelease();
        }
        else {
            CC_SAFE_DELETE(mWinManager);
            mWinManager = NULL;
        }
    }

    return mWinManager;
}
*/


bool GWWinManager::init() {
    mWinXmlDataSetting = GWWinXmlDataSetting::create();
    mWinXmlDataSetting->retain();

    mDesktopWin = GWDesktopWin::create();
    mDesktopWin->retain();

    mWinSystem = GWWinSystem::create(this, mDesktopWin);
    mWinSystem->retain();

    return true;
}

void GWWinManager::deleteAllData() {
	//CC_SAFE_RELEASE_NULL(mWinXmlDataSetting);
    //CC_SAFE_RELEASE_NULL(mWinSystem);
    //CC_SAFE_RELEASE_NULL(mDesktopWin);
    //mWinManager = NULL;
}

GWBase* GWWinManager::createWinsFromXML( const char* sXmlPath ) {
    /* ��ȡXML�ļ�,����MMWinXmlData���� */

    tinyxml2::XMLDocument * xmlDoc = new tinyxml2::XMLDocument();
    unsigned char* pBuffer = NULL;
    unsigned long bufferSize = 0;

    pBuffer = CCFileUtils::sharedFileUtils()->getFileData(sXmlPath, "r", &bufferSize);

    if (pBuffer)
    {
        xmlDoc->Parse((const char*)pBuffer);

    }


    XMLElement* rootElement = xmlDoc->RootElement();
    GWWinXmlData* xmlData = createXmlData(rootElement->FirstChildElement());

    delete xmlDoc;

    /* ���ɿؼ� */
    GWBase* baseWin = mWinSystem->createWinsByXmlData(xmlData, false);

    if(baseWin->isHasChildWin() == false) {
        mWinSystem->dressPropertiesByType(baseWin, xmlData);
    }

    /* ��Ӹ��ؼ��������� */        
    mDesktopWin->addChild(baseWin, baseWin->getiOrder());

    return baseWin;
}

GWWinXmlData* GWWinManager::createXmlData( XMLElement* xmlElement ) {
    GWWinXmlData* xmlData = GWWinXmlData::create();
    XMLElement* cldElement = xmlElement->FirstChildElement();

    CCLOG("%s %d: ----------------------------", __FILE__, __LINE__);

    /* Ĭ�Ͻڵ�Ϊ�սڵ� */
    xmlData->setNone(true);

    while(cldElement != NULL) {
        /* MMCld�ڵ������Ϊ��,���Բ���ȡ��������,���������ӽڵ� */
        if(cldElement->GetText() != NULL) {
            xmlData->setNone(false);

            /* ���ڵ㸳ֵ */
            setWinXmlData(xmlData, cldElement->Value(), cldElement->GetText());

            CCLog("%s %d:[%s]-[%s]", __FILE__, __LINE__, cldElement->Value(), cldElement->GetText());
        }
        else {
            /* ������ӽڵ�,���������,������ӵ���ǰ�ڵ���ӽڵ��б� */
            if(cldElement->FirstChildElement() != NULL) {
                xmlData->addCldXmlData(createXmlData(cldElement));
            }
        }

        /* ��һ��ͬ���ڵ� */
        cldElement = cldElement->NextSiblingElement();
    }

    return xmlData;
}

void GWWinManager::setWinXmlData( GWWinXmlData* xmlData, const char* sName, const char* sText ) {
    mWinXmlDataSetting->setWinXmlData(xmlData, sName, sText);
}


void GWWinManager::printTest( GWWinXmlData* xmlData ) {
    if(xmlData->isNone() == false) {
        CCLog("%s %d: x = %d", __FILE__, __LINE__, xmlData->getiX());
        CCLog("%s %d: y = %d", __FILE__, __LINE__, xmlData->getiY());
    }

    if(xmlData->isHasChild()) {
        CCArray* cldXmlDataList = xmlData->getCldXmlDataList();
        CCObject* obj = NULL;
        GWWinXmlData* cldXmlData = NULL;

        CCARRAY_FOREACH(cldXmlDataList, obj) {
            cldXmlData = (GWWinXmlData*) obj;
            printTest(cldXmlData);
        }
        
    }
}

GWDesktopWin* GWWinManager::getDesktopWin() {
    return this->mDesktopWin;
}

GWWinSystem* GWWinManager::getWinSystem() {
    return this->mWinSystem;
}