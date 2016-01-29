#include "GWWinSystem.h"
#include "GWDiv.h"

GWWinSystem::GWWinSystem()
: m_iWinID(0),
  mDesktopWin(NULL),
  mWinFactory(NULL),
  mWinProperityFactory(NULL) {

}

GWWinSystem::~GWWinSystem() {
    CC_SAFE_RELEASE(mDesktopWin);
    CC_SAFE_RELEASE(mWinFactory);
    CC_SAFE_RELEASE(mWinProperityFactory);
}

GWWinSystem* GWWinSystem::create(GWWinManager* managers, GWDesktopWin* desktopWin ) {
    GWWinSystem* winSystem = new GWWinSystem;
    if(winSystem && winSystem->init(managers, desktopWin)) {
        winSystem->autorelease();
    }
    else {
        CC_SAFE_DELETE(winSystem);
        winSystem = NULL;
    }

    return winSystem;
}

bool GWWinSystem::init(GWWinManager* managers, GWDesktopWin* desktopWin) {
    desktopWin->retain();
    this->mDesktopWin = desktopWin;
	manager = managers;

    /* �ؼ����� */
    mWinFactory = GWWinFactory::create();
    mWinFactory->retain();

    /* �ؼ����Լӹ��� */
    mWinProperityFactory = GWWinProperityFactory::create();
    mWinProperityFactory->retain();
    return true;
}

GWBase* GWWinSystem::createWinsByXmlData( GWWinXmlData* xmlData, bool isHasParent ) {
    assert(xmlData && "createWinsByXmlData:xmlData is NULL!");

    /* �涨ֻ����һ��MMBase,xml�����ɵ����пؼ������ո��ؼ��������ΨһMMBase */
    GWBase* baseWin = NULL;

    if(xmlData->isNone() == false) {
        baseWin = createWinByXmlData(xmlData);
    }

    if(xmlData->isHasChild()) {
        if(baseWin != NULL) {
            baseWin->setHasChildWin(true);

            /* ���û�и��ؼ������������Ǹ��ؼ������ؼ�Ҫ���ӿؼ�֮ǰ�������� */
            if(isHasParent == false) {
                /* ���ݿؼ����͸��ؼ��������ԣ����ؼ�Ҫ���ӿؼ�֮ǰ�������� */
                dressPropertiesByType(baseWin, xmlData);
            }
        }

        CCArray* cldXmlDataList = xmlData->getCldXmlDataList();
        CCObject* obj = NULL;
        GWWinXmlData* cldXmlData = NULL;

        CCARRAY_FOREACH(cldXmlDataList, obj) {
            cldXmlData = (GWWinXmlData*) obj;
            GWBase* mmWin = createWinsByXmlData(cldXmlData, true);

            baseWin->addChild(mmWin, cldXmlData->getiOrder());
            mmWin->setHasParentWin(true);

            
            /* ���ݿؼ����͸��ؼ��������ԣ����û�и��ؼ������������Ǹ��ؼ������ؼ��Ѿ����ù����ԣ����ظ����ã� */
            if(mmWin->isHasParentWin() == true) {
                dressPropertiesByType(mmWin, cldXmlData);

                //baseWin->removeChild(mmWin, true);
                //baseWin->addChild(mmWin, cldXmlData->getiOrder());
            }
        }

    }


    return baseWin;
}

GWBase* GWWinSystem::createWinByXmlData( GWWinXmlData* xmlData ) {
    assert(xmlData && "createWinByXmlData:xmlData is NULL!");
 
    EnumWinType enWinType = xmlData->getEnWinType();
    
    /* ���ݿؼ����ʹ����ؼ� */
    GWBase* win = createWinByType(enWinType);

    /* ��ӿؼ��ַ��������Ϳؼ�ID��ֵ�� */
    const char* sDes = xmlData->getsDes();
    if(sDes != NULL && strcmp(sDes, "") != 0) {
        mDesktopWin->addDesID(win->getiWinID(), sDes);
    }

    return win;
}

GWBase* GWWinSystem::createWinByType( EnumWinType enWinType ) {
    /* �ӿؼ���������һ���ؼ� */
    return mWinFactory->createWinByType(manager, enWinType);
}

int GWWinSystem::createUniqueID() {
    m_iWinID += 1;

    return m_iWinID;
}

void GWWinSystem::dressPropertiesByType( GWBase* mWin, GWWinXmlData* xmlData ) {
    mWinProperityFactory->dressPropertiesByType(mWin, xmlData);
}