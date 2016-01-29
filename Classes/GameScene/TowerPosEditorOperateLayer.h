/*
    文件名：    TowerPosEditorOperateLayer.h
    描　述：    塔坐标编辑器，操作层
    
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
	/* 编辑层 */
    TowerPosEditorLayer* layer;

    /* 添加操作控件 */
    void addWins();

    /* 把所有塔坐标对象生成到plist配置文件 */
    void outputPosToPlistFile(CCObject* pSender, CCControlEvent event);

    /* 切换到下一关 */
    void nextLvl(CCObject* pSender, CCControlEvent event);

    /* 切换到上一关 */
    void preLvl(CCObject* pSender, CCControlEvent event);

	/* 切换模式（塔坐标编辑/怪物坐标编辑） */
	void changeMode(CCObject* pSender, CCControlEvent event);

	/* 生成新的怪物坐标列表 */
    void addNewMonsterList(CCObject* pSender, CCControlEvent event);

    /* 切换到下一波 */
    void nextList(CCObject* pSender, CCControlEvent event);

    /* 切换到上一波 */
    void preList(CCObject* pSender, CCControlEvent event);

	/* 删除当前怪物坐标列表 */
	void deleteNowMonsterList(CCObject* pSender, CCControlEvent event);

	/* 怪物定制 */
    void startMonsterMgr(CCObject* pSender, CCControlEvent event);

    /* 切换到下一个 */
    void nextMonster(CCObject* pSender, CCControlEvent event);

    /* 切换到上一个 */
    void preMonster(CCObject* pSender, CCControlEvent event);

	/* 删除最后一个怪物 */
	void deleteLastMonster(CCObject* pSender, CCControlEvent event);

	/* 添加当前怪物 */
	void addNowMonster(CCObject* pSender, CCControlEvent event);
};

#endif
