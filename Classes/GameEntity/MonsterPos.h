/*
    �ļ�����    MonsterPos.h
    �衡����    �����������
    
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

	/* �ж������Ƿ���뷶Χ */
	bool isClickMe(CCPoint pos);

private:
	Monster* m_monster;
};

#endif