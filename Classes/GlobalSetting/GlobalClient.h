/*
    文件名：    GlobalClient.h
    描　述：    游戏全局引用
    
*/
#ifndef _GlobalClient_H_
#define _GlobalClient_H_

#include "cocos2d.h"
#include "GameScene\TollgateScene.h"
USING_NS_CC;

class GlobalClient : public CCNode {
public:
	GlobalClient();
	~GlobalClient();

	static GlobalClient* sharedGlobalClient();
	virtual bool init();

	/* 设置当前关卡场景对象 */
	void setCurTollgateScene(TollgateScene* scene);

	/* 获取当前关卡场景对象 */
	TollgateScene* getCurTollgateScene();

	/* 设置当前关卡数 */
    void setiCurTollgateLevel(int iLevel);

	/* 获取当前关卡数 */
    int get_iCurTollgateLevel();

	/* 设置当前英雄编号 */
    void set_iCurHeroNo(int iNo);

	/* 获取当前英雄编号 */
    int get_iCurHeroNo();

	/* 设置当前英雄编号 */
    void set_iCurGold(int iGold);

	/* 获取当前英雄编号 */
    int get_iCurGold();

	int getMusicSet();

	void setMusicSet(int music);

	int getLanguage();

	void setLanguage(int language);

	void loadLanguage();

	void saveLanguage();

	void loadMusicSet();

	void saveMusicSet();

private:
	static GlobalClient* m_client;

	/* 当前关卡场景对象 */
	TollgateScene* m_curTollgateScene;

	/* 当前关卡数 */
    int m_iCurTollgateLevel;

	/* 当前英雄编号 */
    int m_iCurHeroNo;

	/* 当前金币 */
    int m_iCurGold; 

	int m_iMusicSet;

	int m_iLanguage;
};

#endif