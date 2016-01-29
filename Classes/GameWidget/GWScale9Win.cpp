#include "GWScale9Win.h"
#include "GlobalSetting/GlobalParam.h"
#include "GlobalSetting/GlobalPath.h"

bool GWScale9Win::init() {
    return true;
}

GWScale9Win::GWScale9Win()
    : mScale9Sprite(NULL) {

}

GWScale9Win::~GWScale9Win() {
    CC_SAFE_RELEASE(mScale9Sprite);
}

void GWScale9Win::setScale9Sprite( CCScale9Sprite* scale9Sprite ) {
    scale9Sprite->retain();

    /* 坐标基准点要一致 */
    scale9Sprite->setAnchorPoint(getAnchorPoint());

    CC_SAFE_RELEASE(mScale9Sprite);

    this->mScale9Sprite = scale9Sprite;
    GWBase::addChild(scale9Sprite, GlobalParam::LayerOrder_LvLLowest);
}

void GWScale9Win::setScale9BG( const char* sPath, CCSize size ) {
    setScale9Sprite(CCScale9Sprite::create(sPath));

    this->mScale9Sprite->setContentSize(size);
}
