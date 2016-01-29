/*
    �ļ�����    TowerPosEditorOperateLayer.h
    �衡����    ������༭����������
    
*/
#ifndef _TowerPosEditorOperateLayer_H_
#define _TowerPosEditorOperateLayer_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GWWinManager;
class GWLabel;

class TowerPosEditorLayer;
class TowerPosEditorOperateLayer : public CCLayer {
public:
    TowerPosEditorOperateLayer();
    ~TowerPosEditorOperateLayer();

    static TowerPosEditorOperateLayer* create(TowerPosEditorLayer* layer);
    virtual bool init(TowerPosEditorLayer* layer);

	virtual void draw();
	void  gotoMenu(CCObject* pSender, CCControlEvent event);
private:
	GWLabel* modeLabel;
	GWWinManager* manager;
	/* �༭�� */
    TowerPosEditorLayer* layer;

    /* ��Ӳ����ؼ� */
    void addWins();

    /* ������������������ɵ�plist�����ļ� */
    void outputPosToPlistFile(CCObject* pSender, CCControlEvent event);

    /* �л�����һ�� */
    void nextLvl(CCObject* pSender, CCControlEvent event);

    /* �л�����һ�� */
    void preLvl(CCObject* pSender, CCControlEvent event);

	/* �л�ģʽ��������༭/��������༭�� */
	void changeMode(CCObject* pSender, CCControlEvent event);

	/* �����µĹ��������б� */
    void addNewMonsterList(CCObject* pSender, CCControlEvent event);

    /* �л�����һ�� */
    void nextList(CCObject* pSender, CCControlEvent event);

    /* �л�����һ�� */
    void preList(CCObject* pSender, CCControlEvent event);

	/* ɾ����ǰ���������б� */
	void deleteNowMonsterList(CCObject* pSender, CCControlEvent event);

	/* ���ﶨ�� */
    void startMonsterMgr(CCObject* pSender, CCControlEvent event);

    /* �л�����һ�� */
    void nextMonster(CCObject* pSender, CCControlEvent event);

    /* �л�����һ�� */
    void preMonster(CCObject* pSender, CCControlEvent event);

	/* ɾ�����һ������ */
	void deleteLastMonster(CCObject* pSender, CCControlEvent event);

	/* ��ӵ�ǰ���� */
	void addNowMonster(CCObject* pSender, CCControlEvent event);
};

#endif
