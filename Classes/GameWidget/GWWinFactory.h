/*
    文件名：    GWWinFactory.h
    描　述：    控件工厂
              主要负责创建控件
    
*/
#ifndef __GW_WIN_FACTORY_H__
#define __GW_WIN_FACTORY_H__

#include "GWWinBaseFactory.h"

class GWWinFactory : public GWWinBaseFactory {
public:
    CREATE_FUNC(GWWinFactory);
    virtual bool init();

protected:
    virtual GWBase* createWin( EnumWinType enWinType );
};

#endif