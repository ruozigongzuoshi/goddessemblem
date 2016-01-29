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

    /* 控件工厂 */
    mWinFactory = GWWinFactory::create();
    mWinFactory->retain();

    /* 控件属性加工厂 */
    mWinProperityFactory = GWWinProperityFactory::create();
    mWinProperityFactory->retain();
    return true;
}

GWBase* GWWinSystem::createWinsByXmlData( GWWinXmlData* xmlData, bool isHasParent ) {
    assert(xmlData && "createWinsByXmlData:xmlData is NULL!");

    /* 规定只能有一个MMBase,xml中生成的所有控件的最终父控件都是这个唯一MMBase */
    GWBase* baseWin = NULL;

    if(xmlData->isNone() == false) {
        baseWin = createWinByXmlData(xmlData);
    }

    if(xmlData->isHasChild()) {
        if(baseWin != NULL) {
            baseWin->setHasChildWin(true);

            /* 如果没有父控件，代表自身是父控件，父控件要在子控件之前设置属性 */
            if(isHasParent == false) {
                /* 根据控件类型给控件设置属性，父控件要在子控件之前设置属性 */
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

            
            /* 根据控件类型给控件设置属性（如果没有父控件，代表自身是父控件，父控件已经设置过属性，不重复设置） */
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
    
    /* 根据控件类型创建控件 */
    GWBase* win = createWinByType(enWinType);

    /* 添加控件字符串描述和控件ID键值对 */
    const char* sDes = xmlData->getsDes();
    if(sDes != NULL && strcmp(sDes, "") != 0) {
        mDesktopWin->addDesID(win->getiWinID(), sDes);
    }

    return win;
}

GWBase* GWWinSystem::createWinByType( EnumWinType enWinType ) {
    /* 从控件工厂创建一个控件 */
    return mWinFactory->createWinByType(manager, enWinType);
}

int GWWinSystem::createUniqueID() {
    m_iWinID += 1;

    return m_iWinID;
}

void GWWinSystem::dressPropertiesByType( GWBase* mWin, GWWinXmlData* xmlData ) {
    mWinProperityFactory->dressPropertiesByType(mWin, xmlData);
}