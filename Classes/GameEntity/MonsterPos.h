/*
    文件名：    MonsterPos.h
    描　述：    怪物坐标对象
    
*/
#ifndef _MonsterPos_H_
#define _MonsterPos_H_

#include "PosBase.h"

#define MONSTER_RADIUS 10

class Monster;
class MonsterPos : public PosBase {
public:
	MonsterPos();
	~MonsterPos();

	static MonsterPos* create(CCPoint pos);
	static MonsterPos* create(CCPoint pos, bool isDebug);
	bool init(CCPoint pos);
	bool init(CCPoint pos, bool isDebug);

	virtual void draw();

	/* 判断坐标是否进入范围 */
	bool isClickMe(CCPoint pos);

private:
	Monster* m_monster;
};

#endif