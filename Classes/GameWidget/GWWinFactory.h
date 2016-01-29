/*
    �ļ�����    GWWinFactory.h
    �衡����    �ؼ�����
              ��Ҫ���𴴽��ؼ�
    
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