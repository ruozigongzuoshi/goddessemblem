/*
    文件名：    GWWinBaseFactory.h
    描　述：    控件抽象工厂
*/
#ifndef __GW_WIN_BASE_FACTORY_H__
#define __GW_WIN_BASE_FACTORY_H__

#include "cocos2d.h"
#include "GWBase.h"
#include "EnumWinType.h"
USING_NS_CC;
class GWWinManager;

class GWWinBaseFactory : public CCObject {
public:

    GWBase* createWinByType(GWWinManager* manager, EnumWinType enWinType);

protected:
    /* 由子类负责创建控件 */
    virtual GWBase* createWin(EnumWinType enWinType) = 0;
};

#endif