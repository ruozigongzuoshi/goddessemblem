/*
    文件名：    TowerBorder.h
    描　述：    炮台
    
*/
#ifndef _TowerBorder_H_
#define _TowerBorder_H_

#include "Entity.h"

class Hero;
class TowerOprBtns;
class TowerBorder : public Entity {
public:
    TowerBorder();
    ~TowerBorder();

    CREATE_FUNC(TowerBorder);
    virtual bool init();

    /* 升级 */
    void upgrade();

	/* 判断坐标是否进入范围 */
	bool isClickMe(CCPoint pos);

	/* 绑定英雄对象 */
	void bindHero(Hero* hero);

	/* 获取英雄对象 */
	Hero* getHero();

	/* 删除英雄对象 */
	void deleteHero();

	/* 显示操作按钮 */
	void showTowerOprBtns();

	/* 删除操作按钮 */
	void deleteOprBtns();
private:
	/* 绑定的塔 */
	Hero* m_hero;

	/* 操作按钮 */
	TowerOprBtns* m_towerOprBtns;
};

#endif