/*
    文件名：    SceneManager.h
    描　述：    场景切换管理器
    
*/

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"

using namespace cocos2d;

class SceneManager : public CCObject {
public:
    /* 场景枚举类 */
    enum EnumSceneType {
        en_TollgateScene,  /* 关卡场景 */
        en_TollgateEditorScene, /* 关卡编辑器场景 */
		en_TollgateSelectScene,	/* 关卡选择场景 */
		en_WinScene,		/* 胜利场景 */
		en_GameOverScene,	/* 游戏结束场景 */
		en_StartScene,  /* 开始场景 */
		en_MenuScene,  /* 菜单场景 */
		en_HandbookScene,	/*图鉴*/
		en_HeroInfoScene,	/*英雄信息*/
		en_ShopScene,	/*商店*/
		en_SetScene,	/*设置*/
    };

    /* 获取场景管理器对象 */
    static SceneManager* sharedSceneManager();

    /* 初始化 */
    virtual bool init();

    /* 切换场景 */
    void changeScene(EnumSceneType enScenType);

private:
    /* 场景管理器对象 */
    static SceneManager* mSceneManager;
};

#endif