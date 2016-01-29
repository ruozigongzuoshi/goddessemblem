#include "GWWinBaseFactory.h"
#include "GWWinManager.h"

GWBase* GWWinBaseFactory::createWinByType(GWWinManager* manager, EnumWinType enWinType ) {
    /* ���������������һ���ؼ� */
    GWBase* mWin = createWin(enWinType);

    /* ���ؼ�����һ��ΨһID(�������0) */
    mWin->setiWinID(manager->getWinSystem()->createUniqueID());

    /* ÿһ���ؼ���Ҫ��ӵ�desktop�� */
    manager->getDesktopWin()->addWin(mWin);

    return mWin;
}