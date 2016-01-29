/*
    文件名：    TowerPos.h
    描　述：    炮塔坐标对象
    
*/

#ifndef _TowerPos_H_
#define _TowerPos_H_

#include "PosBase.h"

#define RADIUS 65

class TowerBase;
class TowerPos : public PosBase {
public:
    TowerPos();
    ~TowerPos();

    static TowerPos* create(CCPoint pos);
    static TowerPos* create(CCPoint pos, bool isDebug);
    bool init(CCPoint pos);
    bool init(CCPoint pos, bool isDebug);

    virtual void draw();

    /* 判断坐标是否进入范围 */
    bool isClickMe(CCPoint pos);

private:
};

#endif