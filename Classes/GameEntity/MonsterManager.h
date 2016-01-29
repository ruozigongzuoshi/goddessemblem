/*
    文件名：    MonsterManager.h
    描　述：    怪物管理器
    
*/
#ifndef _MonsterManager_H_
#define _MonsterManager_H_

#include "cocos2d.h"
USING_NS_CC;

class MonsterPos;
class MonsterManager : public CCNode {
public:
	MonsterManager();
	~MonsterManager();
	static MonsterManager* createWithLevel(int iCurLevel, int num);
	bool initWithLevel(int iCurLevel, int num);

	/* 读取配置文件创建怪物 */
	void createMonsters(int iCurLevel, int num);

	/* 获取还没有出场的怪物数量 */
	int getNotShowMonsterCount();

	/* 获取怪物出场坐标 */
	MonsterPos* getMonsterStartPos();

	/* 获取怪物终点坐标 */
	MonsterPos* getMonsterEndPos();

	/* 获取怪物列表 */
	CCArray* getMonsterList();
private:
	/* 未出场的怪物列表 */
	CCArray* m_notShowMonsterList;

	/* 存放所有怪物的坐标对象 */
	CCArray* m_monsterPosList;

	/* 怪物列表 */
	CCArray* m_monsterList;

	/* 用于计算怪物出场时间 */
	float m_fShowTimeCount;

	/* 检查是否有新怪物出场 */
	void showMonster(float dt);

	/* 管理器逻辑处理 */
	void logic(float dt);
};

#endif