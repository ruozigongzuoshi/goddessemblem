/*
    文件名：    BulletNormal.h
    描　述：    普通子弹
   
*/
#ifndef _BulletNormal_H_
#define _BulletNormal_H_

#include "BulletBase.h"

class BulletNormal : public BulletBase {
public:
	BulletNormal();
	~BulletNormal();

    CREATE_FUNC(BulletNormal);
    virtual bool init();

	static BulletNormal* create(CCSprite* sprite);
	bool init(CCSprite* sprite);
protected:
    virtual void onLockAim(Entity* aim);
private:
    void moveEnd();
};

#endif