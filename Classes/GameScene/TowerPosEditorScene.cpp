#include "TowerPosEditorScene.h"
#include "GameEntity/TowerPos.h"
#include "TowerPosEditorOperateLayer.h"
#include "TowerPosEditorLayer.h"
#include "FileLoad/I18N.h"

TowerPosEditorScene::TowerPosEditorScene() {

}

TowerPosEditorScene::~TowerPosEditorScene() {

}

CCScene* TowerPosEditorScene::scene() {
    CCScene* scene = NULL;

    do {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        TowerPosEditorLayer* layer = TowerPosEditorLayer::create();
        CC_BREAK_IF(! layer);

        TowerPosEditorOperateLayer* operateLayer = TowerPosEditorOperateLayer::create(layer);
        CC_BREAK_IF(! operateLayer);

        scene->addChild(layer, 1);
        scene->addChild(operateLayer, 2);

		/* ²âÊÔI18N¹¤¾ßÀà */
		CCLOG("I18N Test: %s", I18N::shareI18N()->getcString(en_StrKey_Public_Confirm));
    } while (0);
    return scene;
}

bool TowerPosEditorScene::init() {
    return true;
}