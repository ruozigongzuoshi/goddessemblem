/*
    �ļ�����    BulletNormal.h
    �衡����    ��ͨ�ӵ�
   
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