/*
    �ļ�����    GlobalClient.h
    �衡����    ��Ϸȫ������
    
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

	/* ���õ�ǰ�ؿ��������� */
	void setCurTollgateScene(TollgateScene* scene);

	/* ��ȡ��ǰ�ؿ��������� */
	TollgateScene* getCurTollgateScene();

	/* ���õ�ǰ�ؿ��� */
    void setiCurTollgateLevel(int iLevel);

	/* ��ȡ��ǰ�ؿ��� */
    int get_iCurTollgateLevel();

	/* ���õ�ǰӢ�۱�� */
    void set_iCurHeroNo(int iNo);

	/* ��ȡ��ǰӢ�۱�� */
    int get_iCurHeroNo();

	/* ���õ�ǰӢ�۱�� */
    void set_iCurGold(int iGold);

	/* ��ȡ��ǰӢ�۱�� */
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

	/* ��ǰ�ؿ��������� */
	TollgateScene* m_curTollgateScene;

	/* ��ǰ�ؿ��� */
    int m_iCurTollgateLevel;

	/* ��ǰӢ�۱�� */
    int m_iCurHeroNo;

	/* ��ǰ��� */
    int m_iCurGold; 

	int m_iMusicSet;

	int m_iLanguage;
};

#endif