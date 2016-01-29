/*
    文件名：    TowerPosEditorScene.h
    描　述：    炮塔坐标编辑器
    
*/
#ifndef _TowerPosEditorScene_H_
#define _TowerPosEditorScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


class TowerPosEditorScene : public CCLayer {
public:
    TowerPosEditorScene();
    ~TowerPosEditorScene();

    static CCScene* scene();
    virtual bool init();

    CREATE_FUNC(TowerPosEditorScene);


private:
    
};


#endif