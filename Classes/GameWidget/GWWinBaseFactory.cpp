#include "GWWinBaseFactory.h"
#include "GWWinManager.h"

GWBase* GWWinBaseFactory::createWinByType(GWWinManager* manager, EnumWinType enWinType ) {
    /* 从子类件工厂创建一个控件 */
    GWBase* mWin = createWin(enWinType);

    /* 给控件设置一个唯一ID(必须大于0) */
    mWin->setiWinID(manager->getWinSystem()->createUniqueID());

    /* 每一个控件都要添加到desktop中 */
    manager->getDesktopWin()->addWin(mWin);

    return mWin;
}